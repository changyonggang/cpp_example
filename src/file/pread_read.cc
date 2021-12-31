/*
 * Copyright (c) 2015 KingSoft.com, Inc. All Rights Reserved
 *
 * @file pread_read.cc
 * @author changyonggang(changyonggang@kingsoft.com)
 * @date 11/23/21 11:10 AM
 * @brief
 *
*/
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <memory.h>

using namespace std;
#define BUFFSIZE 20

//read.txt -> 123456

void preadTest(int fd) {
    char buf[BUFFSIZE];
    memset(&buf, 0, 0);
    cout << "pread" << endl;
    pread(fd, buf, 3, 2);
    cout << buf << endl;

//  memset(&buf,0,0);
    read(fd, buf, 3);
    cout << buf << endl;
}

void readTest(int fd) {
    char buf[BUFFSIZE];
    cout << "read" << endl;
    read(fd, buf, 3);
    cout << buf << endl;

//  memset(&buf,0,0);
    read(fd, buf, 3);
    cout << buf << endl;
}

int pread_main() {
    int fd;
    fd = open("./data/read.txt", O_RDWR);
    preadTest(fd);
//    readTest(fd);
    return 0;
}
