#ifndef __SPELL_CHECKER_H__
#define __SPELL_CHECKER_H__

#define MAX_STR 20
#define MAX_INT 999999

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

class SpellChecker{
private:
    // s => t로 가기 위한 거리를 구하게 된다.
    char s[MAX_STR];    // 
    char t[MAX_STR];
    int width;          // s의 길이 + 1 = 테이블 세로의 길이(width)
    int height;         // t의 길이 + 1 = 테이블 가로의 길이(height)
    int** table;        // edit distance table(width * height) 
public:
    SpellChecker(const char* str1, const char* str2) {
        strcpy(this->s, str1);  strcpy(this->t, str2);
        height = strlen(s) + 1;     width = strlen(t) + 1;
        table = new int*[height];
        for(int i = 0; i < height; i++) {
            table[i] = new int[width] { -1 };
        }

        // 첫번째 행, 첫번째 열 초기화 
        for(int i = 0; i < width; i++) {
            table[0][i] = i;
        }
        for(int i = 0; i < height; i++) {
            table[i][0] = i;
        }
    }

    ~SpellChecker() {
        for(int i = 0; i < height; i++) {
            delete[] table[i];
        }
        delete[] table;
    }



    // edit distance 알고리즘 실행
    // 최소가 되는 거리를 반환한다.
    int exec() {
        for(int i = 1; i < height; i++) {
            for(int j = 1; j < width; j++) {
                // 삭제 연산을 해야하는 경우
                int del = table[i-1][j] + 1;
                // 삽입 연산을 해야하는 경우 
                int ins = table[i][j-1] + 1;
                // 교체 연산을 해야하는 경우(맨마지막 글자가 같은지 판별)
                int rep = table[i-1][j-1] + ((s[j-1] == t[i-1]) ? 0 : 1);
                // 세 값 중 가장 작은 값 반환
                table[i][j] = findMin(del, ins, rep);
            }
        } 
        // 결과적으로 최종해를 반환하게 된다.
        return table[height-1][width-1];
    }

    // 세 개의 값 중 최소가 되는 값 반환
    int findMin(int n1, int n2, int n3) {
        int min = n1;
        if (n2 < min) min = n2;
        if (n3 < min) min = n3;
        return min;
    }


    // table 출력 함수
    void pritnTable() {
        cout << setw(4) << "S|T";
        for (int j = 0; j < width; j++) {
            cout << setw(3) << j;
        }
        cout << endl;
        for (int i = 0; i < height; i++) {
            cout << setw(4) << i;  // 행 번호
            for (int j = 0; j < width; j++) {
                cout << setw(3) << table[i][j];
            }
            cout << endl;
        }
    }
};


#endif