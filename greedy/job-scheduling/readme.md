# Job Scheduling vs Task Scheduling
Job Scheduling은 Job의 시작 시간과 끝 시간을 알려준다. 그래서 전체 작업 시간을 알 수 있다. 작업의 수행 시간이 중복되지 않도록 모든 작업을 가장 적은 수의 기계에 배정하는 문제 

Task Scheduling은 작업 시간만 주고 효과적으로 스케줄링하는 것이다. 가장 최적의 답을 찾는 것 뿐이다. 정답이 없는 문제다.


## 전략
▪ 빠른 시작시간 작업 우선 (Earliest start time first) 배정

▪ 빠른 종료시간 작업 우선 (Earliest finish time first) 배정

▪ 짧은 작업 우선 (Shortest job first) 배정

▪ 긴 작업 우선 (Longest job first) 배정

## 의사코드

    Input : T = {t1, t2, ⋯, tn}, starting time, ending time
    Output : Task Schedule for Each Machine
    1. L = Sorted T in the ascending order of staring time
    2. M = { }
    3. while ( L ≠ ∅ ) {
    4. ti =L[0]
    5. if (isRunnable(ti,m) for m in M)
    6. m = m U {ti}
    7. else
    8. m’ = m U {ti}
    9. M = M U m’
    10. L = L\ti}
    11. return M

## 시간 복잡도
정렬하는데 n * logn 

비교하는데 worst case = m * n

= O(n * logn) + O(n * m) 