#ifndef __psyanalyze_h
#define __psyanalyze_h
#include "dbh.h"

// analyze.cc

psytype getanalyzeclosesttype(psytype type);

int psytype2analyze(psytype pixeltype);

psytype analyze2psytype(int analyzetype, int pixelbits=-1);

int psyorient2analyze(psyorient orientation);

psyorient analyze2psyorient(int analyzetype);

void bldanalyzefilenames(string primaryname, string *imgname=NULL,
			 string *hdrname=NULL);

int validanalyzehdr(dsr *rawhdr);

int isanalyzefile(string name);

dsr *readAnalyzeHeader(string name, dsr *rawhdr=NULL, fstream **fdptrptr=NULL,
		       psyswaptype *swaptypeptr=NULL);

int writeAnalyzeHeader(dsr *rawhdr, string name, fstream *fdptr=NULL);

class analyzefile : public rawfile {
 protected:
  fstream hdrfd;
  string hdrfilename;
  dsr rawhdr;
  void writetofiles();
 public:
  analyzefile(string fname, const char *mode=NULL, int ignore_valid=0);
  analyzefile(string fname, psyimg *psyimgptr, psytype pixeltype=psynotype);
  virtual ~analyzefile();
  void output_tree(ostream *out) {rawfile::output_tree(out);*out<<"::analyzefile";};
  void openanalyzefiles(string fname, const char *mode);
  static void showhdr(dsr *rawhdr, ostream *out= &cout);
  static void showhdr(dsr rawhdr);
  void showhdr();
};

class outputanalyze : public analyzefile {
 public:
  outputanalyze(string fname, psyimg *psyimgptr, psytype pixeltype=psynotype) :
    analyzefile(fname, psyimgptr, pixeltype) {};
  void output_tree(ostream *out) {analyzefile::output_tree(out);*out<<"::outputanalyze";};
};

#endif
