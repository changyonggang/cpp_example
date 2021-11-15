#include "mult_thread/mult_thread.cpp"
#include "utils/static_var.cpp"
//#include "atomic_module/AtomicClass.h"
#include "mult_thread/threadpool_run.cpp"

using namespace std;

int main() {
//    thread_run();

//    run_thread_id();

//    auto ac = new AtomicClass();
//    ac->Clone();

    run_threadpool_main();
    return 0;
}



