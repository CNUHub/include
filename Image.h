// ========== File: Image.h ==========

#include "ImagePlane.h"
#include <new.h> 

class Image
{
   private:
      ImagePlane **zPlane;
   public:
      Image(int zDim, int yDim, int xDim, int InitFlag);
      int GetPixel(int zIndex, int yIndex, int xIndex);
      void PutPixel(int zIndex, int yIndex, int xIndex, int value);
      void ReadAnalyzeHeader(char *CoreName, char *RawFileName,
                             IntTrio& ImageDim, DoubleTrio& VoxelDim);
      void ReadAnalyzeImage(char *AnalyzeFileName, IntTrio ImageDim,
                            int& MaxVoxel);
      void MapAtlasToTomo(IntTrio ImageDim, DoubleTrio VoxelDim,
                          Image *RawImage, DoubleTrio Translation, 
                          DoubleTrio Lengths, DoubleTrio AtlasConstants,
                          double MagFactor, DoubleTrio AC, DoubleTrio PC,
                          FILE *fpImage, DoubleTrio RelRot,
                          int& TalDataMin, int& TalDataMax);
      void MappingInput(char *CoreName, DoubleTrio& Translation,
                        DoubleTrio& RelRot, DoubleTrio& AtlasConstants,
                        DoubleTrio& Lengths, double& MagFactor,
                        DoubleTrio& AC, DoubleTrio& PC);
      DoubleTrio AtlasToTomo(DoubleTrio AtlasCoor, DoubleTrio Scale,
                             DoubleTrio Translation, double MagFactor, 
                             DoubleTrio RelRot);
      DoubleTrio TomoToAtlas(DoubleTrio TomoCoor, DoubleTrio Scale,
                             DoubleTrio Translation, double MagFactor,
                             DoubleTrio RelRot);
      char* PearlInput(int argc, char *argv[], int& CubeSide,
                       char& RelaxNeighbor, float& ThreshPercent);
      void FindBrainExtent(float ThreshPercent, int RawDataMax,
                           IntTrio Size, double& Threshold,
                           int& xMinExtent, int& xMaxExtent,
                           int& yMinExtent, int& yMaxExtent,
                           int& zMinExtent, int& zMaxExtent);
      void CubeSum(Image *CubeSum, int CubeSide, IntTrio ImageDim,
                   int xMinExtent, int xMaxExtent, int yMinExtent,
                   int yMaxExtent, int zMinExtent, int zMaxExtent,
                   int& shave, int& CubeVolume);
      void FindExtrema(char *CoreName, Image *RawImage,
                       float ThreshPercent, int CubeSide,
                       char RelaxNeighbor, IntTrio ImageDim,
                       int xMinExtent, int xMaxExtent, int yMinExtent,
                       int yMaxExtent, int zMinExtent, int zMaxExtent,
                       int shave, double Threshold, int CubeVolume); 
};
