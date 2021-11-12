//
// Created by 常永刚 on 2021/11/12.
//

#ifndef CPP_EXAMPLE_ATOMICCLASS_H
#define CPP_EXAMPLE_ATOMICCLASS_H


#include <atomic>

class AtomicClass {
private:
    std::atomic<bool> exclusive_lock_;
public:
    bool AcquireExclusiveLock();
    void ReleaseExclusiveLock();

    static void* Clone(void* args);
    static void* LoadBalance(void* args);
};


#endif //CPP_EXAMPLE_ATOMICCLASS_H
