#ifndef __blood_h
#define __blood_h
#include "PET_analysis.h"
/* this include defines c functions included in libblood.a */

/* PET_signal_routines.c */
int ROI_decay_correct(ROI_data *ROI);
int blood_decay_correct(blood_data *blood);
int ROI_decay_apply(ROI_data *ROI);
int blood_decay_apply(blood_data *blood);
int ROI_signal2blood(ROI_data *ROI, blood_data *blood, cal_data *cal);
int ROI_signal2ROI(ROI_data *ROI, ROI_data *ROI2, cal_data *cal);
int plane_decay_correct(plane_data *plane);
int get_isotope(char *name, float *half_life, float *pos_abund, float *lambda);

/* PET_time_routines.c */
int ROI_time2min(ROI_data *ROI);
int ROI_time2sec(ROI_data *ROI);
int blood_time2min(blood_data *blood);
int blood_time2sec(blood_data *blood);
int ROI_time2blood(ROI_data *ROI, blood_data *blood);
int ROI_time2ROI(ROI_data *ROI, ROI_data *ROI2);
int blood_time2blood(blood_data *dest, blood_data *blood);
int plane_time2min(plane_data *plane);
long clock2sec(int hrs, int mins, int secs);

/* load_PET_data.c */
int load_blood_data(blood_data *curve);
int load_ROI_data(ROI_data *curve);
int load_cal_data(cal_data *ratios);
int load_trans_data(trans_data *coefs);
int load_plane_data(plane_data *curve);
void set_blood_ends(blood_data *blood);
void set_ROI_ends(ROI_data *ROI);
void get_ks(char *filename, float *a, float *lc);
void load_ks(char *filename, char *model, float *a, float *lc);
void get_h2o_ks(char *filename, float *a);
void strip_path(char *infile, char *outfile);
void strip_suff(char *infile, char *outfile);

/* save_PET_data.c */
int save_blood_data(blood_data *curve);
int save_ROI_data(ROI_data *curve);
int save_cal_data(cal_data *ratios);
int save_trans_data(trans_data *coefs);
int save_plane_data(plane_data *plane);

/* print_PET_data.c */
int print_blood_data(blood_data *blood);
int print_ROI_data(ROI_data *ROI);
int print_cal_data(cal_data *calib);
int print_plane_data(plane_data *plane);

/* marquardt_routines.c */
/* mrqmin & mrqcof declared in nr.h
 void mrqmin(float x[],float y[],float sig[],int ndata,float a[],int ma,
	    int *lista,int mfit,float **covar,float **alpha,
	    float *chisq,
	    void (*funcs)(float time, float *a, float *y, float *dyda,
	    int nparams),
	    float *alamda);
void mrqcof(float x[],float y[],float sig[],int ndata,float a[],int ma,
	    int *lista,int mfit,float **alpha,float *beta,float *chisq,
	    void (*funcs)(float time, float *a, float *y, float *dyda,
			  int nparams));
*/

/* void (*funcs)();*/
/* ANSI: void (*funcs)(float,float *,float *,float *,int); */  
void covsrt(float **covar,int ma,int *lista,int mfit);
void gaussj(float **a,int n,float **b,int m);

/* FDG_model_routines.c */
float conv_line_exp( float slope, float offset, float alpha, float Tmax,
float T1, float T2);
float FDG4K_ROI_estimate(float t, float *k);
void brooks(float t, float *k, float *c_rapid, float *c_slow);
void huang(float t, float *k, float *c_extravascular, float *c_metabolic);
int get_alphas(float k[], float *alpha1, float *alpha2);
int blood_value( float time_in, float *value);
float FDGTH_ROI_estimate(float t, float *kk);
void schmidt(float t, float *kk, float *c_e, float *c_m, float *intc_a);
int get_betas(float k[], float *beta1, float *beta2);
float FDGq_ROI_estimate(float t, float *k);
void q_model(float t, float *k, float *c_b, float *c_e, float *c_m,
	     float *intc_a);
float blood_estimate(float t, float *intc_a);
/* FDG_marquardt.c */
void FDG4K_model4fit(float time, float *a, float *y, float *dyda,
		     int nparams);
void FDG4K_marquardt_interface(ROI_data *ROI, float min_time, float max_time,
			       float *a, int ma, int method, int print);
void FDGTH_model4fit(float time, float *a, float *y, float *dyda, int nparams);
void FDGTH_marquardt_interface(ROI_data *ROI, float min_time, float max_time,
			       float  *a, int ma, int method, int print,
			       float CBV);
void FDGq_model4fit(float time, float *a, float *y, float *dyda,
		    int nparams);
void FDGq_marquardt_interface(ROI_data *ROI, float min_time, float max_time,
			      float *a, int ma, int method, int print);
/* smear_marquardt.c */
void smearSE_model4fit(float time, float *a, float *y, float *dyda,
		       int nparams);
void smearSE_marquardt_interface(ROI_data *ROI, float min_time, float max_time,
				 float *a, int ma, int method, int print);
void fpoly(float x, float p[], int np);
int blood_value2(float time_in, float *value, float *first_der,
		 float *second_der);
void smearPD_model4fit(float time, float *a, float *y, float *dyda,
		       int nparams);
void smearPD_marquardt_interface(ROI_data *ROI, float min_time, float max_time,
				 float *a, int ma, int method, int print);
/* poly_fit_routines.c */
/* svdfit declared in nr.h
void svdfit(float x[],float y[],float sig[],int ndata,float a[],int ma,
	    float **u,float **v,float w[],float *chisq,void (*funcs)());
*/
void svdcmp(float **a,int m,int n,float *w,float **v);
void svbksb(float **u,float w[],float **v,int m,int n,float b[],float x[]);
/* smear_model_routines.c */
/* float conv_line_exp(float slope, float offset, float alpha, float Tmax,
		    float T1, float T2); */
float smearSE_ROI_estimate(float t, float *k);
float smearPD_ROI_estimate(float t, float *k);

/* make_roi_pac.cc */
void make_roi_pac(char *infile, char *out_pac_fname, int debug);

#endif
