#ifndef __psyhdr_h
#define __psyhdr_h

// defines structures and routines used in libpsyimg.a
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//#include <string.h>
#include <string>
#include <cstring>
//#include <iostream.h>
#include <iostream>
//#include <fstream.h>
#include <fstream>
//#include <iomanip.h>
#include <iomanip>
using namespace std;


#ifdef NO_IRINT
// IRINT not defined
inline int irint(double x){return((int)rint(x));}
#endif

// internal image storage types
enum psytype {psynotype=0, psychar, psyuchar, psyshort, psyushort,
	      psyint, psyuint, psyfloat, psydouble, psyshortsw,
	      psycomplex, psydate, psystring, psydicomdataelement,
              psyrgb, psyargb};
extern const char* psytypenames[];

enum psyorient {psynoorient=-1, psytransverse, psycoronal, psysagittal};

// internal image space types
enum imagespacecode {unknown_space=0, scanner_anatomical_space, aligned_anatomical_space,
		     talairach_space, mni_152_space};
extern const char* imagespacenames[];

// type used to store pixel passed as char array
// and insure size and allignment correct for largest pixel
typedef double largest_pixel;
typedef union { char c[1]; largest_pixel l; } char_or_largest_pixel;

// timefunc.cc
// time functions
int getcurrenttimeinsecs();
string currenttime();
string currentdate();
void SecToHMS(int sec, int& hours, int& minutes, int& seconds);
void PrintHMS(int hours, int minutes, int seconds);

// mathfunc.cc
// 2 value array storage structures
struct xydouble {
  double x, y;
};
struct xyint {
  int x, y;
};
// 3 value array storage structures and operators
struct xyzdouble : xydouble {
  double z;
};
xyzdouble operator + (xyzdouble l, xyzdouble r);
xyzdouble operator + (xyzdouble l, double r);
xyzdouble operator - (xyzdouble l, xyzdouble r);
xyzdouble operator * (xyzdouble l, xyzdouble r);
xyzdouble operator / (xyzdouble l, xyzdouble r);
xyzdouble operator * (xyzdouble l, double r);
double magnitude(xyzdouble p);
struct xyzint : xyint {
  int z;
};
xyzdouble xyzint2double(xyzint in);
xyzint xyzdouble2int(xyzdouble in); // truncates no rounding
xyzint lesserxyzdouble2int(xyzdouble in); // truncates towards lesser numbers
xyzint greaterxyzdouble2int(xyzdouble in); // truncates towards greater numbers
xyzint roundxyzdouble2int(xyzdouble in);
xyzint operator + (xyzint l, xyzint r);
xyzint operator + (xyzint l, int r);
xyzint operator - (xyzint l, xyzint r);

// 4 value array storage structures and operators
struct xyzidouble : xyzdouble {
  double i;
};
xyzidouble operator + (xyzidouble l, xyzidouble r);
xyzidouble operator + (xyzidouble l, double r);
xyzidouble operator - (xyzidouble l, xyzidouble r);
xyzidouble operator * (xyzidouble l, xyzidouble r);
xyzidouble operator / (xyzidouble l, xyzidouble r);
xyzidouble operator * (xyzidouble l, double r);
double magnitude(xyzidouble p);
struct xyziint : xyzint {
  int i;
};
xyzidouble xyziint2double(xyziint in);
xyziint xyzidouble2int(xyzidouble in); // truncates no rounding
xyziint lesserxyzidouble2int(xyzidouble in); // truncates towards lesser numbers
xyziint greaterxyzidouble2int(xyzidouble in); // truncates towards greater numbers
xyziint roundxyzidouble2int(xyzidouble in); // rounding conversion
xyziint operator + (xyziint l, xyziint r);
xyziint operator + (xyziint l, int r);
xyziint operator - (xyziint l, xyziint r);

// matrix storage structures and operators
enum init_matrix_type {Zero, Identity};

union matrix4X4 {
  double a[16];
  double aa[4][4];
  struct matrix_values {
    double m11,m12,m13,m14;
    double m21,m22,m23,m24;
    double m31,m32,m33,m34;
    double m41,m42,m43,m44;
  } m;
  struct row_vectors {
    xyzidouble v1, v2, v3, v4;
  } rv;
  matrix4X4(init_matrix_type mtype=Zero);
  matrix4X4(matrix4X4 *duplicate_mat);
  void reset(init_matrix_type mtype=Zero);
  void reset(matrix4X4 *duplicate_mat);
};

void dispmatrix4X4(const char *name, matrix4X4 *m);

matrix4X4 operator * (double l, matrix4X4 r);

matrix4X4 operator + (matrix4X4 l, matrix4X4 r);

matrix4X4 operator - (matrix4X4 l, matrix4X4 r);

xyzdouble operator * (matrix4X4 l, xyzdouble r);

xyzidouble operator * (matrix4X4 l, xyzidouble r);

matrix4X4 operator * (matrix4X4 l, matrix4X4 r);

// define psyimg dimensions with these storage types
typedef xyzidouble psyres;
typedef xyziint psydims;

