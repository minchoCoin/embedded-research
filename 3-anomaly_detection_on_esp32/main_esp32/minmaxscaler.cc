#include "minmaxscaler.h"
static float min[8] = {0.44566611, 0.76919872, 0.6322389,  0.60612691, 0.82548109, 0.60107335,0.49998736, 0.48786925};
static float scale[8] = {0.3845948,  0.49740237 ,3.15106305, 2.18818381, 0.66357001 ,0.2555584 ,0.32877444, 0.34700859};
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