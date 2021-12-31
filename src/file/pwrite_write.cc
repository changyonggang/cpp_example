/*
 * Copyright (c) 2015 KingSoft.com, Inc. All Rights Reserved
 *
 * @file pwrite_write.cc
 * @author changyonggang(changyonggang@kingsoft.com)
 * @date 11/23/21 11:10 AM
 * @brief
 *
*/

#include <unistd.h>
#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <fcntl.h>

using namespace std;

#define BUFFSIZE 20
char name[] = "HELLO WORLD";

void pwriteTest(int fd) {
    char buf[BUFFSIZE];
    pwrite(fd, name, 5, 0);

    read(fd, buf, 5);
    cout << buf << endl;
}

void writeTest(int fd) {
    char buf[BUFFSIZE];
    write(fd, name, 5);

    read(fd, buf, 5);
    cout << buf << endl;
}

int pwrite_main() {
    int fd;
    fd = open("./data/write.txt", O_RDWR);
    pwriteTest(fd);
//    writeTest(fd);
    return 0;
}
