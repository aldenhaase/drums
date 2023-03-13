#include"process.h"
//#include"sound.h"
//#include"alsa.h"


void setNoise(cam& camera, blob blobs[], int num_blobs){
int finished = 0;
int arr[num_blobs] ={0};
unsigned int width = 213;
unsigned int len = 21300;
int swtch = 0;
while(finished < num_blobs){

  camera.dq1(swtch);
  char* frame = (char*)camera.getstart(swtch);

 for(int i = 0; i < num_blobs; i++){  
    int index = 640 * 100 + blobs[i].offset;
    unsigned int clean = 0;
    for(unsigned int k = 0; k < len; k+=width){
        for(unsigned int x = 0; x < width; x++){
          if( /*frame1[index] > (ref[index]+ref[index] *0.2) &&*/
                frame[index] > (blobs[i].ref[k + x]+(blobs[i].noise_mask[k + x]))
                ){ 
              blobs[i].noise_mask[k + x] += 10;
              //blobs[i].weight++; 
         }else{
          clean++;
         }
        index++;
        }
    index += (640 - width);
    }
      if(clean == len){
        arr[i]++;
      }
      if(arr[i] > 2){
      finished ++;
    }
    }

camera.q1(swtch);
swtch = !swtch;
}
if(swtch){
  camera.dq1(swtch);
  camera.q1(swtch);
}
}

void setRef(cam& camera, blob blobs[], int num_blobs){
  unsigned int len = 21300;
  unsigned int width = 213;
      camera.dq1(0);
      char* frame = (char*)camera.getstart(0);
      for(int i = 0; i < num_blobs; i ++){
        int index = 640 * 100 + blobs[i].offset;
        for(unsigned int k = 0; k < len; k+=width){
          for(unsigned int x = 0; x < width; x++){
            blobs[i].ref[k + x] = frame[index];
            index++;
          }
          index += (640-width);
        }
      }
      camera.q1(0);
}




void process(cam& camera, int flag, blob blobs[], int num_blobs, midi& mid){
     // unsigned int width = 213; 
      //unsigned int len = 21300;
      char* frame;
      if(flag){
      camera.dq1(0);
      frame = (char*)camera.getstart(0);
   //   camera.dq1(1);
      }else{
        camera.dq1(1);
        frame = (char*)camera.getstart(1);
     // camera.dq1(2);
    //  camera.dq1(3);
      }
   int count = 0;
   for(int i = 0; i < num_blobs; i ++){
    int index = 640 * 100 + blobs[i].offset;
      unsigned int width = 213; 
      unsigned int len = 21300;
    for(unsigned int k = 0; k < len; k+=width){
        for(unsigned int x = 0; x < width; x++){

          if(frame[index] > (blobs[i].ref[k + x] + blobs[i].noise_mask[k + x])){
              count++;
            //  frame[index] = 200;
              //blobs[i].weight++; 
         }else{
         // frame[index] = 0;
          if(count > 0){
            count --;
          }
        }
        if(count > 20){
          blobs[i].weight++;
        }
        index++;
        }
    index +=(640-width);
    }
    if(blobs[i].weight > 50 && blobs[i].debounce  == 0){
//     std::cout<<"bloby boi"<<i<<std::endl;
     blobs[i].debounce = 8;
     mid.play(i);
   }else{
     if(blobs[i].debounce > 0){
      blobs[i].debounce--;
     }
     mid.stop(i);
   }
     blobs[i].weight = 0;
   }


    }

