/*
행렬 곱셈 비교
행렬 곱셈을 수행하는 단순 알고리즘과 쉬트라센 알고리즘을 각각 프로그래밍
64x64 행렬의 곱셈 수행 결과를 확인하고, 두 방법의 실제 곱셈 횟수를 비교
256x256 행렬의 곱셈 수행 결과를 확인하고, 두 방법의 실제 곱셈 횟수를 비교
입력 행렬은 자신이 임의로 생성하여 사용
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mat_mul_cnt = 0;
int str_mul_cnt = 0;

//행렬에 랜덤 수 입력
void inputMat(int **m, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      m[i][j] = (rand() % (size * 10));  //값 할당
    }
  }
}

//행렬 출력
void outputMat(int **m, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d\t", m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

//단순 반복 곱셈
void matMul(int n, int **A, int **B, int **C) {
  int i, j, k = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      C[i][j] = 0;
      for (k = 0; k < n; k++) {
        C[i][j] += A[i][k] * B[k][j];
        mat_mul_cnt++;
      }
    }
  }
}

// strassen 곱셈
void strassen(int n, int **A, int **B, int **C) {
  int i, j = 0;
  int p, q = 0;

  if (n <= 1) {  //임계값 1로 설정.
    matMul(n, A, B, C);
    str_mul_cnt++;  //재귀 끝날 때마다 곱셈 카운트 증가
  } else {
    int mid = n / 2;  //크기는 반만 필요하므로 mid값 설정
    int **m1 = malloc(sizeof(int *) * mid);  //배열 동적할당
    int **m2 = malloc(sizeof(int *) * mid);
    int **m3 = malloc(sizeof(int *) * mid);
    int **m4 = malloc(sizeof(int *) * mid);
    int **m5 = malloc(sizeof(int *) * mid);
    int **m6 = malloc(sizeof(int *) * mid);
    int **m7 = malloc(sizeof(int *) * mid);
    int **temp1 = malloc(sizeof(int *) * mid);
    int **temp2 = malloc(sizeof(int *) * mid);

    for (q = 0; q < mid; q++) {  // 2차원 배열 동적할당
      m1[q] = malloc(sizeof(int *) * mid);
      m2[q] = malloc(sizeof(int *) * mid);
      m3[q] = malloc(sizeof(int *) * mid);
      m4[q] = malloc(sizeof(int *) * mid);
      m5[q] = malloc(sizeof(int *) * mid);
      m6[q] = malloc(sizeof(int *) * mid);
      m7[q] = malloc(sizeof(int *) * mid);
      temp1[q] = malloc(sizeof(int *) * mid);
      temp2[q] = malloc(sizeof(int *) * mid);
    }

    for (i = 0; i < mid; i++) {
      for (j = 0; j < mid; j++) {
        temp1[i][j] = 0;
        temp1[i][j] = A[i][j] + A[i + mid][j + mid];  // a11 + a22
        temp2[i][j] = B[i][j] + B[i + mid][j + mid];  // b11 + b22
      }
    }
    strassen(mid, temp1, temp2, m1);  // m1

    for (i = 0; i < mid; i++) {
      for (j = 0; j < mid; j++) {
        temp1[i][j] = A[i + mid][j] + A[i + mid][j + mid];  // a21 + a22
        temp2[i][j] = B[i][j];                              // b11
      }
    }
    strassen(mid, temp1, temp2, m2);  // m2

    for (i = 0; i < mid; i++) {
      for (j = 0; j < mid; j++) {
        temp1[i][j] = A[i][j];                              // a11
        temp2[i][j] = B[i][j + mid] - B[i + mid][j + mid];  // b12 - b22
      }
    }
    strassen(mid, temp1, temp2, m3);  // m3

    for (i = 0; i < mid; i++) {
      for (j = 0; j < mid; j++) {
        temp1[i][j] = A[i + mid][j + mid];      // a22
        temp2[i][j] = B[i + mid][j] - B[i][j];  // b21 - b11
      }
    }
    strassen(mid, temp1, temp2, m4);  // m4

    for (i = 0; i < mid; i++) {
      for (j = 0; j < mid; j++) {
        temp1[i][j] = A[i][j] + A[i][j + mid];  // a11 + a12
        temp2[i][j] = B[i + mid][j + mid];      // b22
      }
    }
    strassen(mid, temp1, temp2, m5);  // m5

    for (i = 0; i < mid; i++) {
      for (j = 0; j < mid; j++) {
        temp1[i][j] = A[i + mid][j] - A[i][j];  // a21 - a11
        temp2[i][j] = B[i][j] + B[i][j + mid];  // b11 + b12
      }
    }
    strassen(mid, temp1, temp2, m6);  // m6

    for (i = 0; i < mid; i++) {
      for (j = 0; j < mid; j++) {
        temp1[i][j] = A[i][j + mid] - A[i + mid][j + mid];  // a12 - a22
        temp2[i][j] = B[i + mid][j] + B[i + mid][j + mid];  // b21 + b22
      }
    }
    strassen(mid, temp1, temp2, m7);  // m7

    for (i = 0; i < mid; i++) {
      for (j = 0; j < mid; j++) {
        C[i][j] = m1[i][j] + m4[i][j] - m5[i][j] + m7[i][j];              // c11
        C[i][j + mid] = m3[i][j] + m5[i][j];                              // c12
        C[i + mid][j] = m2[i][j] + m4[i][j];                              // c21
        C[i + mid][j + mid] = m1[i][j] + m3[i][j] - m2[i][j] + m6[i][j];  // c22
      }
    }

    for (j = 0; j < mid; j++) {  // 동적 배열 해제
      free(m7[j]);
      free(m6[j]);
      free(m5[j]);
      free(m4[j]);
      free(m3[j]);
      free(m2[j]);
      free(m1[j]);
      free(temp2[j]);
      free(temp1[j]);
    }
    free(m7);
    free(m6);
    free(m5);
    free(m4);
    free(m3);
    free(m2);
    free(m1);
    free(temp2);
    free(temp1);
  }
}

int main(void) {
  int n;
  clock_t start = 0;
  clock_t end = 0;
  printf("Please enter the size of the matrix : ");
  scanf("%d", &n);
  srand(time(NULL));

  // 이중 포인터에 (int 포인터 크기 * n)만큼 동적 메모리 할당. 배열의 세로
  int **matrix1 = malloc(sizeof(int *) * n);
  int **matrix2 = malloc(sizeof(int *) * n);
  int **matrix3 = malloc(sizeof(int *) * n);

  for (int i = 0; i < n; i++) {  // 세로 크기만큼 반복
    // (int의 크기 * n)만큼 동적 메모리 할당. 배열의 가로
    matrix1[i] = malloc(sizeof(int) * n);
    matrix2[i] = malloc(sizeof(int) * n);
    matrix3[i] = malloc(sizeof(int) * n);
  }

  inputMat(matrix1, n);
  inputMat(matrix2, n);
  // outputMat(matrix1, n);
  // outputMat(matrix2, n);

  //단순 반복 곱셈
  start = clock();
  matMul(n, matrix1, matrix2, matrix3);
  end = clock();
  printf("Simple Multiplication Count : %d \n", mat_mul_cnt);
  printf("Simple Multiplication Time: %lf\n",
         (double)(end - start) / CLOCKS_PER_SEC);  //초 단위

  //슈트라센 곱셈
  start = clock();
  strassen(n, matrix1, matrix2, matrix3);
  end = clock();
  printf("Strassen Count : %d \n", str_mul_cnt);
  printf("Strassen Time: %lf\n",
         (double)(end - start) / CLOCKS_PER_SEC);  //초 단위

  // outputMat(matrix3, n);

  for (int i = 0; i < n; i++) {  // 세로 크기만큼 반복
    free(matrix1[i]);  // 2차원 배열의 가로 공간 메모리 해제
    free(matrix2[i]);
    free(matrix3[i]);
  }

  free(matrix1);  // 2차원 배열의 세로 공간 메모리 해제
  free(matrix2);
  free(matrix3);

  return 0;
}
