#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "daegu_weather.h"
using namespace std;
 
int MAX_LINES = 0;

// [p~m]/[m+1~q] 두 개의 블록에 대해 병합 -> 내림차순으로 정렬
void mergeWeather(DaeguWeather* weathers, DaeguWeather* result, int p, int q, int m) {
    int resultIdx = p;
    int leftStartIdx = p;
    int rightStartIdx = m+1;

    do{
        if(weathers[leftStartIdx].temperature >= weathers[rightStartIdx].temperature)  
                result[resultIdx++] = weathers[leftStartIdx++];
        else    result[resultIdx++] = weathers[rightStartIdx++];
    } while((leftStartIdx <= m && rightStartIdx <= q));

    while(leftStartIdx <= m)      result[resultIdx++] = weathers[leftStartIdx++];
    while (rightStartIdx <= q)    result[resultIdx++] = weathers[rightStartIdx++];
    copyResultToList(weathers, result, p, q);
}

// p와 q는 인덱스
void mergeSortWeather(DaeguWeather* weathers, DaeguWeather* result, int p, int q) {
    if(p < q) {
        int k = (p+q)/2;
        mergeSortWeather(weathers, result, p, k);
        mergeSortWeather(weathers, result, k+1, q);

        // 합병 진행 p ~ q 까지에 대해 비교 하면됨.
        mergeWeather(weathers, result, p, q, k);
    }
}

void printWeather(DaeguWeather* weathers){
    cout << ("[INFO] ");
    for(int i = 0; i < MAX_LINES; i++) {
        if( i % 5 == 0) cout << endl;
        cout << "[" << weathers[i].date << "|" << weathers[i].temperature << "]" << " -> " ;
    }
    cout << ("[END]") << endl;
}

void test(DaeguWeather* weathers){
    for(int i = 0; i < MAX_LINES; i++) {
        weathers[i].temperature = 0;
        strcpy(weathers[i].date, "emp");
    }
}

void printTop3(DaeguWeather* weathers){
    for(int i = 0; i < 3; i++) {
        cout << "[TOP" << i << "] [" << weathers[i].date << "|" << weathers[i].temperature << "]" << endl;
    }
}

void copyResultToList(DaeguWeather* weathers, DaeguWeather* result, int p, int q) {
    for(; p <= q; p++){
        weathers[p] = result[p];
    }
}

// 반환값으로 배열길이 반환
int setWeathers(DaeguWeather** weathers, DaeguWeather** result) {
    ifstream file("daegu_weather_2024.txt");
    string line;
    int lines = 0;
    int capacity = 1;

    weathers[0] = (DaeguWeather*)malloc(capacity * sizeof(DaeguWeather));
    while (getline(file, line)){
        // 재할당
        if(lines >= capacity) {
            capacity *= 2;
            weathers[0] = (DaeguWeather*)realloc(weathers[0], capacity * sizeof(DaeguWeather));
            if(weathers[0] == NULL || result[0] == NULL) {
                cout << "[ERROR]realloc failed" << endl;
            }
        }
        weathers[0][lines] = *makeNewDaeguWeather(line);
        lines++;
    }

    file.close();
    result[0] = (DaeguWeather*)calloc(lines, sizeof(DaeguWeather));
    MAX_LINES = lines;
    return lines;
}

DaeguWeather* makeNewDaeguWeather(string line) {
    string date = line.substr(0, sizeof("0000-00-00") - 1);
    DaeguWeather* weather = (DaeguWeather*)malloc(sizeof(DaeguWeather));
    strcpy(weather->date, date.c_str());
    weather->temperature = stoi(line.substr(line.find(" ")));
    return weather;
}

void saveWeather(DaeguWeather* weathers) {
    ofstream file("./daegu_weather_2024_output.txt");
    for(int i = 0; i < MAX_LINES; i++){
        file << weathers[i].date << " "  << weathers[i].temperature << endl;
    }
    file.close();
}