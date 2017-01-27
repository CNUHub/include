#ifndef __cnusdt_h
#define __cnusdt_h

#include "psyhdr.h"

void bldsdtfilenames(string primaryname, string *imgname=NULL,
		     string *hdrname=NULL);

class sdtheader {
public:
  sdtheader();
  virtual ~sdtheader();
  int numDim;
  int *dim;
  double *origin;
  double *extent;
  double *fov;
  double *interval;
  string dataType;
  double displayRange[2];
  string fidName;
  string sdtOrient;
  double real2WordScale;
  int getSize(int i);
  double getOrigin(int i);
  double getExtent(int i);
  double getFov(int i);
  double getInterval(int i);
  psytype getPsyType();
  double getWordRes();
  psyorient getPsyOrient();
};

sdtheader *readSdtHeader(string name, sdtheader *rawhdr=NULL,
			 fstream **fdptrptr=NULL);

int issdtfile(string name);

psytype getsdtclosesttype(psytype type);

class sdtfile : public rawfile {
 protected:
  fstream hdrfd;
  string hdrfilename;
  sdtheader rawhdr;
 public:
  sdtfile(string fname, char const *mode=NULL);
  sdtfile(string fname, psyimg *psyimgptr,
	  psytype pixeltype=psynotype);
  virtual ~sdtfile();
  void opensdtfiles(string fname, const char *mode);
  void output_tree(ostream *out) {rawfile::output_tree(out);*out<<"::sdtfile";};
  static void showhdr(sdtheader *rawhdr, ostream *out= &cout);
  void showhdr() { showhdr(&rawhdr); };
  void writeheader();
};


#endif /* !__cnusdt_h */
