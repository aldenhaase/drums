 #include"cam.h"
 #include"process.h" 
 #include"disp.h" 
 //#include"sound.h"
 //#include"jack/jack.h"
 //#include"pthread.h"
 //#include"alsa.h"
 #include<chrono>
 #include"midi.h"
int fd;

 int main(){
   int iterations = 3000;
   cam camera; 
  disp display;
   int num_blobs = 3;
   blob blobs[num_blobs];
   int offset = 0;
   for(int i = 0; i < num_blobs; i++){ 
      blobs[i].offset = offset;
      offset += 213;
   }
   camera.q();
  midi mid;
  setRef(camera, blobs, num_blobs); 
  setNoise(camera, blobs, num_blobs);
  auto start = std::chrono::high_resolution_clock::now();
  int flag = 0;
    for(int i =0; i < iterations; i++){   
      if(i%2 == 0){
       flag = 0; 
      }else{
        flag = 1;
      }
    process(camera, flag,blobs, num_blobs, mid);
 //   display.sendFrame(camera, flag); 
    
if(flag){
 camera.q1(0);
}else{
    camera.q1(1);

}

   }
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> ms_double = end - start;
   std::cout<<(ms_double.count()/iterations);
         return EXIT_SUCCESS;
 }
 
               
