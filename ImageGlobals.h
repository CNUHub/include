// ========== File: ImageGlobals.h ==========

#include <math.h> 

const double DEG_TO_RAD = (M_PI/180.);  // Converts degrees to radians

struct tm *tmptr;

typedef struct 
{
   double x;
   double y;
   double z;
} DoubleTrio;

typedef struct 
{
   int x;
   int y;
   int z;
} IntTrio;
