#ifndef __talairach_h
#define __talairach_h
enum mapfiletype {standard_mapfile=0, satoshi_sta_lib};
enum mappingmodes {standard_mappingmode=0, outside_nearest};

// standard dimensions approximated from 1988 Co-Planar Stereotaxic Atlas
// of the Human Brain by Jean Talairach and Pierre Tournoux
const double TALAIRACH_WIDTH = (.136);
const double TALAIRACH_HEIGHT = (.118);
const double TALAIRACH_LENGTH = (.172);
const double TALAIRACH_FRONT_AC_LENGTH = (.070);
const double TALAIRACH_ACPC_LENGTH = (.024);
const double TALAIRACH_ACPC_HEIGHT = (.043);
// old dimensions from older atlas
//const double TALAIRACH_HEIGHT = (.121);
//const double TALAIRACH_LENGTH = (.171);
//const double TALAIRACH_FRONT_AC_LENGTH = (.071);
//const double TALAIRACH_ACPC_LENGTH = (.025);
const double TALAIRACH_ACPC_CENTER =
  (TALAIRACH_FRONT_AC_LENGTH + TALAIRACH_ACPC_LENGTH/2.0);

class to_talairach : public psyimglnkpxl {
  xyzdouble AC;            // loc. AC tomo coor. [m]
  xyzdouble PC;            // loc. PC tomo coor. [m]
  xyzdouble front;         // loc. brain front along acpc tomo coor. [m]
  xyzdouble back;          // loc. brain back along acpc tomo coor. [m]
  xyzdouble TomoOrig;      // loc. of origin in tomo coor. [m]
  xyzdouble Lengths;       // lengths of this brain [m]
  xyzdouble AtlasLengths; // lengths of talairach brain [m]
  xyzdouble Scale;         // Ratio of Lengths to AtlasLengths    [-] 
  xyzdouble Offset;        // location of origin in talairach coor.  [m]
  xyzdouble RelRot;        // relative rotations [deg]
  xyzdouble SinRelRot;   // Sin of RelRot                           [-]
  xyzdouble CosRelRot;   // Cos of RelRot                           [-]
  mappingmodes mappingmode;
 public:
  to_talairach(psyimg *psyimgptr, psytype outtype=psynotype,
	       int resize=0);
  void init(int resize=0);
  void setmappingmode(mappingmodes mappingmode){
    to_talairach::mappingmode=mappingmode;};
  mappingmodes getmappingmode(){return(mappingmode);};
  void getnextpixel(char *pixel);
  void mappinginput();
  void mappinginput(char *file,
		    mapfiletype mftype=standard_mapfile);
  void outputmapping(char *file);
  xyzdouble AtlasToTomo(xyzdouble AtlasCoor);
  xyzdouble TomoToAtlas(xyzdouble AtlasCoor);
  void indice2atlas(double xi, double yi, double zi,
		    double *xa, double *ya, double *za);
  void tomo2indice(double xt, double yt, double zt,
		   double *xi, double *yi, double *zi);
  void indice2tomo(double xi, double yi, double zi,
		   double *xt, double *yt, double *zt);
  void showto_talairach();
};

class talairach_location {
  xyzdouble res, front, back, ac, pc, origin;
  xyzint reverse_flag;
 public:
  talairach_location(psyimg *psyimgptr, xyzint *reverse_flag)
    {init(psyimgptr, reverse_flag);};
  talairach_location(xyzint orig, xyzint end, xyzdouble res){
    init(orig, end, res); };
  void init(psyimg *psyimgptr, xyzint *reverse_flag=NULL);
  void init(xyzint orig, xyzint end, xyzdouble res, xyzint *reverse_flag=NULL);
  void pixel2talairach(double xp, double yp, double zp,
		       double *xt, double *yt, double *zt);
};

#endif