// inline functions
inline int clip(int x, int xmin, int xmax)
{
  if(x<xmin)return(xmin);
  else if(x>xmax)return(xmax);
  else return(x);
}
inline psydims clip(psydims value, psydims min, psydims max)
{
  psydims local;
  local.x = clip(value.x, min.x, max.x);
  local.y = clip(value.y, min.y, max.y);
  local.z = clip(value.z, min.z, max.z);
  local.i = clip(value.i, min.i, max.i);
  return local;
}
inline int max(int x, int y)
{
  return( (x>y) ? x : y);
}
inline int min(int x, int y)
{
  return( (x<y) ? x : y);
}
inline double max(double x, double y)
{
  return( (x>y) ? x : y);
}
inline double min(double x, double y)
{
  return( (x<y) ? x : y);
}

// conversions.cc
int gettypebytes(psytype type);
int istypesigned(psytype type);
double min_value_for_type(psytype type);
double max_value_for_type(psytype type);
// type conversion algorithms
void type2char(char *in, psytype intype, char *out);
void type2uchar(char *in, psytype intype, char *out);
void type2short(char *in, psytype intype, char *out);
void type2ushort(char *in, psytype intype, char *out);
void type2int(char *in, psytype intype, char *out);
void type2float(char *in, psytype intype, char *out);
void type2double(char *in, psytype intype, char *out);
void pixeltypechg(char *in, psytype intype, char *out, psytype outtype);

// complex classes

// logfile.cc
// class and functions to build image log files
string bldlogfilename(string fname);
class logfile {
  fstream logfd;
 public:
  logfile(string fname, int argc, char *argv[]);
  ~logfile();
  void loginfilelog(string fname);
  void logmessage(string message);
};

// transforms.cc
struct cnuquatern {
  double b, c, d, qfac, xoff, yoff, zoff, xfactor, yfactor, zfactor;
};

// class to transfrom 3D coordinates from one space to another
class threeDtransform {
private:
  // 4x4 3-d affine transform is represented like this:
  // ___________________________________   _____   _____
  // | srow1.x srow1.y srow1.z srow1.i |   | x |   | x'|
  // | srow2.x srow2.y srow2.z srow2.i | X | y | = | y'|
  // | srow3.x srow3.y srow3.z srow3.i |   | z |   | z'|
  // |     0.0     0.0     0.0     1.0 |   |1.0|   |1.0|
  // -----------------------------------   -----   -----
  matrix4X4 t;
  int quatern_set;
  cnuquatern quatern;
  int inverse_set;
  matrix4X4 inv;
public:
  threeDtransform(matrix4X4 in_matrix, matrix4X4 *in_inverseMatrix=NULL);
  threeDtransform(xyzidouble in_srow1, xyzidouble in_srow2, xyzidouble in_srow3);
  threeDtransform(cnuquatern in_quatern);
  void setMatrix(matrix4X4 in_matrix);
  void setInverseMatrix(matrix4X4 in_inverseMatrix);
  void buildInverseMatrix();
  void setquatern(cnuquatern in_quatern, int calcMatrix=1);
  xyzdouble to_space(xyzdouble in);
  matrix4X4 getMatrix();
  matrix4X4 *getInverseMatrix();
  int isQuaternSet();
  cnuquatern *getQuatern();
  xyzidouble getRow1();
  xyzidouble getRow2();
  xyzidouble getRow3();
  threeDtransform *getInverseTransform();
  //  void threeDtransform::write(ostream *out);
  void write(ostream *out);
};

// psyimg.cc

enum psystatstatus {StatsUninitialized, StatsInitialized};

