/*
연쇄행렬곱셈
무작정 알고리즘과 동적 계획법 알고리즘을 각각 프로그래밍 한다.
행렬 차원의 변화에 따른 두 알고리즘의 실제 실행시간을 측정하고 비교한다.
행렬은 스스로 생성하며, 차원도 스스로 결정하여 실험한다.
*/
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int mulBF(int i, int j, int d[]) {
  int count = 0;
  int min = INT_MAX;

  if (i == j) return 0;

  for (int k = i; k < j; k++) {
    count = mulBF(i, k, d) + mulBF(k + 1, j, d) + d[i - 1] * d[k] * d[j];
    if (count < min) min = count;
  }

  return min;
}

int mulDP(int n, int d[]) {
  int i, j, M[n + 1][n + 1];  // M : 최소 곱셈 수

  for (i = 0; i <= n; i++) {
    for (j = 0; j <= n; j++) {
      if (i == j)
        M[i][j] = 0;
      else
        M[i][j] = INT_MAX;
    }
  }

  for (int diagonal = 0; diagonal < n; diagonal++) {
    for (i = 1; i <= n - diagonal; i++) {  // 행
      j = i + diagonal;                    // 열
      for (int k = i; k <= j - 1; k++) {   // i <= k <= j - 1
        M[i][j] = MIN(M[i][j], M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j]);
      }
    }
  }

  // M 배열 확인띠
  // printf("\n\nM\n");
  // for (i = 1; i <= n; i++) {
  //   for (j = 1; j <= n; j++) {
  //     printf("%d\t", M[i][j]);
  //   }
  //   printf("\n");
  // }
  //

  return M[1][n];
}

int main() {
  int n = 0;   // 곱할 행렬의 수
  int *d = 0;  // d[i-1] * d[i] : i번째 행렬의 규모
  clock_t start = 0;
  clock_t end = 0;

  printf("n : ");
  scanf("%d", &n);

  srand(time(NULL));
  d = malloc(sizeof(int) * (n + 1));

  for (int i = 0; i <= n; ++i) {  // 1 ~ 10
    d[i] = (rand() % 10 + 1);
    // printf("%d\t", d[i]);
  }

  start = clock();
  printf("\nBF : %d\n", mulBF(1, n, d));
  end = clock();
  printf("BF Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);  //초 단위

  start = clock();
  printf("\nDP : %d\n", mulDP(n, d));
  end = clock();
  printf("DP Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);  //초 단위

  free(d);

  return 0;
}