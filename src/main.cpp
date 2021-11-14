#include "mult_thread/mult_thread.cpp"
#include "utils/static_var.cpp"
#include "atomic_module/AtomicClass.h"

using namespace std;

int main() {
    thread_run();

    run_thread_id();

    auto ac = new AtomicClass();
    ac->Clone();
    return 0;
}



