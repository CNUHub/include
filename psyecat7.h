#ifndef __psyecat7_h
#define __psyecat7_h

#include <stdio.h>
#include <math.h>
extern "C" {
#include "read_ecat2.h"
}
#include "psyecat.h"

#define ECAT7MAINHDRSIZE 1024
#define ECAT7SUBHDRSIZE 512

  /** ECAT 7 file types */
enum psyecat7types {
  UNKNOWN_FILE_TYPE=0,
  ECAT7_SINOGRAM,
  ECAT7_IMAGE_16,
  ECAT7_ATTENUATION_CORRECTION,
  ECAT7_NORMALIZATION,
  ECAT7_POLAR_MAP,
  ECAT7_VOLUME_8,
  ECAT7_VOLUME_16,
  ECAT7_PROJECTION_8,
  ECAT7_PROJECTION_16,
  ECAT7_IMAGE_8,
  ECAT7_3D_SINOGRAM_16,
  ECAT7_3D_SINOGRAM_8,
  ECAT7_3D_SINOGRAM_NORMALIZATION,
  ECAT7_3D_SINOGRAM_FIT
};
extern const char* psyecat7names[];

/* ecat7 header structures */

extern int ecat7_main_soff[];
extern int ecat7_main_loff[];
extern int ecat7_main_foff[];
extern data_word ecat7_main_header[];

extern int ecat7_attenuation_soff[];
extern int ecat7_attenuation_loff[];
extern int ecat7_attenuation_foff[];
extern data_word ecat7_attenuation_subheader[];

extern int ecat7_image_soff[];
extern int ecat7_image_loff[];
extern int ecat7_image_foff[];
extern data_word ecat7_image_subheader[];

extern int ecat7_polar_map_soff[];
extern int ecat7_polar_map_loff[];
extern int ecat7_polar_map_foff[];
extern data_word ecat7_polar_map_subheader[];

extern int ecat7_3d_scan_soff[];
extern int ecat7_3d_scan_loff[];
extern int ecat7_3d_scan_foff[];
extern data_word ecat7_3d_scan_subheader[];

extern int ecat7_3d_norm_soff[];
extern int ecat7_3d_norm_loff[];
extern int ecat7_3d_norm_foff[];
extern data_word ecat7_3d_norm_subheader[];

extern int ecat7_imported_6_5_scan_soff[];
extern int ecat7_imported_6_5_scan_loff[];
extern int ecat7_3d_imported_6_5_scan_foff[];
extern data_word ecat7_imported_6_5_scan_subheader[];

extern int ecat7_imported_6_5_norm_soff[];
extern int ecat7_imported_6_5_norm_loff[];
extern int ecat7_3d_imported_6_5_norm_foff[];
extern data_word ecat7_imported_6_5_norm_subheader[];

/* ecat7file.cc */

psytype getecat7closesttype(psytype type);

class ecat7file : public rawfile {
 protected:
  FILE *fp;
  int file_type;
  char main_hdr[ECAT7MAINHDRSIZE];
  char sub_hdr[ECAT7SUBHDRSIZE];
  data_word *sub_hdr_info;
 public:
  ecat7file(string fname);
  ecat7file(string fname, psyimg *psyimgptr,
	    psytype outtype=psynotype, int ecat7filetype=ECAT7_IMAGE_16,
	    char *in_main_hdr=NULL, char *in_sub_hdr=NULL);
  virtual ~ecat7file();
  void initecat7file();
  void output_tree(ostream *out) {rawfile::output_tree(out); *out<<"::ecat7file";};
  void showhdr(ostream *out= &cout);
  void showmainhdr(ostream *out= &cout);
  void showsubhdr(ostream *out= &cout);
  int get_ecat7filetype() {return file_type;};
  char *get_mainheader(char *out_main_hdr=NULL);
  char *get_subheader(char *out_sub_hdr=NULL);
};

string ecat7filetypetoname(int filetype);

int isecat7file(string name, fstream *imgfd=NULL, char *main_hdr=NULL,
		psyswaptype *swaptype=NULL);

#endif /* !__psyecat7_h */
