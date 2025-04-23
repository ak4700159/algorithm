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

public:
    HuffmanCode()
    {
        exist = 0;
        openFile();
        countExistChar();
        // min-priority queue 구성하기
        heap = Heap(exist);
        for (int i = 0; i < exist; i++)
        {
            if(freq[i] > 0)
            {
                heap.insert(Node(char(i), freq[i]));
            }
        }
        
    }

    // 허프만 코드로 변환 -> sample.enc 파일 저장
    // 알고리즘 동작 , 초기에 세팅된 우선 순위 코드를 보고 하나의 트리를 생성 -> 트리를 참고하여 원본 파일 인코딩
    void encode()
    {
    }

    // 원본 파일로 복원 -> sample.dec 파일 저장
    void decode()
    {
    }

    // 두 개의 파일(sample.txt, sample.dec) 비교
    bool compareFile()
    {
        return true;
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
    }

    // Heap의 크기를 정하기 위해 몇 종류의 문자들이 존재하는지 확인
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

    // 제어 문자 출력
    string getControlCharName(int code)
    {

        if (code >= 0 && code < 32)
            return control[code];
        else if (code == 127)
            return "DEL";
        else
            return "UNKNOWN";
    }
};

#endif