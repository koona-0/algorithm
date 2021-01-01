/*
Shortest Path Problem
동적 프로그래밍과 Dijkstra 알고리즘을 각각 프로그래밍 한다.
그래프 노드 수 변화에 따른 두 알고리즘의 실제 수행 시간을 측정하고 비교한다.
그래프의 노드 수, 가중치 등은 스스로 결정하여 실험한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define INF 99999

void printArr(int n, int **arr) {
  printf("\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d\t", arr[i][j]);
    }
    printf("\n");
  }
}

void floyd(int n, int **W, int **D, int **P) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      P[i][j] = -1;
      D[i][j] = W[i][j];
    }
  }

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if ((D[i][k] + D[k][j]) < D[i][j]) {
          P[i][j] = k;
          D[i][j] = D[i][k] + D[k][j];
        }
}

void path(int **P, int q, int r) {
  if (P[q][r] == -1) {
    return;
  } else {
    path(P, q, P[q][r]);
    printf("v%d -> ", P[q][r] + 1);
    path(P, P[q][r], r);
  }
}

int *Dijkstra(int n, int **W, int F[]) {
  int i, vnear = 0;
  int min;
  int cost;
  int *touch;
  int *length;
  touch = malloc(sizeof(int) * n);
  length = malloc(sizeof(int) * n);

  for (i = 1; i < n; i++) {
    touch[i] = 0;
    length[i] = W[0][i];
  }

  for (int k = 0; k < n - 1; k++) {
    min = INF;
    for (i = 1; i < n; i++) {
      if (length[i] >= 0 && length[i] < min) {
        min = length[i];
        vnear = i;
      }
    }

    cost = length[vnear];
    F[vnear - 1] = cost;

    for (i = 1; i < n; i++)
      if (length[vnear] + W[vnear][i] < length[i]) {
        length[i] = length[vnear] + W[vnear][i];
        touch[i] = vnear;
      }
    length[vnear] = -1;
  }

  free(touch);
  free(length);

  return F;
}

int main() {
  int n = 0;
  // int start_node = 0, end_node = 0;
  int **W;  // 가중치
  int **D;  // 최단경로 길이
  int **P;  // 최단경로
  int *F = {0};
  int *weight = {0};
  clock_t start = 0;
  clock_t end = 0;

  printf("n : ");
  scanf("%d", &n);

  // 동적 할당
  srand(time(NULL));

  W = malloc(sizeof(int *) * n);
  D = malloc(sizeof(int *) * n);
  P = malloc(sizeof(int *) * n);
  weight = malloc(sizeof(int) * n);
  F = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    W[i] = malloc(sizeof(int) * n);
    D[i] = malloc(sizeof(int) * n);
    P[i] = malloc(sizeof(int) * n);
  }
  // 동적 할당 끝

  // 랜덤 값 할당 (범위 : 자기 자신 0, 1 ~ 9, INF)
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        W[i][j] = 0;
      } else {
        W[i][j] = (rand() % 10 + 1);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (W[i][j] == 10) {
        W[i][j] = INF;
      }
    }
  }
  // 가중치 할당 끝

  // printf("\nW[][]\n");
  // printArr(n, W);

  start = clock();
  floyd(n, W, D, P);
  end = clock();
  printf("DP Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);  //초 단위

  // printf("\nD[][]\n");
  // printArr(n, D);

  // printf("\nP[][]\n");
  // printArr(n, P);

  // DP 랜덤 길찾기
  // start_node = rand() % n;
  // end_node = rand() % n;
  // printf("v%d -> ", start_node + 1);
  // path(P, start_node, end_node);
  // printf("v%d", end_node + 1);

  // 다익스트라
  start = clock();
  *weight = *Dijkstra(n, W, F);
  end = clock();
  printf("Dijkstra Time: %lf\n",
         (double)(end - start) / CLOCKS_PER_SEC);  //초 단위

  // 동적 할당 해제
  for (int i = 0; i < n; i++) {
    free(W[i]);
    free(D[i]);
    free(P[i]);
  }
  free(W);
  free(D);
  free(P);
  free(weight);
  free(F);

  return 0;
}