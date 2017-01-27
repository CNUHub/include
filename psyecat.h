#ifndef __psyecat_h
#define __psyecat_h

#include <stdio.h>
#include <math.h>
extern "C" {
#include "read_ecat2.h"
}

struct data_word {
  short byte;
  psytype type;
  const char *name;
  short words;
};

/* ecatfile.cc */

/* ecat header structures - each should be one block(512 bytes) long */
extern data_word ecat_main_header[];
extern data_word ecat_image_subhdr[];
extern data_word ecat_scan_subhdr[];
extern data_word ecat_norm_subhdr[];
extern data_word ecat_attn_subhdr[];

psytype getecatclosesttype(psytype type);

class ecatfile : public psyimglnk {
 protected:
  FILE *fp;
  int file_type;
  char main_hdr[MatBLKSIZE];
  int main_hdr_set;
  char frame_hdr[MatBLKSIZE];
  int frame_hdr_frame;
  int frame_hdr_plane;
  int ecat_frame_offset;
  int ecat_plane_offset;
  int *ecat_plane_list;
  MatDir *mlist;
  int nmat;
  int quantify;
  data_word *subhdr;
 public:
  ecatfile(){fp=NULL;mlist=NULL;main_hdr_set=0;frame_hdr_frame=0;
	     file_type=IMAGE_FILE;ecat_frame_offset=ecat_plane_offset=1;
	     subhdr=ecat_image_subhdr;ecat_plane_list=NULL;};
  ecatfile(string fname, int firstframe=1, int lastframe=0, int quantify=1);
  ecatfile(string fname, psyimg *psyimgptr, psytype outtype=psynotype,
	   int ecatfiletype=IMAGE_FILE,
	   char *in_main_hdr=NULL, char *in_frame_hdr=NULL);
  virtual ~ecatfile();
  void initecatfile(string fname, int firstframe=1, int lastframe=0, int quantify=1);
  void output_tree(ostream *out) {psyimglnk::output_tree(out); *out<<"::ecatfile";};
  void getpixel(char *pixel, psytype pixeltype, int x, int y, int z, int i);
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int xinc, int yinc, int zinc, int iinc,
		 psytype pixeltype=psyuchar);
  void showhdr(ostream *out= &cout);
  void showmainhdr(ostream *out= &cout);
  void showsubhdr(ostream *out= &cout);
  float get_header_value(string key_name, int frame=0, int plane=1);
  int get_quantify() {return quantify;}
  float get_frame_quantification(int i=0, int z=0);
  string get_header_string(string key_name, int frame=0, int plane=1);
  int get_ecatfiletype() {return file_type;};
  char *get_mainheader(char *out_main_hdr=NULL);
  char *get_frameheader(char *out_frame_hdr=NULL);
};

psytype ecattype2psytype(int ecattype);
int psytype2ecattype(psytype intype);
void put_ecat_header_string(string str, string key_name, char *hdr,
			    const data_word header_template[]);
string get_ecat_header_string(string key_name, const char *hdr,
			      const data_word header_template[]);
void put_ecat_header_value(float value, string key_name, char *hdr,
			   const data_word header_template[]);
float get_ecat_header_value(string key_name, const char *hdr,
			    const data_word header_template[]);
string get_ecat_patientid(const char *hdr, const data_word header_template[]);
string get_ecat_date(const char *hdr, const data_word header_template[]);
string get_ecat_time(const char *hdr, const data_word header_template[]);
void show_ecat_header(char *hdr, data_word header_template[], ostream *out= &cout);
string bldecatfilename(string name);
int isecatfile(string name, FILE **fp=NULL, char *main_hdr=NULL);

#endif /* !__psyecat_h */
