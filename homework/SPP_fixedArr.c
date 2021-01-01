/*
Shortest Path Problem
동적 프로그래밍과 Dijkstra 알고리즘을 각각 프로그래밍 한다.
그래프 노드 수 변화에 따른 두 알고리즘의 실제 수행 시간을 측정하고 비교한다.
그래프의 노드 수, 가중치 등은 스스로 결정하여 실험한다.
*/

// **************************** 일단 고정된거로 계산 잘 되는지 확인 ****************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX 99999

void floyd(int n, int (*W)[5], int (*D)[5], int (*P)[5]) {
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

void path(int (*P)[5], int q, int r){
  if (P[q][r] == -1){
    return;
  }
	else{
		path(P, q, P[q][r]);
    printf("v%d ",P[q][r]+1);
		path(P, P[q][r], r);
	}
}


int main() {
  int n = 5;
  int W[5][5] = {{0, 1, MAX, 1, 5},
                 {9, 0, 3, 2, MAX},
                 {MAX, MAX, 0, 4, MAX},
                 {MAX, MAX, 2, 0, 3},
                 {3, MAX, MAX, MAX, 0}};  // 가중치
  int D[5][5] = {0};                      // 최단경로 길이
  int P[5][5] = {0};                      // 최단경로

  printf("\nW[][]\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d\t", W[i][j]);
    }
    printf("\n");
  }

  floyd(n, W, D, P);

  printf("\nD[][]\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d\t", D[i][j]);
    }
    printf("\n");
  }

printf("\nP[][]\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d\t", P[i][j]);
    }
    printf("\n");
  }
  
  path(P, 4, 2);

  return 0;
}