class psyimg {
 protected:
  psydims size;
  psydims inc;
  psydims orig;
  psydims end;
  psyres res; // m/pixel
  double wordres; // units/bit or scale factor
  int skip;
  int length;
  psytype type;
  psyorient orientation;
  psystatstatus statstatus;
  double minimum;
  double maximum;
  double average;
  double summation;
  double sum_of_squares;
  string patientid;
  string date;
  string time;
  string description;
  threeDtransform *spatialtransform;
  imagespacecode spatialtransformcode;
  threeDtransform *spatialtransform2;
  imagespacecode spatialtransformcode2;
  void setorig(int xorig, int yorig, int zorig, int iorig);
  void setsizeendinc(int xdim, int ydim, int zdim, int idim);
  void setend(int xend, int yend, int zend, int iend);
  void setres(double xres, double yres, double zres, double ires);
  void setinc(int xinc, int yinc, int zinc, int iinc);
  void setstats(double min, double max, double mean, double sum, double sqrsum);
 public:
  psyimg();
  virtual ~psyimg();
  psyimg(int xdim, int ydim, int zdim, int idim=1, psytype pixeltype=psyuchar,
	 int xorig=0, int yorig=0, int zorig=0, int iorig=0,
	 int skippixels=0,
	 double xres=1, double yres=1, double zres=1,
	 double ires=1, double wres=1);
  void initpsyimg(int xdim,int ydim,int zdim,int idim=1,
		  psytype pixeltype=psyuchar,
		  int xorig=0,int yorig=0,int zorig=0,int iorig=0,
		  int skippixels=0,
		  double xres=1, double yres=1, double zres=1,
		  double ires=1, double wres=1);
  virtual void output_tree(ostream *out) { *out<<"psyimg"; };
  virtual void copyblock(char *outbuff, int xorig, int yorig, int zorig,
			 int iorig, int xend, int yend, int zend, int iend,
			 int out_xinc, int out_yinc,
			 int out_zinc, int out_iinc,
			 psytype pixeltype=psyuchar);
  virtual void getpixel(char *pixel, psytype pixeltype,
			int x, int y, int z, int i)=0;
  virtual void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  virtual void freegetpixel();
  virtual void getnextpixel(char *pixel);
  psydims getsize(){return(size);};
  void getsize(int *x, int *y, int *z, int *i);
  psydims getinc(){return(inc);};
  void getinc(int *x, int *y, int *z, int *i);
  psydims getorig(){return(orig);};
  void getorig(int *x, int *y, int *z, int *i);
  psydims getend(){return(end);};
  void getend(int *x, int *y, int *z, int *i);
  psyres getres(){return(res);};
  void getres(double *x, double *y, double *z, double *i);
  void setwordres(double wres){wordres=wres;};
  double getwordres(){return(wordres);};
  psytype gettype(){return(type);};
  int getbytesperpixel(){return(gettypebytes(type));};
  int getlength(){return(length);};
  virtual int inside(int x,int y,int z,int i=0);
  virtual int inside(psydims location);
  virtual long offset(int x,int y,int z, int i=0);
  void showpsyimg();
  psystatstatus getstatstatus() {return(statstatus);};
  void unsetstats() {statstatus=StatsUninitialized;};
  virtual void getstats(double *min, double *max, double *mean,
			double *sum=NULL, double *sqrsum=NULL);
  virtual void getthreshstats(double *min, double *max, double *mean,
			      int *pixelsused, double thresh,
			      double *sum=NULL, double *sqrsum=NULL);
  void showstats();
  int samedim(int xdim, int ydim, int zdim, int idim);
  int samedim(psyimg *psyimgptr);
  void setpatientid(string pid);
  void setdate();
  void setdate(string dt);
  void settime();
  void settime(string tm);
  void setdescription(string desc);
  void setorient(psyorient orientation) {psyimg::orientation=orientation;};
  psyorient getorient() { return(orientation); };
  string getpatientid();
  string getdate();
  void getdate(int *month, int *day=NULL, int *year=NULL);
  string gettime();
  void gettime(int *hour, int *minute=NULL, int *second=NULL);
  string getdescription();
  void setspatialtransform(threeDtransform *transform, imagespacecode code=unknown_space);
  virtual threeDtransform *getspatialtransform();
  virtual imagespacecode getspatialtransformcode();
  void setspatialtransform2(threeDtransform *transform, imagespacecode code=unknown_space);
  virtual threeDtransform *getspatialtransform2();
  virtual imagespacecode getspatialtransformcode2();
};

class psyimglnk : public psyimg {
 public:
  psyimg *inputpsyimg;
  psyimglnk();
  psyimglnk(psyimg *psyimgptr, psytype pixeltype=psynotype);
  psyimglnk(psyimg *psyimgptr,
	    int xdim, int ydim, int zdim, int idim=1,
	    psytype pixeltype=psynotype,
	    int xorig=0, int yorig=0, int zorig=0,
	    int iorig=0, int skippixels=0,
	    double xres=1, double yres=1, double zres=1,
	    double ires=1, double wres=1);
  void initpsyimglnk(psyimg *psyimgptr, psytype pixeltype=psynotype);
  void initpsyimglnk(psyimg *psyimgptr,
		     int xdim, int ydim, int zdim, int idim=1,
		     psytype pixeltype=psynotype,
		     int xorig=0, int yorig=0, int zorig=0,
		     int iorig=0, int skippixels=0,
		     double xres=1, double yres=1, double zres=1,
		     double ires=1, double wres=1);
  void output_tree(ostream *out) {psyimg::output_tree(out); *out<<"::psyimglnk";};
  threeDtransform *getspatialtransform();
  imagespacecode getspatialtransformcode();
  threeDtransform *getspatialtransform2();
  imagespacecode getspatialtransformcode2();
};

class psybuff : public psyimg {
  char *buff;
  char *currentbuffptr;
  psytype currentouttype;
  int getnextpixel_lock;
 public:
  psybuff();
  psybuff(int x,int y,int z,int i=1,psytype pixeltype=psyuchar,
	  int xorig=0,int yorig=0,int zorig=0,int iorig=0,
	  double xres=1, double yres=1, double zres=1,
	  double ires=1, double wres=1);
  virtual ~psybuff();
  void initbuff(int x,int y,int z,int i=1,psytype pixeltype=psyuchar,
		int xorig=0,int yorig=0,int zorig=0,int iorig=0,
		double xres=1, double yres=1, double zres=1,
		double ires=1, double wres=1);
  void output_tree(ostream *out) {psyimg::output_tree(out); *out<<"::psybuff";};
  void getpixel(char *pixel, psytype pixeltype, int x, int y, int z, int i);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void freegetpixel(){getnextpixel_lock=0;};
  void getnextpixel(char *pixel);
  void copyblock(char *, int, int, int, int, int, int, int, int,
		 int, int, int, int, psytype=psyuchar);
  void showbuff();
  char *getbuff() {return(buff);};
};

