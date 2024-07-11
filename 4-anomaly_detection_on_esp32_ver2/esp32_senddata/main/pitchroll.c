#include <math.h>
#include "pitchroll.h"
float get_pitch(float ax, float ay, float az){
    return atan2(ay,sqrt(ax*ax+az*az));
}
float get_roll(float ax, float ay, float az){
    return atan2(ax,sqrt(ay*ay+az*az));
}