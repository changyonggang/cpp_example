#include <iostream>
#include <pthread.h>
#include "AtomicClass.h"
using namespace std;

int ThreadId(){
    static int scheduler_id = 0;
    static int zookeeper_id = 0;
    static int service_id = 0;

    printf("scheduler_id : %d\n", scheduler_id++);
    printf("zookeeper_id : %d\n", zookeeper_id++);
    printf("service_id : %d\n", service_id++);
}

//int main() {
////    std::cout << "Hello, World!" << std::endl;
////    for (int i = 0; i < 10; ++i) {
////        printf("loop start ...");
////        ThreadId();
////    }
//
//    auto ac = new AtomicClass();
//    pthread_t tids[8];
//    for(int i = 0; i < 8; ++i)
//    {
//        printf("loop ...");
//        int ret = -1;
//        if (i%2) {
//            // 参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
//            ret = pthread_create(&tids[i], NULL, ac->Clone, NULL);
//        } else {
//            ret = pthread_create(&tids[i], NULL, ac->LoadBalance, NULL);
//        }
//
//        if (ret != 0)
//        {
//            cout << "pthread_create error: error_code=" << ret << endl;
//        }
//    }
//    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
//    pthread_exit(NULL);
//    return 0;
//}



#define NUM_THREADS     5

void *PrintHello(void *threadid)
{
    // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
    int tid = *((int*)threadid);
    cout << "Hello Runoob! 线程 ID, " << tid << endl;
    pthread_exit(NULL);
}

int main ()
{
    pthread_t threads[NUM_THREADS];
    int indexes[NUM_THREADS];// 用数组来保存i的值
    int rc;
    int i;
    for( i=0; i < NUM_THREADS; i++ ){
        cout << "main() : 创建线程, " << i << endl;
        indexes[i] = i; //先保存i的值
        // 传入的时候必须强制转换为void* 类型，即无类型指针
        rc = pthread_create(&threads[i], NULL,
                            PrintHello, (void *)&(indexes[i]));
        if (rc){
            cout << "Error:无法创建线程," << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}