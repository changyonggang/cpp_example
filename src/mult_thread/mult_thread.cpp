//
// Created by 常永刚 on 2021/11/12.
//
#include <pthread.h>
#include <iostream>

#define NUM_THREADS 5
using namespace std;

// https://www.runoob.com/cplusplus/cpp-multithreading.html

void *PrintHello(void *threadid) {
    // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
    int tid = *((int *) threadid);
    cout << "Hello Runoob! 线程 ID, " << tid << endl;
    pthread_exit(NULL);
}

int thread_run() {
    pthread_t threads[NUM_THREADS];
    int indexes[NUM_THREADS];// 用数组来保存i的值
    int rc;
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        cout << "main() : 创建线程, " << i << endl;
        indexes[i] = i; // 先保存i的值
        // 传入的时候必须强制转换为void* 类型，即无类型指针
        rc = pthread_create(&threads[i], NULL,
                            PrintHello, (void *) &(indexes[i]));
        if (rc) {
            cout << "Error:无法创建线程," << rc << endl;
            exit(-1);
        }
    }
    // exit thread
    pthread_exit(NULL);
}