class psyfullbuff : public psyimglnk {
 protected:
  psybuff buffimage;
 public:
  psyfullbuff();
  psyfullbuff(psyimg *psyimgptr, psytype pixeltype=psynotype);
  void initpsyfullbuff(psyimg *psyimgptr, psytype pixeltype=psynotype);
  void output_tree(ostream *out) {psyimglnk::output_tree(out);*out<<"::psyfullbuff";};
  virtual void chknfillbuff();
  void getpixel(char *pixel, psytype pixeltype, int x, int y, int z, int i);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void freegetpixel() {buffimage.freegetpixel();};
  void getnextpixel(char *pixel);
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int xinc, int yinc, int zinc, int iinc,
		 psytype pixeltype=psyuchar);
};

class pgbuff {
 public:
  pgbuff(int size=0);
  ~pgbuff();
  char *buff;
  pgbuff *next;
  pgbuff *prev;
  pgbuff **arrayloc;
  int lockcount;
};

class psypgbuff : public psyimglnk {
  pgbuff *linklist;
  pgbuff **pgbuffarray;
  int numpages;
  int maxpages;
  int currentz;
  int currenti;
  char *currentbuffptr;
  char *endcurrentpg;
  psytype currentouttype;
  int getnextpixel_lock;
  char *getzptr(int z, int i);
 protected:
  virtual void fillpage(char *buff, int z, int i);
 public:
  psypgbuff();
  psypgbuff(psyimg *psyimgptr, int maxnumpages=10);
  virtual ~psypgbuff();
  void initpgbuff(psyimg *psyimgptr, int maxnumpages=10,
		  psytype pixeltype=psynotype);
  void initpgbuff(int maxnumpages=10);
  void initpgbuff(psyimg *psyimgptr,
		  int xdim, int ydim, int zdim, int idim=1,
		  psytype pixeltype=psynotype,
		  int xorig=0, int yorig=0, int zorig=0,
		  int iorig=0, int skippixels=0,
		  double xres=1, double yres=1, double zres=1,
		  double ires=1, double wres=1,
		  int maxnumpages=10);
  void output_tree(ostream *out) {psyimglnk::output_tree(out);*out<<"::psypgbuff";};
  void reset(psyimg *psyimgptr=NULL);
  void getpixel(char *pixel, psytype pixeltype, int x, int y, int z, int i);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void freegetpixel();
  void getnextpixel(char *pixel);
  void copyblock(char *, int, int, int, int, int, int, int, int,
		 int, int, int, int, psytype=psyuchar);
  char *getzptrlocked(int z, int i);
  void unlockzptr(int z, int i);
};

class reverserows : public psypgbuff {
 protected:
  void fillpage(char *buff, int z, int i);
 public:
  reverserows() {};
  reverserows(psyimg *psyimgptr, int maxnumpages=1);
};

class psyimglnkpxl : public psyimglnk {
 protected:
  psydims getpixelloc;
  psytype getpixeltype;
  int getnextpixel_lock;
 public:
  psyimglnkpxl();
  psyimglnkpxl(psyimg *psyimgptr, psytype pixeltype=psynotype);
  void initpsyimglnkpxl(psyimg *psyimgptr, psytype pixeltype=psynotype);
  void initpsyimglnkpxl(psyimg *psyimgptr,
			int xdim, int ydim, int zdim, int idim=1,
			psytype pixeltype=psynotype,
			int xorig=0, int yorig=0, int zorig=0,
			int iorig=0, int skippixels=0,
			double xres=1, double yres=1, double zres=1,
			double ires=1, double wres=1);
  void output_tree(ostream *out) {psyimglnk::output_tree(out);*out<<"::psyimglnkpxl";};
  void getpixel(char *pixel, psytype pixeltype,
		int x, int y, int z, int i);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void freegetpixel(){getnextpixel_lock=0;};
  void incgetpixel();
};

// rawfile.cc
void swap_data(char *data, const int *soff, const int *loff, const int *foff);


enum psyfileclass {psynoclass=0, rawfileclass, analyzefileclass,
		   ecatfileclass, ecat7fileclass, dicomfileclass,
		   sdtfileclass, niftifileclass};
extern const char* psyfileclassnames[];

void writeouttypeargchoices(ostream *out);
psytype checkouttypearg(char *arg);

void writeoutfileclassargchoices(ostream *out);
psyfileclass checkoutfileclassarg(char *arg);

psyimg *psynewinfile(string filename, psyfileclass *infileclass=NULL,
		     psytype *intype=NULL, int **fileclassinfo=NULL);

psyimg *psynewoutfile(string filename, psyimg *psyimgptr,
		      psyfileclass outfileclass=analyzefileclass,
		      psytype outtype=psynotype, int *fileclassinfo=NULL);

void psyopenfile(string fname, const char *mode, fstream *fd, int *status=NULL);

enum psyswaptype { psynoswap=0, psyreversewordbytes };

