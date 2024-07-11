#include <cmath>
#include "pitchroll.h"
float get_pitch(float ax, float ay, float az){
    return (float)atan2(ay,sqrt(ax*ax+az*az));
}
float get_roll(float ax, float ay, float az){
    return (float)atan2(ax,sqrt(ay*ay+az*az));
}