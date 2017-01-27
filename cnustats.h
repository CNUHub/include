#ifndef __cnustats_h
#define __cnustats_h

// defines structures and routines used for statistics

// cnustats.cc
class probfromtvalueimg : public proc2img {
  void proc2pixels(char *in1, psytype in1type,
		   char *in2, psytype in2type,
		   char *out, psytype outtype);
  double additionToDF;
  int keepNeg;
 public:
  probfromtvalueimg(psyimg *timgptr, psyimg *dfimgptr, double additionToDF,
		    psytype pixeltype=psynotype, int keepNeg=0);
  void output_tree(ostream *out) {proc2img::output_tree(out);*out<<"::probfromtvalueimg";};
};



#endif