class rawfile : public psyimglnk {
 protected:
  fstream imgfd;
  string imgfilename;
  psyswaptype swaptype;
  int getnextpixel_lock;
 public:
  rawfile(){getnextpixel_lock=0;};
  rawfile(psyimg *psyimgptr, psytype pixeltype=psynotype);
  rawfile(string fname, const char *mode);
  rawfile(string fname, const char *mode, psyimg *psyimgptr);
  rawfile(string fname, const char *mode, int xdim, int ydim, int zdim,
	  int idim=1, psytype pixeltype=psyuchar,
	  int xorig=0, int yorig=0, int zorig=0, int iorig=0,
	  int skippixels=0, double xres=1, double yres=1,
	  double zres=1, double ires=1, double wres=1);
  virtual ~rawfile();
  void setinc(int xinc, int yinc, int zinc, int iinc)
    {psyimglnk::setinc(xinc,yinc,zinc,iinc);};
  void output_tree(ostream *out) {psyimglnk::output_tree(out);*out<<"::rawfile";};
  void getpixel(char *pixel, psytype pixeltype, int x, int y, int z, int i);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void freegetpixel() {getnextpixel_lock=0;};
  void getnextpixel(char *pixel);
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int xinc, int yinc, int zinc, int iinc,
		 psytype pixeltype=psyuchar);
  void writedata();
};

// proc1img.cc
class proc1img : public psyimglnk {
 protected:
  virtual void convertpixel(char *in, psytype intype,
			    char *out, psytype outtype)=0;
 public:
  proc1img() : psyimglnk() {};
  proc1img(psyimg *psyimgptr, psytype pixeltype=psynotype)
    : psyimglnk(psyimgptr, pixeltype) {};
  void initproc1img(psyimg *psyimgptr, psytype pixeltype=psynotype)
    {initpsyimglnk(psyimgptr, pixeltype);};
  void output_tree(ostream *out) {psyimglnk::output_tree(out);*out<<"::proc1img";};
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int out_xinc, int out_yinc,
		 int out_zinc, int out_iinc,
		 psytype pixeltype=psyuchar);
  void getpixel(char *pixel, psytype pixeltype, int x, int y, int z, int i);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void freegetpixel(){inputpsyimg->freegetpixel();};
  void getnextpixel(char *pixel);
};

// conversions.cc
class convertimg : public proc1img {
  void convertpixel(char *in, psytype intype, char *out, psytype outtype);
 public:
  convertimg() {};
  convertimg(psyimg *psyimgptr, psytype pixeltype=psynotype)
    : proc1img(psyimgptr, pixeltype) {};
  void initconvertimg(psyimg *psyimgptr, psytype pixeltype=psyuchar);
  void output_tree(ostream *out) {proc1img::output_tree(out);*out<<"::convertimg";};
};

// proc2img.cc
string combine_comments(string s1, string s2);

class psy2imglnk : public psyimg {
 public:
  psyimg *in1psyimg;
  psyimg *in2psyimg;
  psy2imglnk();
  psy2imglnk(psyimg *psy1imgptr, psyimg *psy2imgptr);
  void initpsy2imglnk(psyimg *psy1imgptr, psyimg *psy2imgptr,
		      psytype pixeltype=psynotype,
		      psydims *indims=NULL, xyziint *inorig=NULL,
		      psyres *inres=NULL);
  void output_tree(ostream *out) {psyimg::output_tree(out);*out<<"::psy2imglnk";};
  psyimg *getlink1();
  psyimg *getlink2();
};

class proc2img : public psy2imglnk {
 protected:
  virtual void proc2pixels(char *in1, psytype in1type,
			   char *in2, psytype in2type,
			   char *out, psytype outtype)=0;
 public:
  proc2img(psyimg *psy1imgptr, psyimg *psy2imgptr,
	   psytype pixeltype=psynotype);
  void initproc2img(psyimg *psy1imgptr, psyimg *psy2imgptr,
		    psytype pixeltype=psynotype);
  void output_tree(ostream *out) {psy2imglnk::output_tree(out);*out<<"::proc2img";};
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int out_xinc, int out_yinc,
		 int out_zinc, int out_iinc,
		 psytype pixeltype=psyuchar);
  void getpixel(char *pixel, psytype pixeltype, int x, int y, int z, int i);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void freegetpixel();
  void getnextpixel(char *pixel);
};

// filter.cc
class pixelavg : public psyimglnkpxl {
  psypgbuff *psypagebuffer;
  xyzint boxsize;
  xyzint startbox, endbox;
  int *zplane;
  char **zptr;
  double factor;
 public:
  pixelavg();
  pixelavg(psyimg *psyimgptr, psytype pixeltype=psynotype,
	   int incubesize=3, int sizey=-1, int sizez=-1,
	   double factor=1.0);
  ~pixelavg();
  void output_tree(ostream *out) {psyimglnkpxl::output_tree(out);*out<<"::pixelavg";};
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int out_xinc, int out_yinc,
		 int out_zinc, int out_iinc,
		 psytype pixeltype=psyuchar);
  void getnextpixel(char *pixel);
};

enum gradienttype {no_gradient=-1, x_gradient, y_gradient, z_gradient,
		   mag_of_x_gradient, mag_of_y_gradient, mag_of_z_gradient,
		   mag_of_xy_gradient, mag_of_xyz_gradient,
		   max_mag_of_xy_gradient, max_mag_of_xyz_gradient};

