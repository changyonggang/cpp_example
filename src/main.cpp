//#include "mult_thread/mult_thread.cpp"
//#include "utils/static_var.cpp"
////#include "atomic_module/AtomicClass.h"
//#include "mult_thread/threadpool_run.cpp"
//#include "file/pread_read.cc"
//#include "file/pwrite_write.cc"
//#include "utils/time.cpp"

#include <string>

//#pragma pack(4)
// cpu 32 则 4byte 对齐，64位则 8byte 对齐
struct Page {
    std::string key;
    std::shared_ptr<std::string> value;
    uint32_t blockid;
    uint32_t off;
    uint32_t size;
};

//#pragma pack(4)
struct PageNew {
    std::string key;
    std::shared_ptr<std::string> value;
    uint32_t blockid;
    uint32_t off;
    uint32_t size;
    uint32_t crc;
};

int main() {
//    thread_run();

//    run_thread_id();

//    auto ac = new AtomicClass();
//    ac->Clone();

//    run_threadpool_main();

//    pread_main();
//    pwrite_main();
//    printf("中文打印\n");
//    print_time();
    Page* p = new Page{};
    p->key = "chang";
    printf("p size %lu \n", sizeof (*p));
    printf("p crc %u", p->blockid);
    printf("page size %lu \n", sizeof (Page));
    printf("PageNew (add crc) size %lu \n", sizeof (PageNew));
    printf("string size %lu \n", sizeof (std::string));
    printf("uint32_t size %lu \n", sizeof (uint32_t));

    printf("std::shared_ptr<std::string> size %lu \n", sizeof (std::shared_ptr<std::string>));
    return 0;
}



