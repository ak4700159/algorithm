#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include "setting.h"
#include "priority_queue.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class HuffmanCode
{
private:
    // 빈도수 측정용
    int freq[MAX_ASC_SIZE]{0};
    // 파일 안에 몇가지의 문자가 존재한느지
    int exist;
    // 최소 우선순위 큐
    Heap heap;
    // 허프만 코드 테이블(아스키 코드값에 따라 0101011 이진수를 문자열로 표현)
    string code[MAX_ASC_SIZE];

public:
    HuffmanCode()
    {
        exist = 0;
        // 파일에서 문자 빈도 수 측정
        openFile();
        countExistChar();
        // min-priority queue 구성하기
        heap = Heap(exist);
        for (int i = 0; i < MAX_ASC_SIZE; i++)
        {
            if (freq[i] > 0)
            {
                heap.insert(new Node(char(i), freq[i]));
            }
        }
        // Heap 검증
        // if (heap.validateMinHeap())
        // {
        //     cout << "[INFO] Heap is valid (min-heap)\n";
        // }
        // else
        // {
        //     cout << "[ERROR] Heap structure is invalid!\n";
        // }
    }

    void openFile()
    {
        ifstream file("sample.txt");
        if (!file.is_open())
        {
            std::cerr << "[INFO] file open failed\n";
            return;
        }

        char ch;
        while (file.get(ch))
        {
            freq[(unsigned char)ch]++; // 문자를 정수 인덱스로 사용
        }
        file.close();
    }

    // Heap의 크기를 정하고 몇 종류의 문자들이 존재하는지 확인
    void countExistChar()
    {
        for (int i = 0; i < MAX_ASC_SIZE; i++)
        {
            if (freq[i] > 0)
            {
                exist++;
            }
        }
    }

    // 문자열 빈도 수 확인
    void printFreq()
    {
        cout << "[INFO] print frequency table\n";
        int count = 0;
        for (int i = 0; i < MAX_ASC_SIZE; ++i)
        {
            if (freq[i] > 0)
            {
                string label;
                if (isprint(i))
                {
                    label = "'" + string(1, (char)i) + "'";
                }
                else
                {
                    label = getControlCharName(i);
                }

                // 포맷: [문자 or 이름] : 빈도수
                cout << left << setw(4) << label << ":";
                cout << right << setw(4) << freq[i] << " |";

                if ((++count) % 5 == 0)
                    cout << endl;
            }
        }
        if (count % 5 != 0)
            cout << endl;
    }

    // 허프만 코드로 변환 -> sample.enc 파일 저장
    // 알고리즘 동작 , 초기에 세팅된 우선 순위 코드를 보고 하나의 트리를 생성 -> 트리를 참고하여 원본 파일 인코딩
    void encode()
    {
        printFreq();
        // 히프에 한 개의 노드만 남을 때까지 반복(문자 수만큼)
        while (heap.getSize() > 1)
        {
            Node *remove1 = heap.remove();
            Node *remove2 = heap.remove();
            Node *combind = new Node(remove1->frequcncy + remove2->frequcncy, remove1, remove2);
            heap.insert(combind);
        }
        Node *root = heap.remove();
        // 허프만 코드 테이블을 만든다.
        buildHuffmanCode(root, "");
        // 만들어진 코드 테이블을 이용해 파일을 압축
        encodeToFile("sample.txt", "sample.enc", root);
    }

    // 허프만 코드를 빌드하는 함수.(root nood 시작 -> 전위순회)
    // leaf node => 무조건 문자가 들어있는 노드다.
    void buildHuffmanCode(Node *node, string path)
    {
        if (!node)
            return;

        if (!node->left && !node->right)
        {
            code[(unsigned char)node->symbol] = path;
            return;
        }

        buildHuffmanCode(node->left, path + "0");
        buildHuffmanCode(node->right, path + "1");
    }

    // 원본 파일을 읽고 비트 단위로 인코딩()
    void encodeToFile(const string &inputPath, const string &outputPath, Node *root)
    {
        ifstream input(inputPath, ios::binary);
        ofstream output(outputPath, ios::binary);

        // 1. 전체 파일 사이즈 출력 파일에 쓰기
        int originalCharCount = 0;
        ifstream countInput(inputPath, ios::binary);
        char ch;
        while (countInput.get(ch))
            originalCharCount++;
        countInput.close();
        output.write((char *)&originalCharCount, sizeof(int));

        // 2. 트리 직렬화
        serializeTree(root, output);

        // 3. 원본 파일을 읽고 생성된 허프만 코드 테이블을 참고해
        unsigned char buffer = 0;
        int bitCount = 0;
        while (input.get(ch))
        {
            string code = this->code[(unsigned char)ch];
            // 현재 코드 테이블에 있는 내용은 0과 1를 표현하는 문자열 -> 이를 실제 비트 단위로 변환해야됨.
            for (char bit : code)
            {
                // 왼쪽 쉬프팅(제일 왼쪽엔 0으로 채워짐)
                buffer <<= 1;
                // 만약 1이였다면 마지막 비트를 1로 변환
                if (bit == '1')
                    buffer |= 1; // 1 => 0000 0001
                bitCount++;

                // 바이트 단위로 저장하게됨
                if (bitCount == 8)
                {
                    output.put(buffer);
                    buffer = 0;
                    bitCount = 0;
                }
            }
        }

        // 나머지 비트 저장
        if (bitCount > 0)
        {
            // 나머지 비트 수 만큼 쉬프팅 -> 즉 0으로 패팅
            buffer <<= (8 - bitCount);
            output.put(buffer);
        }

        input.close();
        output.close();
    }

    // 원본 파일로 복원 -> sample.dec 파일 저장
    void decode()
    {
        decodeFromFile("sample.enc", "sample.dec");
    }

    // encoded file format : [file length][serialized tree][encoded content]
    void decodeFromFile(const string &encodedPath, const string &outputPath)
    {
        ifstream in(encodedPath, ios::binary);
        ofstream out(outputPath, ios::binary);
        int totalChars;
        // 문자 개수 읽기 [file length]
        in.read((char *)&totalChars, sizeof(int));
        // 트리 복원 [serialized tree]
        Node *root = deserializeTree(in);
        buildHuffmanCode(root, "");
        Node *current = root;

        int decodedChars = 0;
        char byte;
        // 바이트 단위로 읽기
        while (in.get(byte) && decodedChars < totalChars)
        {
            // 바이트 안에서 비트 단위로 접근하기 위한 반복문
            for (int i = 7; i >= 0 && decodedChars < totalChars; --i)
            {
                // 오른쪽 쉬프팅을 통해 현재 비교 하고자 하는 비트를 맨 오른쪽 위치시킨다.
                // 쉬프팅된 바이트 & [0000 0001] 하여 0인지 1인지 판별
                int bit = (byte >> i) & 1;
                // 비트가 0이면 왼쪽으로 1이면 오른쪽으로 이동
                current = (bit == 0) ? current->left : current->right;

                // 리프 노드면 해당 노드가 심볼을 가지는 노드를 의미
                if (!current->left && !current->right)
                {
                    // 복원된 문자를 작성
                    out.put(current->symbol);
                    // 다시 root에서부터 시작
                    current = root;
                    decodedChars++;
                }
            }
        }

        in.close();
        out.close();
    }

    void printCodeTable()
    {
        for (int i = 0; i < MAX_ASC_SIZE; ++i)
        {
            if (!code[i].empty())
            {
                if (isprint(i))
                    cout << "'" << (char)i << "' : " << code[i] << endl;
                else
                    cout << "[ASCII " << i << "] : " << code[i] << endl;
            }
        }
    }

    // 압축률 확인용
    double getCompressionRate(const string &originalPath, const string &compressedPath)
    {
        // ios::ate 파일 위치 포인터를 끝에 두기
        ifstream original(originalPath, ios::binary | ios::ate);
        ifstream compressed(compressedPath, ios::binary | ios::ate);

        // 파일의 끝위치를 기반해 압축률 계산
        double originalSize = original.tellg();
        double compressedSize = compressed.tellg();

        return 100.0 * (1.0 - (compressedSize / originalSize));
    }

    // 두 개의 파일(sample.txt, sample.dec) 비교
    bool compareFile()
    {
        ifstream file1("sample.txt", ios::binary);
        ifstream file2("sample.dec", ios::binary);

        if (!file1.is_open() || !file2.is_open())
        {
            cerr << "[ERROR] file open failed.\n";
            return false;
        }

        char ch1, ch2;
        size_t index = 0;
        // 두 개의 파일을 한 글자씩 읽으면서 동일한지 비교
        while (file1.get(ch1) && file2.get(ch2))
        {
            if (ch1 != ch2)
            {
                cout << "[DIFF] pos " << index << " different: ";
                cout << "sample.txt = " << (int)(unsigned char)ch1 << ", ";
                cout << "sample.dec = " << (int)(unsigned char)ch2 << '\n';
                return false;
            }
            index++;
        }

        // 한 파일만 EOF에 도달한 경우
        if (file1.get(ch1) || file2.get(ch2))
        {
            cout << "[DIFF] file length is different\n";
            return false;
        }

        return true;
    }

    // 트리 직렬화
    void serializeTree(Node *node, ostream &out)
    {
        if (!node)
            return;

        // 리프 노드인 경우 flag 1로 표현 후 문자 삽입
        if (!node->left && !node->right)
        {
            out.put('1');
            out.put(node->symbol);
        }
        // 리프 노드가 아닌 경우 flag 0
        else
        {
            out.put('0');
            serializeTree(node->left, out);
            serializeTree(node->right, out);
        }
    }

    // 트리 역직렬화
    // 문자의 빈도 수는 중요하지 않다. 허프만 코드를 복원하는 것이 목표
    Node *deserializeTree(istream &in)
    {
        char flag;
        if (!in.get(flag))
            return nullptr;

        // 리프 노드 발견
        if (flag == '1')
        {
            char symbol;
            in.get(symbol);
            return new Node(symbol, 0); // freq는 중요하지 않음
        }
        // 리프 노드가 아닌 경우
        else
        {
            Node *left = deserializeTree(in);
            Node *right = deserializeTree(in);
            return new Node(0, left, right);
        }
    }
};

#endif