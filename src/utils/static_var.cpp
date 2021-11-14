//
// Created by 常永刚 on 2021/11/12.
//
#include <iostream>

int ThreadId() {
    static int scheduler_id = 0;
    static int zookeeper_id = 0;
    static int service_id = 0;

    printf("scheduler_id : %d\n", scheduler_id++);
    printf("zookeeper_id : %d\n", zookeeper_id++);
    printf("service_id : %d\n", service_id++);
}

void run_thread_id() {
    std::cout << "Hello, World!" << std::endl;
    for (int i = 0; i < 10; ++i) {
        printf("loop start ...");
        ThreadId();
    }
}