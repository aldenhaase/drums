

#include"cam.h"

cam::cam(){

        if((fd = open("/dev/video0", O_RDWR))<0){
                 perror("open");
                 exit(1);
         }

       if(ioctl(fd,VIDIOC_QUERYCAP, &cap)<0){
                 perror("VIDIOC_QUERYCAP");
                 exit(1);
         }
 
 
         if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)){
                 std::cout<<"boo";
                 exit(1);
         }
        if(!(cap.capabilities & V4L2_CAP_STREAMING)){
                 std::cout<<"boo";
                 exit(1);
         }
        format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        format.fmt.pix.pixelformat = V4L2_PIX_FMT_Y12;
        format.fmt.pix.width = 640;
        format.fmt.pix.height = 480;

        v4l2_streamparm parm;
        parm.type = format.type;

        parm.parm.capture.timeperframe.numerator = 1;
        parm.parm.capture.timeperframe.denominator = 90;
        int ret = ioctl(fd, VIDIOC_S_PARM, &parm);

        std::cout<<ret;

/*
        struct v4l2_control control;
        control.id = V4L2_CID_VBLANK;
        control.value = 10000;
       if(!( ioctl(fd, VIDIOC_S_CTRL, &control))){
            exit(1);
           }

*/ 
        if(ioctl(fd, VIDIOC_S_FMT, &format) < 0){
                perror("VIDIOC_S_FMT");
                exit(1);
        }

        bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        bufrequest.memory = V4L2_MEMORY_MMAP;
        bufrequest.count =2;
 
        if(ioctl(fd, VIDIOC_REQBUFS, &bufrequest) < 0){
         perror("VIDIOC_REQBUFS");
         exit(1);
        }

        buffers = (struct bb*)calloc(bufrequest.count, sizeof(bb)); 
        if(buffers == NULL){
        std::cout<< "buffer didnt calloc" << std::endl;
        }
        for(unsigned i = 0; i < bufrequest.count;i++){
            memset(&barr[i], 0, sizeof(barr[i]));
            barr[i].type = bufrequest.type;
            barr[i].memory = V4L2_MEMORY_MMAP;
            barr[i].index = i;

	          if (-1 == ioctl (fd, VIDIOC_QUERYBUF, &barr[i])) {
	          	perror ("VIDIOC_QUERYBUF");
	          	exit (EXIT_FAILURE);
	          }


            //buffers[i].length = buffer.length;
          	buffer_start[i] = mmap (NULL, barr[i].length,
          				 PROT_READ | PROT_WRITE, /* recommended */
          				 MAP_SHARED,             /* recommended */
          				 fd, barr[i].m.offset);
          
          	if (MAP_FAILED == buffer_start[i]) {
                  		perror ("mmap");
          		exit (EXIT_FAILURE);
                  }
            memset(buffer_start[i], 0, barr[i].length);
        }
      // type = bufferinfo.type;
      
      type = bufrequest.type; 
       if(ioctl(fd, VIDIOC_STREAMON, &type) < 0){
            perror("VIDIOC_STREAMON");
            exit(1);
        }



}

int cam::q(){

  for(unsigned i = 0; i< bufrequest.count; i ++){
         if(ioctl(fd, VIDIOC_QBUF, &barr[i]) < 0){
            perror("VIDIOC_QBUF");
            exit(1);
        }

  }
return 0;
}

void cam::q1(int index){
   if(ioctl(fd, VIDIOC_QBUF, &barr[index]) < 0){
            perror("VIDIOC_QBUF");
            exit(1);
        }

}

int cam::dq(){
       // The buffer's waiting in the outgoing queue.
       for(unsigned i = 0; i < bufrequest.count; i++){
        if(ioctl(fd, VIDIOC_DQBUF, &barr[i]) < 0){
            perror("VIDIOC_QBUF");
            exit(1);
        }
       }
         
  
return 0;
}

void cam::dq1(int index){
        if(ioctl(fd, VIDIOC_DQBUF, &barr[index]) < 0){
            perror("VIDIOC_QBUF");
            exit(1);
        }

}

int cam::getstride(){
return format.fmt.pix.bytesperline;
}

void* cam::getstart(int index){
  return buffer_start[index];
}
void* cam::getstart2(int index){
  return buffer_start[index];
}

__u32 cam::getlength(){
  return barr[1].length;
}

int cam::getfd(){
  return fd;  
}
v4l2_buffer& cam::getbuffinfo(){
  return barr[0];
}
int& cam::getType(){
  return type;
}
cam::~cam(){

     if(ioctl(fd, VIDIOC_STREAMOFF, &type) < 0){
            perror("VIDIOC_STREAMOFF");
            exit(1);
        }
for (unsigned i = 0; i < bufrequest.count; i++)
	munmap (buffers[i].start, buffers[i].length);

  close(fd);
}


