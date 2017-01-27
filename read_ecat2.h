#ifndef _read_ecat2_h
#define _read_ecat2_h
#include <stdio.h>
/* this file contains "C" defines, structures and function declarations */

#define MatBLKSIZE 512
#define MatFirstDirBlk 2
#define MAXMAT 8192

/* offsets to fields in various headers */
#define QUANT_SCALE 172		/* quant_scale in image sub_header */
#define SCALE_FACTOR 182	/* scale_factor other file type sub_headers */
#define DATA_TYPE 126		/* data_type in all sub_headers */
#define NUM_PLANES 376		/* num_planes in main_header */
#define NUM_FRAMES 378		/* num_frames in main_header */
#define NUM_GATES 380		/* num_gates in main_header */

/* file types */
#define SCAN_FILE 1
#define IMAGE_FILE 2
#define ATTN_FILE 3
#define NORM_FILE 4

/* matrix data types */
#define GENERIC 0
#define BYTE_TYPE 1
#define VAX_I2 2
#define VAX_I4 3
#define VAX_R4 4
#define SUN_R4 5
#define SUN_I2 6
#define SUN_I4 7

extern int main_soff[];
extern int main_loff[];
extern int main_foff[];

extern int scan_soff[];
extern int scan_loff[];
extern int scan_foff[];

extern int norm_soff[];
extern int norm_loff[];
extern int norm_foff[];

extern int attn_soff[];
extern int attn_loff[];
extern int attn_foff[];

extern int image_soff[];
extern int image_loff[];
extern int image_foff[];

typedef struct {
  unsigned char unk1;	/* seems to be always 1 */
  unsigned char pnum;	/* plane number */
  unsigned char fp;	/* ms 7 bits are plane*256, ls 1 bit is frame*256 */
  unsigned char fnum;	/* frame number */
} matnum_fields;

typedef struct MatDir {
  int matnum;	/* unknown(byte),planeNumber(byte),frameNumber(short) */
  int strtblk;	/* starting block (actually block of matrix sub_header */
  int endblk;	/* ending block */
  int matstat;	/* status (1 == OK ??) */
} MatDir;

/* read_ecat2_utils.h */
void dump_block(const unsigned char *ptr);
short int get_short(const unsigned char *ptr);
int get_int(const unsigned char *ptr);
float get_float(const unsigned char *ptr);
void swaw (short int from[], short int to[], int length);
void swaper(unsigned char *data);
void lswaper(unsigned char *data);
void lswaper2(unsigned char *data);
void fswaper(unsigned char *data);
void read_plane(FILE *fp, int file_type, MatDir *mlist, int nmat,
		int frame, int plane, int doScale, char *outbuff,
		int outbuffbytes, double *planesquantscale);
int read_header(FILE *fp, int blk, unsigned char block[], 
		int *soff, int *loff, int *foff);
int read_block(FILE *fptr, int blkno, char *bufr, int nblks);
void decodeMatnum(int matnum, int *frame, int *plane, int *gate,
		 int *data, int *bed);
int findBlocks(MatDir mlist[],int nmat, int frame, int plane,
	       int *blk0, int *nblk);
int maxPlaneNumber(MatDir mlist[], int nmat, int frame);
int maxFrameNumber(MatDir mlist[], int nmat);
int buildMatrixDirectory(FILE *fptr, MatDir mlist[], int lmax);

/* write_ecat2_utils.c */
void copy_bytes(unsigned char *inptr, unsigned char *outptr, int nbytes);
void ifswaper(unsigned char *data);
void write_plane(FILE *fp, MatDir *mlist, int nmat, int frame, int plane,
		 char *inbuff, int inbuffbytes,
		 char *header, int *soff, int *loff, int *foff);
void write_header(FILE *fp, int blk, unsigned char header[], 
	    int *soff, int *loff, int *foff);
int write_block(FILE *fptr, int blkno, char *bufr, int nblks);
void encodeMatnum(int frame, int plane, int gate, int data, int bed,
		  int *matnum);
int writeMatrixDirectory(MatDir mlist[], int lmax, int nframes, int nplanes,
			 int bytesperplane, int gate, int data, int bed,
			 FILE *fptr);

/*-----------------------------------------------------------------*/
#endif /* _read_ecat2_h */
