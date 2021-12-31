/*
 * Copyright (c) 2015 KingSoft.com, Inc. All Rights Reserved
 *
 * @file time.cc
 * @author changyonggang(changyonggang@kingsoft.com)
 * @date 2021/12/10 11:32 AM
 * @brief
 *
*/

#include <cstdint>
#include <ctime>
#include <iostream>
#include <chrono>
using namespace std;

void print_time() {
    int64_t t1, t2;
    int idx = 0;
    while (idx < 10) {
        t1 = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        t2 = time(nullptr);
        printf("t1 %lld \n", t1);
        printf("t2 %lld \n", t2);
        idx++;
    }
}
