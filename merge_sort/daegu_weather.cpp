#include <iostream>
#include <fstream>
#include <string>
#include "daegu_weather.h"
using namespace std;
 
// [p~m]/[m+1~q] 두 개의 블록에 대해 병합 -> 내림차순으로 정렬
void merge(DaeguWeather weathers[], DaeguWeather result[], int p, int q, int m) {
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
void merge_sort(DaeguWeather weathers[], DaeguWeather result[], int p, int q) {
    if(p < q) {
        int k = (p+q)/2;
        merge_sort(weathers, result, p, k);
        merge_sort(weathers, result, k+1, q);

        // 합병 진행 p ~ q 까지에 대해 비교 하면됨.
        merge(weathers, result, p, q, k);
    }
}

void printList(DaeguWeather weathers[], int len){
    cout << ("[INFO] ");
    for(int i = 0; i < len; i++) {
        cout << "[" << weathers[i].temperature << "|" << weathers[i].date << "]" << " -> " ;
    }
    cout << ("[END]") << endl;
}

void copyResultToList(DaeguWeather list[], DaeguWeather result[], int p, int q) {
    for(; p <= q; p++){
        list[p] = result[p];
    }
}

// 반환값으로 배열길이 반환
int setWeathers(DaeguWeather weathers[]) {
    ifstream file("daegu_weather_2024.txt");
    string line;
    int lines = 0;
    int capacity = 1;

    while (!file.eof()){
        getline(file, line);
        cout << line << endl;
        lines++;
        if(capacity < lines) {
            capacity *= 2;
            weathers = (DaeguWeather*)realloc(weathers, capacity * sizeof(DaeguWeather));
        }

        string date = line.substr(sizeof("0000-00-00"));
        int temperature = stoi(line.substr(line.find(" ")));
        weathers[lines] = DaeguWeather{
            date,
            temperature,
        };
    }

    file.close();
    return lines;
}