// Bit matrix multiplication - count rowsize sum
// Ref) https://www.acmicpc.net/problem/8907
vector<bitset<1000>> matx(N);
for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
        if (i != j && matx[i][j]) {
            auto mul = matx[i] & matx[j];
            res += mul.count();
        }
    }
}