class gradient : public psyimglnkpxl {
  gradienttype gradtype;
  xyzint gradsize;
  xyzint prevoffset, nextoffset;
  double factor;
  psypgbuff *psypagebuffer;
 public:
  gradient();
  gradient(psyimg *psyimgptr, gradienttype gradtype=no_gradient,
	   psytype pixeltype=psynotype, double factor=1.0);
  ~gradient();
  void output_tree(ostream *out) {psyimglnkpxl::output_tree(out);*out<<"::gradient";};
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int out_xinc, int out_yinc,
		 int out_zinc, int out_iinc,
		 psytype pixeltype=psyuchar);
  void getnextpixel(char *pixel);
};

// template.cc
class bldtemplate : public psypgbuff {
  double threshold;
  int *top_most, *bottom_most;
 protected:
  void fillpage(char *buff, int z, int i);
 public:
  bldtemplate();
  bldtemplate(psyimg *psyimgptr, double threshold=0, int maxnumpages=1);
  ~bldtemplate();
  void output_tree(ostream *out) {psypgbuff::output_tree(out);*out<<"::bldtemplate";};
};

class templateimg : public psypgbuff {
  psyimg *templateptr;
  double threshold;
  double default_value;
 protected:
  void fillpage(char *buff, int z, int i);
 public:
  templateimg();
  templateimg(psyimg *psyimgptr, psyimg *templateptr, int maxnumpages=1,
	      double threshold=1e-16, double default_value=0);
  void output_tree(ostream *out) {psypgbuff::output_tree(out);*out<<"::templateimg";};
  void reset(psyimg *psyimgptr=NULL, psyimg *templateptr=NULL);
  void setthresholdvalues(double threshold, double default_value);
  void gettemplatedstats(double *min, double *max, double *mean,
			 int *pixelsused,
			 double *sum=NULL, double *sqrsum=NULL,
			 double *var=NULL, double *adev=NULL,
			 psydims *min_location=NULL,
			 psydims *max_location=NULL,
			 xyzidouble *center_of_mass = NULL);
};

void outputindice(FILE *fp, double x, double y, double z, double value);

void FindBrainExtent(psyimg *inimageptr, double Threshold,
                     int *pass_xMinExtent, int *pass_xMaxExtent, 
		     int *pass_yMinExtent, int *pass_yMaxExtent,
		     int *pass_zMinExtent, int *pass_zMaxExtent,
		     int debug=0);

void FindExtrema(string CoreName, psyimg *avgimgptr, psyimg *rawimgptr,
		 psyimg *template_imgptr, double Threshold,
		 int CubeSide, int relax_neighbor,
		 int xMinExtent, int yMinExtent, int zMinExtent,
		 int xMaxExtent, int yMaxExtent, int zMaxExtent,
		 const char *command_desc,
		 int DEBUG=0);

// psyimgdblz.cc
class psyimgdblz : public  psyimglnkpxl {
 public:
  psyimgdblz(psyimg *psyimgptr, psytype pixeltype=psynotype);
  void output_tree(ostream *out) {psyimglnkpxl::output_tree(out);*out<<"::psyimgdblz";};
  void getnextpixel(char *pixel);
};

class psyimghalfz : public psypgbuff {
 protected:
  void fillpage(char *buff, int z, int i);
 public:
  psyimghalfz(psyimg *psyimgptr);
  void output_tree(ostream *out) {psypgbuff::output_tree(out);*out<<"::psyimghalfz";};
};


class psyimgdupplanes : public psyimglnkpxl {
 private:
  int number_of_duplicates;
 public:
  psyimgdupplanes(psyimg *psyimgptr, int number_of_duplicates);
  void output_tree(ostream *out) {psyimglnk::output_tree(out);*out<<"::psyimgdupplanes";};
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void freegetpixel();
  void getnextpixel(char *pixel);
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int xinc, int yinc, int zinc, int iinc,
		 psytype pixeltype=psyuchar);
};

class psyimgdupframes : public psypgbuff {
 private:
  int number_of_duplicates;
 protected:
  void fillpage(char *buff, int z, int i);
 public:
  psyimgdupframes(psyimg *psyimgptr, int number_of_duplicates);
  void output_tree(ostream *out) {psypgbuff::output_tree(out);*out<<"::psyimgdupframes";};
};

// imgmath.cc
double scale_factor_for_max_res(double dmin, double dmax, psytype outtype);

void calc_image_centroid(psyimg *psyimgptr, double *x, double *y=NULL,
			 double *z=NULL, double *i=NULL);

class scaleimg : public proc1img {
  double scale;
  double translation;
  double threshmin, threshmax;
  int threshminflag, threshmaxflag;
  double threshminvalue, threshmaxvalue;
  void convertpixel(char *in, psytype intype, char *out, psytype outtype);
 public:
  scaleimg(psyimg *psyimgptr, psytype pixeltype,
	   double scale_factor=1.0, double translate=0.0);
  void initscaleimg(psyimg *psyimgptr, psytype pixeltype,
		    double scale_factor=1.0, double translate=0.0);
  void output_tree(ostream *out) {proc1img::output_tree(out);*out<<"::scaleimg";};
  void set_scale_factor(double scale_factor);
  void set_scale_factor_for_max_res();
  void set_min_thresh(double min_thresh, double min_thresh_value);
  void set_max_thresh(double max_thresh, double max_thresh_value);
};

