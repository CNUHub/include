// ========== File: ImagePlane.h ==========

#include "ImageGlobals.h"

class ImagePlane 
{
   private:
      int **p;
      int s1, s2;
   public:
      int ub1, ub2;
      ImagePlane(int yDimension, int xdimension);
      ~ImagePlane();
      int& GetElement(int yIndex, int xIndex);
      void PutElement(int yIndex, int xIndex, int value);
};
