## Quick Sort 특징
1. 하나를 문제를 두개로 나눈다. 단, 나눠진 사이즈는 일정하지 않다다(가변성).
2. 정렬 후 문제를 나눈다.

## Quick Sort 아이디어
1. 피봇이라 일컫는 배열의 원소를 선정
2. 피봇보다 작은 숫자들은 왼쪽, 피봇보다 큰 숫자들은 오른쪽에 위치하도록 분할


## Quick Sort 의사코드
### 함수 : QuickSort(A, left, right)
### 입력 : 정렬되지 않은 배열
### 출력 : 정렬된 배열
### 어떻게 반복 : 피봇을 중심으로 좌우를 계속가른다.
    if(left < right>) {

        **효과적으로 Sorting 하는 방식에 대해 알아야됨**

    }
    QuickSort(A, left, p-1)
    QuickSort(A, p+1, right)


## Sorting 방식
피봇을 기준으로 왼쪽에 어떤 요소가 오른쪽엔 어떤 요소가 들어갈지 탐색하며 피봇이 들어가야될 위치를 구한다.
1. Linear search -> 효율적이지 않음
2. key search -> 피봇을 기준으로 왼쪽엔 피봇보다 작은 값, 오른쪽엔 피봇보다 큰 값으로 정렬(정확한 순서는 고려 X)

### Sorting 방식 -> key search 방식
- 피봇 선정 방식이 중요
    1. 아무 피봇? 맨왼쪽 인덱스나 맨오른쪽 인덱스로 선정된다면
    ? -> 맨오른쪽, 맨왼쪽에서부터 비교 시작 -> O( n long n)
    2. 배열 가운데 있는 아무 요소로 선정(랜덤)
    3. 정확하게 중간값 선정
    4. 맨왼쪽 맨오른쪽 중간을 샘플링해서 중간에 있는 값으로 피봇 선정(Approximately sampling)


- 비교가 끝나는 시점

        피봇 = left(피봇을 맨좌측을 선정한 경우)
        i = left + 1, j = right
        if( (left - right) < 2 ) return
        while(j < i && 피봇 > i && 피봇 < j>) 

- 성능 최적화
    1. 분할되는 문제의 입력값이 n-1로 떨어지면 -> worst case
    2. O(log n) 성능이 제일 효율적 -> best case

## Quick Sorting 사용이유
입력크기가 클 때 유용해진다.