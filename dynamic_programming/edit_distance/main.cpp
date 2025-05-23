#include "spell_checker.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

void sol1();
void sol2();

int main(void) {
    sol1();
    sol2();
    return 0;
}

// 1. 두 문자열 str1과 str2가 주어졌을 때, 
// 1-1. 삽입, 삭제, 치환 연산만으로 str1을 str2로 바꾸는 최소 연산 횟수를 구하시오.
// 1-2. Edit Distance Table을 출력하시오.
void sol1() {
    char str1[MAX_STR]; char str2[MAX_STR];
    cout << "user input(str1, str2) : "; 
    cin >> str1 >> str2;
    SpellChecker checker = SpellChecker(str1, str2);  
    int result = checker.exec();
    checker.pritnTable();
    cout << "edit distance : " << result << endl << endl;
}   


// 2. 사전에 다음 세단어 있을 때, 사용자가 입력한 단어를 수정해서 출력하시오.
// 사용자 입력: "definately"
// 사전 단어: ["definitely", "defiantly", "define"]
// (출력) 추천: "definitely" (edit distance 3)
void sol2() {
    // 단어 리스트 
    const char* dictionary[] = {"definitely", "defiantly", "define"};
    // 입력 문자열 초기화
    char* input; char buffer[MAX_STR];
    cout << "user input : "; cin >> buffer;
    input = new char[strlen(buffer)];
    strcpy(input, buffer);
    // edit distrance 알고리즘을 통해 어떤 문자와 가장 유사한지 확인
    int min = MAX_INT; char minWord[MAX_STR];
    for(int i = 0; i < 3; i++) {
        SpellChecker checker = SpellChecker(input, dictionary[i]);  
        int result = checker.exec();
        if(result < min) {
            min = result;
            strcpy(minWord, dictionary[i]);
        }
        // checker.pritnTable();
    }
    cout << "recommend output : " << minWord << "( edit distacne " << min << " )"  << endl;
}