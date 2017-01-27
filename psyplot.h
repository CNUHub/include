#ifndef __psyplot_h
#define __psyplot_h

class psyplot_template {
 public:
  virtual ~psyplot_template(){};
  virtual char *resource();
  virtual void print_not_available(char *function=NULL);
  virtual void image(psyimg *psyimgptr, int z=0, int i=0, char *name=NULL);
  virtual void line(double *y, int ysize, double *x=NULL, int xsize=0,
		    char *type=NULL, char *name=NULL);
  virtual void overdraw_line(double *y, int ysize, double *x=NULL, int xsize=0,
			     char *type=NULL, char *name=NULL);
  virtual void axis(double xmin, double xmax, double ymin, double ymax);
  virtual void title(char *string);
  virtual void xlabel(char *string);
  virtual void ylabel(char *string);
  virtual void text(double x, double y, char *string);
  virtual void set_figure_string(char *property, char *string);
  virtual void new_figure();
  virtual void printout();
};

#ifdef USE_MATLAB
extern "C" {
#include "mat.h"
#include "engine.h"
}
class psyplot : public psyplot_template{
  Engine *ep;
  MATFile *fp;
  char matlab_output[256];
  void open();
 public:
  psyplot();
  virtual ~psyplot();
  char *resource();
  void image(psyimg *psyimgptr, int z=0, int i=0, char *name=NULL);
  void line(double *y, int ysize, double *x=NULL, int xsize=0,
	    char *type=NULL, char *name=NULL);
  void overdraw_line(double *y, int ysize, double *x=NULL, int xsize=0,
		     char *type=NULL, char *name=NULL);
  void axis(double xmin, double xmax, double ymin, double ymax);
  void title(char *string);
  void xlabel(char *string);
  void ylabel(char *string);
  void text(double x, double y, char *string);
  void set_figure_string(char *property, char *string);
  void new_figure();
  void printout();
};
#else
class psyplot : public psyplot_template {
};
#endif

#endif
