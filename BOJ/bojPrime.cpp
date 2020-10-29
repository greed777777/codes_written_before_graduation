#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX = 1000000;
bool prime[MAX + 1];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    prime[1] = true;
    for (int i = 2; i * i <= MAX; i++) {
        if (!prime[i]) {
            for (int j = (i * i) % MAX; j <= MAX; j += i) {
                prime[j] = true;
            }
        }
    }
    for (int i = m; i <= n; i++) {
        if (!prime[i]) printf("%d\n", i);
    }
    return 0;
}