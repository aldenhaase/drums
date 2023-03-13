#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>
#include<sys/mman.h>
#include<sys/ioctl.h>
#include<linux/videodev2.h>

#ifndef CAM_H
#define CAM_H
class cam{
int fd;
struct v4l2_capability cap;
struct v4l2_format format;
struct v4l2_requestbuffers bufrequest;
struct v4l2_buffer bufferinfo;
struct v4l2_buffer barr[5];
struct bb{
        void* start;
        size_t length;
} *buffers;

void* buffer_start[5];
int type;

        public:
        cam();
        ~cam();
        void* getstart(int index);
        void* getstart2(int index);
        int getstride();
        __u32 getlength();
        int getfd();
        void q1(int);
        void dq1(int);
        v4l2_buffer& getbuffinfo();
        int& getType();
        int getFrame();
        int q();
        int dq();
};
#endif
