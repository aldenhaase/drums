
#include"cam.h"
#include"midi.h"
#include<iostream>
#ifndef PROC_H
#define PROC_H

class blob{
  public:
  int weight;
  int debounce;
  float denoise;
  float noise_mask[21300] = {0};
  char ref[21300] = {0};
  int offset;
  blob() :
    weight(0), debounce(0), denoise(0), offset(0){}
};

void process(cam& camera, int flag, blob blobs[], int num_blobs, midi& mid);
void setRef(cam& camera, blob blobs[], int num_blobs);
void setNoise(cam& camera, blob blobs[], int num_blobs);
#endif
