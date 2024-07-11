#include "minmaxscaler.h"
static float min[8] = {0.53552572 ,0.43903253 ,0.53470179, 0.52415995 ,0.40047341, 0.49226948,0.49511962 ,0.50342496};
static float scale[8] = {0.00718123, 0.03960096 ,0.03830409 ,3.89362613 ,1.71523645, 0.34542076,0.32582555, 0.33624183};
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
