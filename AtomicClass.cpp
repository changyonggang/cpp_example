//
// Created by 常永刚 on 2021/11/12.
//
#include <stdio.h>
#include <unistd.h>
#include "AtomicClass.h"

using namespace std;

bool AtomicClass::AcquireExclusiveLock() {
    bool acquired_lock = false;
    return exclusive_lock_.compare_exchange_strong(acquired_lock, true);
}

void AtomicClass::ReleaseExclusiveLock() {
    bool acquired_lock = true;
    exclusive_lock_.compare_exchange_strong(acquired_lock, false);
}

void* AtomicClass::Clone(void* args) {
    printf("clone start ...");
    sleep(10 * 1000);
    printf("clone end ...");

    return 0;
}

void* AtomicClass::LoadBalance(void* args) {
    printf("LoadBalance start ...");
    sleep(20 * 1000);
    printf("LoadBalance end ...");
    return 0;
}