#include "minmaxscaler.h"
static float min[8] = {0.66223519 ,0.76072856 ,0.65273372 ,0.61111111, 0.59532374, 0.49964539, 0.50183961, 0.51558958};
static float scale[8] = {1.07132962 , 1.65911217 ,10.69150579  ,2.77777778 , 1.79856115,  0.35460993, 0.32241303,  0.33680666};
void minmax_scale(float* arr){
    for(int i=0;i<8;++i){
        arr[i] = arr[i] * scale[i] + min[i];
    }
}
void minmax_scale_revert(float* arr){
    for(int i=0;i<8;++i){
        arr[i] = (arr[i] - min[i])/scale[i];
    }
}