//
// Created by 常永刚 on 2021/11/14.
//

#include "threadpool.h"
#include <iostream>

void fun1(int slp) {
    printf("hello, fun1 ! thread_id %d \n", std::this_thread::get_id());
    if (slp > 0) {
        printf(" ======= fun1 sleep %d  ========= sub_thread_id  %d\n", slp, std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::milliseconds(slp));
    }
}

struct gfun {
    int operator()(int n) {
        printf("%d  hello, gfun ! thread_id %d\n", n, std::this_thread::get_id());
        return 42;
    }
};

class Param {
public:
    Param(int value = -1) : value_(value), exclusive_lock_(false) {};

private:
    atomic<bool> exclusive_lock_;
    int value_;

public:
    void increase(){
        value_++;
    }
    int value() { return value_; }
    bool AcquireExclusiveLock() {
        bool acquired_lock = false;
        return exclusive_lock_.compare_exchange_strong(acquired_lock, true);
    }

    void ReleaseExclusiveLock() {
        bool acquired_lock = true;
        exclusive_lock_.compare_exchange_strong(acquired_lock, false);
    }

};


class A {

public:
    // 函数必须是 static 的才能直接使用线程池
    static int Afun(int n = 0) {
        printf("%d, hello, Afun ! thread_id %d\n", n, std::this_thread::get_id());
        return n;
    }

    static std::string Bfun(int n, std::string str, char c) {
        printf("%d hello, Bfun !%s %d thread_id %d \n", n, str.c_str(), (int) c, std::this_thread::get_id());
        return str;
    }

    static int Cfun(int n = 0) {
        printf("%d, hello, Cfun ! thread_id %d\n", n, std::this_thread::get_id());
        this_thread::sleep_for(chrono::seconds(n));
        return n;
    }

    static int Dfun(Param* p) {
        while (!p->AcquireExclusiveLock()) {
            printf("sleep no lock Dfun value %d\n", p->value());
            this_thread::sleep_for(chrono::seconds(1));
        }
        p->increase();
        printf("%d, hello, Dfun ! thread_id %d\n", p->value(), std::this_thread::get_id());
        this_thread::sleep_for(chrono::seconds(p->value()));
        auto ret = p->value();
        p->ReleaseExclusiveLock();
        return ret;
    }

    static int Efun(Param* p) {
        while (!p->AcquireExclusiveLock()) {
            printf("sleep no lock Efun value %d\n", p->value());
            this_thread::sleep_for(chrono::seconds(1));
        }

        p->increase();
        printf("%d, hello, Efun ! thread_id %d\n", p->value(), std::this_thread::get_id());
        this_thread::sleep_for(chrono::seconds(p->value()));
        auto ret = p->value();
        p->ReleaseExclusiveLock();
        return ret;
    }
};

void unit_test_1() {
    std::threadpool pool(4);
    std::vector<std::future<int> > results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
                pool.commit([i] {
                    printf("hello %d\n", i);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    printf("world %d\n", i);
                    return i * i;
                })
        );
    }
    printf(" =======  commit 8 tasks ========= %d \n", std::this_thread::get_id());

    // 观察一下，该句注释与否，返回值是不一样的！
    std::this_thread::sleep_for(std::chrono::seconds(10));
    for (auto &&result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
}

void unit_test_2() {

    std::threadpool executor{50};
    A a;
    // 支持 普通函数
    std::future<void> ff = executor.commit(fun1, 0);
    // 支持 struct 中重构的operator ()
    std::future<int> fg = executor.commit(gfun{}, 0);
    // 支持 类中的static函数
    std::future<int> gg = executor.commit(a.Afun, 9999);
    std::future<std::string> gh = executor.commit(A::Bfun, 9998, "mult args", 123);
    // support lambd 表达式
    std::future<std::string> fh = executor.commit([]() -> std::string {
        printf("hello, fh !  thread_id %d \n", std::this_thread::get_id());
        return "hello,fh ret !";
    });

    printf("======= sleep ========= main_thread \n");
    std::this_thread::sleep_for(std::chrono::microseconds(900));

    for (int i = 0; i < 50; i++) {
        executor.commit(fun1, i * 100);
    }
    printf("=======  commit all ========= idlsize= %s \n", executor.idlCount());

    printf("======= sleep ========= main_thread \n");
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // 调用.get()获取返回值会等待线程执行完,获取返回值
    ff.get();
    std::cout << fg.get() << "  " << fh.get().c_str() << "  " << std::this_thread::get_id() << std::endl;

    std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << " =======  fun1,55 ========= " << std::this_thread::get_id() << std::endl;
    executor.commit(fun1, 55).get();    // 调用.get()获取返回值会等待线程执行完

    std::cout << "end... " << std::this_thread::get_id() << std::endl;

}

void unit_test3() {
    std::threadpool pool(4);
    A a;
    std::future<int> gg = pool.commit(a.Afun, 5);
    printf("get result %d\n", gg.get());
}

void unit_test_4() {
    std::threadpool pool{4};
    std::vector<std::future<int>> results;
    Param* p = new Param(1);
    A a;
    for (int i = 0; i < 4; ++i) {
        results.emplace_back(pool.commit(a.Dfun, p));
        results.emplace_back(pool.commit(a.Efun, p));
    }

    std::this_thread::sleep_for(std::chrono::seconds(60));
    for (auto &&result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
}

int run_threadpool_main()
try {
//    unit_test_1();
//    unit_test_2();
//    unit_test3();
    unit_test_4();
    return 0;
}
catch (std::exception &e) {
    std::cout << "some unhappy happened...  " << std::this_thread::get_id() << e.what() << std::endl;
}