class addimgs : public proc2img {
  void proc2pixels(char *in1, psytype in1type,
		   char *in2, psytype in2type,
		   char *out, psytype outtype);
 protected:
  double scalefactor1;
  double scalefactor2;
 public:
  addimgs(psyimg *psy1imgptr, psyimg *psy2imgptr,
	  double scalefactor1=1, double scalefactor2=1,
	  psytype pixeltype=psynotype);
  void output_tree(ostream *out) {proc2img::output_tree(out);*out<<"::addimgs";};
  void setvalues(double scalefactor1, double scalefactor2);
};

class multiplyimgs : public proc2img {
  void proc2pixels(char *in1, psytype in1type,
		   char *in2, psytype in2type,
		   char *out, psytype outtype);
 protected:
  double factor;
 public:
  multiplyimgs(psyimg *psy1imgptr, psyimg *psy2imgptr,
	  double factor=1, psytype pixeltype=psynotype);
  void output_tree(ostream *out) {proc2img::output_tree(out);*out<<"::multiplyimgs";};
  void setvalues(double factor);
};

class divideimgs : public proc2img {
  void proc2pixels(char *in1, psytype in1type,
		   char *in2, psytype in2type,
		   char *out, psytype outtype);
 protected:
  double factor;
  double minimum_divisor_magnitude;
  double below_minimum_default;
 public:
  divideimgs(psyimg *psy1imgptr, psyimg *psy2imgptr,
	     double factor=1,
	     double below_minimum_default=0,
	     double minimum_divisor_magnitude=1e-16,
	     psytype pixeltype=psynotype);
  void output_tree(ostream *out) {proc2img::output_tree(out);*out<<"::divideimgs";};
  void setvalues(double factor,
		 double below_minimum_default=0,
		 double minimum_divsior_magnitude=1e-16);
};

class accumulateimgs : public psypgbuff {
 private:
  psyimg *accumulatedpsyimgptr;
  double first_factor;
  psytype accumulatetype;
 protected:
  void fillpage(char *buff, int z, int i);
 public:
  accumulateimgs(psytype pixeltype=psydouble);
  accumulateimgs(psyimg *psyimgptr, double factor=1.0,
		 psytype pixeltype=psydouble);
  ~accumulateimgs();
  void output_tree(ostream *out) {psypgbuff::output_tree(out);*out<<"::accumulateimgs";};
  void addimg(psyimg *psyimgptr, double factor=1.0);
  void setscale(double scale);
};

class psyshiftimg: public psypgbuff {
  psydims shift;
 protected:
  virtual void fillpage(char *buff, int z, int i);
 public:
  psyshiftimg(psyimg *psyimgptr, psydims shift);
};

class padimage: public psypgbuff {
  double padvalue;
  xyziint image_beg;
  xyziint image_end;
 protected:
  virtual void fillpage(char *buff, int z, int i);
 public:
  padimage(psyimg *psyimgptr,
	   xyziint prepad, xyziint postpad,
	   double padvalue=0.0);
};

class concatimgs : public psy2imglnk {
  int catdim;
  double dim_res;
  int dim_res_set;
  int first_img_2_size;
 public:
  concatimgs();
  concatimgs(psyimg *psy1imgptr, psyimg *psy2imgptr, int catdim=2);
  concatimgs(psyimg *psy1imgptr, psyimg *psy2imgptr, int catdim, double dimres);
  void initconcatimgs(psyimg *psy1imgptr, psyimg *psy2imgptr, int catdim=2);
  void initconcatimgs(psyimg *psy1imgptr, psyimg *psy2imgptr, int catdim, double dimres);
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int out_xinc, int out_yinc,
		 int out_zinc, int out_iinc,
		 psytype pixeltype=psyuchar);
  void getpixel(char *pixel, psytype pixeltype,
		int x, int y, int z, int i);
  void getnextpixel(char *pixel);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void output_tree(ostream *out) {psy2imglnk::output_tree(out);*out<<"::concatimgs";};
};

class psyhistogram : public psyfullbuff {
 protected:
  int lessercnt;
  int greatercnt;
  double histmin;
  double histmax;
 public:
  psyhistogram();
  psyhistogram(psyimg *psyimgptr,
			double min, double max, int numberbins=256);
  void initpsyhistogram(psyimg *psyimgptr,
			double min, double max, int numberbins=256);
  void output_tree(ostream *out) {psyfullbuff::output_tree(out);*out<<"::psyhistogram";};
  double gethistogrammin() { return histmin; };
  double gethistogrammax() { return histmax; };
  int getlessercount() { return lessercnt; };
  int getgreatercount() { return greatercnt; };
  void chknfillbuff();
};

// psyshapes.cc

