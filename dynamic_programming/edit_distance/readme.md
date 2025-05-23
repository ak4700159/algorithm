# 편집 연산의 수를 최소화 시키는 알고리즘
사용되는 연산
1. insert
2. remove
3. replace

        <Edit Distance>
        Input : string S and T, |S|=m, |T|=n
        Output : Edit distance of S and T, E[m,n]
        1. for i=0 to m E[i,0]=i
        2. for j=0 to n E[0,j]=j
        3. for i=1 to m
        4. for j=1 to n
        5. E[i,j] = min{E[i,j-1]+1, E[i-1,j]+1, E[i-1,j-1]+α}
        6. return E[m,n]

