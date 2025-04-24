#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include "setting.h"
#include "priority_queue.h"
#include <iostream>
#include <fstream>

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

    string code[MAX_ASC_SIZE];

public:
    HuffmanCode()
    {
        exist = 0;
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
        if (heap.validateMinHeap())
        {
            cout << "[INFO] Heap is valid (min-heap)\n";
        }
        else
        {
            cout << "[ERROR] Heap structure is invalid!\n";
        }
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
        // cout << "[INFO] exist count : " << exist << endl;
    }

    // 문자열 빈도 수 확인
    void printFreq()
    {
        cout << "[INFO] print frequncey" << endl;
        for (int i = 0; i < MAX_ASC_SIZE; i++)
        {
            if (freq[i] > 0)
            {
                if (isprint(i))
                {
                    cout << (char)i << " : " << freq[i] << " exists" << endl;
                }
                else
                {
                    cout << getControlCharName(i) << " : " << freq[i] << " exists" << endl;
                }
            }
        }
        cout << endl;
    }

    // 허프만 코드로 변환 -> sample.enc 파일 저장
    // 알고리즘 동작 , 초기에 세팅된 우선 순위 코드를 보고 하나의 트리를 생성 -> 트리를 참고하여 원본 파일 인코딩
    void encode()
    {
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
        // printCodeTable();
        if (freq[13] > 0)
            cout << "CR(\\r) exists: " << freq[13] << endl;
        if (freq[10] > 0)
            cout << "LF(\\n) exists: " << freq[10] << endl;
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

    // 원본 파일을 읽고 비트 단위로 인코딩 파일에 작성하기 위해 필요한 함수
    void encodeToFile(const string &inputPath, const string &outputPath, Node *root)
    {
        ifstream input(inputPath, ios::binary);
        ofstream output(outputPath, ios::binary);

        int originalCharCount = 0;
        ifstream countInput(inputPath, ios::binary);
        char ch;
        while (countInput.get(ch))
            originalCharCount++;
        countInput.close();

        output.write((char *)&originalCharCount, sizeof(int)); // 4바이트 저장
        serializeTree(root, output);

        unsigned char buffer = 0;
        int bitCount = 0;

        // char ch;
        while (input.get(ch))
        {
            string code = this->code[(unsigned char)ch];

            // 현재 코드 테이블에 있는 내용은 0과 1를 표현하는 문자열 -> 이를 실제 비트로 변환해야됨.
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
            // 나머지 비트 수 만큼 쉬프팅
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
        // printCodeTable();
        if (!code[13].empty())
            cout << "CR(\\r) exists " << endl;
        if (!code[10].empty())
            cout << "LF(\\n) exists " << endl;
    }

    void decodeFromFile(const string &encodedPath, const string &outputPath)
    {
        ifstream in(encodedPath, ios::binary);
        ofstream out(outputPath, ios::binary);
        int totalChars;
        in.read((char *)&totalChars, sizeof(int)); // 문자 개수 읽기
        Node *root = deserializeTree(in);          // 트리 복원
        buildHuffmanCode(root, "");
        Node *current = root;

        int decodedChars = 0;
        char byte;
        while (in.get(byte) && decodedChars < totalChars)
        {
            for (int i = 7; i >= 0 && decodedChars < totalChars; --i)
            {
                int bit = (byte >> i) & 1;
                current = (bit == 0) ? current->left : current->right;

                if (!current->left && !current->right)
                {
                    out.put(current->symbol);
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
        ifstream original(originalPath, ios::binary | ios::ate);
        ifstream compressed(compressedPath, ios::binary | ios::ate);

        double originalSize = original.tellg();
        double compressedSize = compressed.tellg();

        return 100.0 * (1.0 - (compressedSize / originalSize)); // 압축률 %
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
        while (file1.get(ch1) && file2.get(ch2))
        {
            if (ch1 != ch2)
            {
                cout << "[DIFF] pos " << index << " different: ";
                cout << "file1 = " << (int)(unsigned char)ch1 << ", ";
                cout << "file2 = " << (int)(unsigned char)ch2 << '\n';
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