class psyimgblk : public psyimglnkpxl {
  psydims orig_fix;
 public:
  psyimgblk(){orig_fix.x=orig_fix.y=orig_fix.z=orig_fix.i=0;};
  psyimgblk(psyimg *psyimgptr,
	    int xorig, int yorig, int zorig, int iorig,
	    int xend, int yend, int zend, int iend,
	    int reset_origin=0,
	    psytype pixeltype=psynotype);
  psyimgblk(psyimg *psyimgptr,
	    psydims orig, psydims end,
	    int reset_origin=0,
	    psytype pixeltype=psynotype);
  void init(psyimg *psyimgptr,
	    int xorig, int yorig, int zorig, int iorig,
	    int xend, int yend, int zend, int iend,
	    int reset_origin=0,
	    psytype pixeltype=psynotype);
  void output_tree(ostream *out) {psyimglnkpxl::output_tree(out);*out<<"::psyimgblk";};
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int out_xinc, int out_yinc,
		 int out_zinc, int out_iinc,
		 psytype pixeltype=psyuchar);
  void getnextpixel(char *pixel);
};

class psyimgconstant : public psyimglnkpxl {
  double value;
 public:
  psyimgconstant(){value=1.0;};
  psyimgconstant(psyimg *psyimgptr, double value=1.0,
		 psytype pixeltype=psynotype);
  psyimgconstant(double value, int xdim, int ydim, int zdim, int idim=1,
		 psytype pixeltype=psynotype,
		 int xorig=0, int yorig=0, int zorig=0, int iorig=0,
		 double xres=1, double yres=1, double zres=1, double ires=1,
		 double wres=1);
  void init(psyimg *psyimgptr, double value=1.0, psytype pixeltype=psynotype);
  void output_tree(ostream *out) {psyimglnkpxl::output_tree(out);*out<<"::psyimgconstant";};
  double getvalue(){return(value);};
  void getnextpixel(char *pixel);
};

class psyimgshape : public psyimglnkpxl {
  double foreground_value;
  double background_value;
  int in_image_as_background;
 public:
  psyimgshape();
  psyimgshape(psyimg *psyimgptr, psytype pixeltype=psynotype);
  void init(psyimg *psyimgptr, psytype pixeltype=psynotype);
  void output_tree(ostream *out) {psyimglnkpxl::output_tree(out);*out<<"::psyimgshape";};
  virtual int inshape(psydims location)=0;
  void set_foreground_value(double foreground_value) {
    psyimgshape::foreground_value=foreground_value;};
  void set_background_value(double background_value) {
    psyimgshape::background_value=background_value;
    in_image_as_background=0;};
  void set_in_image_as_background(){in_image_as_background=1;};
  double getforeground_value(){return(foreground_value);};
  double getbackground_value();
  void getnextpixel(char *pixel);
};

class psyimgbox : public psyimgshape {
  psydims box_orig;
  psydims box_end;
 public:
  psyimgbox();
  psyimgbox(psyimg *psyimgptr, psydims box_orig, psydims box_end,
	    psytype pixeltype=psynotype);
  void init(psyimg *psyimgptr, psydims box_orig, psydims box_end,
	    psytype pixeltype=psynotype);
  void output_tree(ostream *out) {psyimgshape::output_tree(out);*out<<"::psyimgbox";};
  int inshape(psydims location);
};

class psyimgsphere : public psyimgshape {
  xyzdouble centroid;
  double radius_squared;
  int ibegin, iend;
 public:
  psyimgsphere(){};
  psyimgsphere(psyimg *psyimgptr, double radius,
	       double xcenter, double ycenter, double zcenter,
	       psytype pixeltype=psynotype);
  void init(psyimg *psyimgptr, double radius,
	    double xcenter, double ycenter, double zcenter,
	    psytype pixeltype=psynotype);
  void setirange(int ibegin, int iend);
  void output_tree(ostream *out) {psyimgshape::output_tree(out);*out<<"::psyimgsphere";};
  int inshape(psydims location);
};

class psyimgcylinder : public psyimgshape {
  double radius_squared;
  double icenter;
  double jcenter;
  int axis;
  int ibegin, iend;
 public:
  psyimgcylinder(){};
  psyimgcylinder(psyimg *psyimgptr, double radius,
		 double icenter, double jcenter, int axis,
		 psytype pixeltype=psynotype);
  void init(psyimg *psyimgptr, double radius,
	    double icenter, double jcenter, int axis,
	    psytype pixeltype=psynotype);
  void setirange(int ibegin, int iend);
  void output_tree(ostream *out) {psyimgshape::output_tree(out);*out<<"::psyimgcylinder";};
  int inshape(psydims location);
};

class psyimgellipsoid : public psyimgshape {
  xyzdouble centroid;
  xyzdouble squared_factors;
  int ibegin, iend;
 public:
  psyimgellipsoid(){};
  psyimgellipsoid(psyimg *psyimgptr, xyzdouble centroid,
		  xyzdouble axis_lengths, psytype pixeltype=psynotype);
  void init(psyimg *psyimgptr, xyzdouble centroid, xyzdouble axis_lengths,
	    psytype pixeltype=psynotype);
  void setirange(int ibegin, int iend);
  void output_tree(ostream *out) {psyimgshape::output_tree(out);*out<<"::psyimgellipsoid";};
  int inshape(psydims location);
};

#endif
