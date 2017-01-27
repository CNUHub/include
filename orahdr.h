//#ifndef __orahdr_h
//#define __orahdr_h

// defines structures and routines used in libstrtoarr.so

 #include <math.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>


char **strtoarr(int argc, char *args);

// Changed the definition of addimgs to accept the in_argv string instead of the argv array.
void addimgs(int argc, char **argv, char *outmessage[], char *errmessage[], int *retval);
void imgprocess(char *in_argv, char *outmessage[], int *retval);
void imgprocess_new(char *in_argv, char *outmessage[], int *retval);
//void addimgs(int argc, char *in_argv, char outmessage[1000]);
void add2imgs(int argc, char **argv, char *outmessage);
void bldtemplate(int argc, char **argv, char *outmessage);
void bldtemplate2(int argc, char **argv, char *outmessage);
void scaleimg(int argc, char **argv, char *outmessage[]);
void roistats(int argc, char **argv, char *outmessage[]);
void pearl(int argc, char **argv, char *outmessage[]);
void talairachpoint(int argc, char **argv, char *outmessage[]);
void pixelstats(int argc, char **argv, char *outmessage[]);


void c_addimgs(double in_argc, char *in_argv, char *outmessage, char *errmessage, int *retval);
char* c_add2imgs(double in_argc, char *in_argv);
char* c_bldtemplate(double in_argc, char *in_argv);
char* c_scaleimg(double in_argc, char *in_argv);
char* c_roistats(double in_argc, char *in_argv);
char* c_pearl(double in_argc, char *in_argv);
char* c_talairachpoint(double in_argc, char *in_argv);
char* c_pixelstats(double in_argc, char *in_argv);
void  c_imgprocess(char *in_argv, char *outmessage1, char *outmessage2, char *outmessage3,
		char *truncated, int *retval);




//#endif
