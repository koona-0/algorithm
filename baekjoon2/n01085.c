/*
문제
한수는 지금 (x, y)에 있다. 직사각형의 왼쪽 아래 꼭짓점은 (0, 0)에 있고, 오른쪽
위 꼭짓점은 (w, h)에 있다. 직사각형의 경계선까지 가는 거리의 최솟값을 구하는
프로그램을 작성하시오. 입력 첫째 줄에 x, y, w, h가 주어진다. 출력 첫째 줄에
문제의 정답을 출력한다. 제한 1 ≤ w, h ≤ 1,000 1 ≤ x ≤ w-1 1 ≤ y ≤ h-1 x, y, w,
h는 정수
*/

#include <stdio.h>

int main() {
  int x, y, w, h;
  int min = 1000;

  scanf("%d %d %d %d", &x, &y, &w, &h);

  if (x < min) {
    min = x;
  }
  if (w - x < min) {
    min = w - x;
  }
  if (y < min) {
    min = y;
  }
  if (h - y < min) {
    min = h - y;
  }
  
  printf("%d", min);

  return 0;
}