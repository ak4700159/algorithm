#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include "setting.h"
#include <iostream>
#include <fstream>

using namespace std;

class HuffmanCode
{
private:
    int freq[MAX_ASC_SIZE]{0};

public:
    HuffmanCode()
    {
        ifstream file("sample.txt");
        if (!file.is_open())
        {
            std::cerr << "[INFO] 파일을 열 수 없습니다.\n";
            return;
        }

        char ch;
        while (file.get(ch))
        {
            freq[(unsigned char)ch]++; // 문자를 정수 인덱스로 사용
        }

        // min-priority queue 구성하기 
    }

    // 허프만 코드로 변환 -> sample.enc 파일 저장
    void encode() {

    }

    // 원본 파일로 복원 -> sample.dec 파일 저장
    void decode() {

    }

    // 두 개의 파일(sample.txt, sample.dec) 비교
    bool compareFile() {
        return true;
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