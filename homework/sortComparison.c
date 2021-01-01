/*
정렬 알고리즘 성능 비교
버블정렬, 합병정렬, 빠른정렬 알고리즘
입력 개수를 달리하면서 실제 정렬 속도를 측정하고 비교
입력 숫자와 개수는 자신이 임의로 생성, 결정하여 사용
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//배열에 랜덤 수 할당 함수
void randomNumber(int arr[], int size){
    for(int i = 0; i < size; i++){
        arr[i] = (rand() % (size*10));    //배열에 값 할당
        //printf("%d\t",arr[i]);   //정렬 전 배열 확인
    }
    printf("\n");
}

//버블 정렬
void bubbleSort(int arr[], int size){    
    int temp;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size - 1; j++){
            if (arr[j] > arr[j + 1]){         // 현재 요소의 값과 다음 요소의 값을 비교하여
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;            // 큰 값을 다음 요소로 보냄
            }
        }
    }
}

//합병 정렬
void merge(int arr[], int p, int q, int r) {
    int i = p, j = q + 1, k = p;
    int tmp[r];    //임시 배열
    while (i <= q && j <= r) {
        if (arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }//한쪽이 끝날때까지 정렬. 그 후 다른 한쪽에서 남은 값들은 이미 정렬됐으므로 그대로 넣어주면 됨.
    while (i <= q)
        tmp[k++] = arr[i++];
    while (j <= r)
        tmp[k++] = arr[j++];
    for (int i = p; i <= r; i++) {
        arr[i] = tmp[i];
    }//합병한 값을 원래 배열에 넣어줌
}
 
void mergeSort(int arr[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(arr, p, q);//전반부 정렬
        mergeSort(arr, q + 1, r);//후반부 정렬
        merge(arr, p, q, r);//합병
    }
}

//퀵 정렬
void swap(int arr[], int a, int b) // a,b 스왑 함수 
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
int partition(int arr[], int left, int right)
{
    int pivot = arr[left]; // 피벗의 위치는 가장 왼쪽에서 시작
    int low = left + 1;
    int high = right;
 
    while (low <= high) // 교차되기 전까지 반복한다 
    {
        while (low <= right && pivot >= arr[low]) // 피벗보다 큰 값을 찾는 과정 
        {
            low++; // low를 오른쪽으로 이동 
        }
        while (high >= (left+1)  && pivot <= arr[high]) // 피벗보다 작은 값을 찾는 과정 
        {
            high--; // high를 왼쪽으로 이동
        }
        if (low <= high)// 교차되지 않은 상태이면 스왑 과정 실행 
        {
            swap(arr, low, high); //low와 high를 스왑 
        }
    }
    swap(arr, left, high); // 피벗과 high가 가리키는 대상을 교환 
    return high;  // 옮겨진 피벗의 위치정보를 반환 
 
}
void quickSort(int arr[], int left, int right)
{
    if (left <= right)
    {
        int pivot = partition(arr, left, right); // 둘로 나누어서
        quickSort(arr, left, pivot - 1); // 왼쪽 영역을 정렬한다.
        quickSort(arr, pivot + 1, right); // 오른쪽 영역을 정렬한다.
    }
}

int main(){
    int arrSize = 0;
    int *arrPtr = 0;
    clock_t start = 0;
    clock_t end = 0;

    srand(time(NULL));

    printf("Please enter the number of numbers to sort. : ");
    scanf("%d", &arrSize);

    arrPtr = (int*)malloc(sizeof(int) * arrSize); //배열 크기만큼 동적 할당

    //버블
    //printf("\nBefore bubbleSort \n");
    //randomNumber(arrPtr, arrSize);
    //start = clock();
    //bubbleSort(arrPtr, arrSize);
    //end = clock();
    //printf("After bubbleSort \n");
    //for(int i = 0; i < arrSize; i++)    printf("%d\t",arrPtr[i]);   //정렬 후 배열 확인
    //printf("\n");
    //printf("bubbleSort Time: %lf\n",(double)(end - start)/CLOCKS_PER_SEC); //초 단위

    //합병
    //printf("\nBefore mergeSort \n");
    randomNumber(arrPtr, arrSize);
    start = clock();
    mergeSort(arrPtr, 0, arrSize - 1);
    end = clock();
    //printf("After mergeSort \n");
    //for(int i = 0; i < arrSize; i++)    printf("%d\t",arrPtr[i]);   //정렬 후 배열 확인
    printf("\n");
    printf("mergeSort Time: %lf\n",(double)(end - start)/CLOCKS_PER_SEC); //초 단위

    //퀵
    //printf("\nBefore QuickSort \n");
    randomNumber(arrPtr, arrSize);
    start = clock();
    quickSort(arrPtr, 0, arrSize - 1);
    end = clock();
    //printf("After QuickSort \n");
    //for(int i = 0; i < arrSize; i++)    printf("%d\t",arrPtr[i]);   //정렬 후 배열 확인
    printf("\n");
    printf("quickSort Time: %lf\n",(double)(end - start)/CLOCKS_PER_SEC); //초 단위
    
    printf("\n\n");
    free(arrPtr);
    return 0;
}