#ifndef __PET_analysis_h
#define __PET_analysis_h
/* PET_analysis.h

This little library defines a few constants and data structures
that are necessary for the routines that analyze PET data.
*/


/* CONSTANTS */

#define FILEMAX 81	/* max number of characters to represent filename */
#define NSCAN 51	/* max number of scan data points expected */
#define NBLOOD 51	/* max number of blood data points expected */
#define NROI 51		/* max number of ROI data points expected */


/* CONSTANTS FOR FDG ANALYSES */

#define NPARMS 5	/* number of parameters in FDG model (k1-4, CBV) */
#define ARRPARM 6	/* number of parameters + 1 for arrays (k1-4, CBV)*/
#define DEF_CRIT 0.40		/* default hematocrit if it is not measured */
#define CRIT_COEF 0.1839	/* Represents mean fractional RBC uptake in blood */
#define CAP_COEF 0.69		/* Ratio of capillary/large vessel hematocrit */


/* TIME UNITS, complements 'xun=' keyword. */

#ifdef SEC
#undef SEC
#endif
#define SEC "sec"
#define MSEC "msec"
#define MIN "min"
#define HRS "hrs"


/* SIGNAL UNITS, complements 'yun=', 'Wun=' and 'Eun' keywords.  */

#define DECAYED_WELLVOL "Well Mcpm/ml volume"
#define CORRECT_WELLVOL "Well Mcpm|t=0/ml volume"
#define DECAYED_WELLPLS "Well Mcpm/ml plasma"
#define CORRECT_WELLPLS "Well Mcpm|t=0/ml plasma"
#define DECAYED_WELLBLD "Well Mcpm/ml blood"
#define CORRECT_WELLBLD "Well Mcpm|t=0/ml blood"
#define DECAYED_TOTAL "Total counts"
#define DECAYED_ECATS "ECAT counts per pixel per second"
#define CORRECT_ECATS "ECAT counts|t=0 per pixel per second"

/* TRANSFORMATION UNITS, complements 'Tun=' keyword. */

#define CMRGLU "mg Glucose/min.100ml tissue"

/* FLAGS */

#define ERFLAG -1
#define NOERFLAG 0


/* FILE NAMES AND EXTENSIONS */

#define TIMEACT ".tac"		/* suffix for any time activity curve */
#define RAWBLD  ".rbl"		/* suffix for raw blood file */
#define BLD	"bld.tac"	/* suffix for blood tac file */
#define CPT	".cpt"		/* suffix for ECAT ROI time activity curves */
#define CAL	".cal"		/* suffix for calibration files */
#define LTC	".ltc"		/* suffix for linear transformation files */
#define PAC	".pac"		/* suffix for plane activity curves */
#define ROITAC  "roi.tac"	/* suffix for roi time activity curve */
#define ROIPAC  "roi.pac"	/* suffix for circular ROI pac's */
#define THRPAC  "thr.pac"	/* suffix for thresholded ROI pac's */
#define CBLD "_bld.tac"     /* suffix for corrected bloode tac file */

/* DEFAULT DIRECTORIES FOR CERTAIN DATA TYPES */
/*
#define BLOODDIR "/home/cauchy/ecat/blood/"
#define CALIBDIR "/home/cauchy/ecat/calib/"
#define IMAGEDIR "/home/xeno/public/data/"
*/
#define BLOODDIR "./"
#define CALIBDIR "./"
#define IMAGEDIR "./"


/* KEYWORDS */
/* These keywords are used to identify important information associated with data files
   The files that will hold these keywords are .dcx, .tac and .cal files
	! = information important for ROI_data
	# = information important for blood_data
	$ = inforamtion important for cal_data
*/

#define FILEKEY "fil="		/* !# name of file holding data */
#define NAMEKEY "nam="		/* !# patient's name */
#define RADIOPHARMKEY "rad="	/* !# abbreviation for radiopharmaceutical, ex FDG */
#define ISOTOPEKEY "iso="	/* !# mneumonic of isotope, ex F18 */
#define DATEKEY "dat="		/* !# date is dd.mm.yy  ex. 01.06.92 = 1 July, 1992 */
#define TIMEKEY "tim="		/* !# time of initiation hh:mm:ss  ex. 13:22:57 */
#define DELAYKEY "del="		/* #  delay time of blood samples */
#define DISPKEY "dsp="		/* #  dispersion time constant for blood samples */
#define CRITKEY "crt="		/* #  hematocrit of blood samples */
#define XUNITSKEY "xun="	/* !# units of time used */
#define YUNITSKEY "yun="	/* !# units for signal used */
#define TRANSUNITS "Tun="	/*    signal units for quantitative images */
#define WELLUNITS "Wun="	/* $  signal units of well counter */
#define ECATUNITS "Eun="	/* $  signal units of ECAT PET scanner */
#define PLANEKEY "pln="		/* !  plane from which ROI data was taken */
#define ACTIVITYKEY "act="	/* $  specific activity of phantom */
#define GLUCOSEKEY "glu="	/*    glucose concentration in blood */
#define AUTOTIMEKEY "aut="	/*    time at which autoradiography is applied */
#define DURATIONKEY "dur="	/*    duration of frame in plane activity curve */
#define METHODKEY "met="	/*    method used to create file */
#define RCLKEY	  "rcl="	/*    file holding rcl data for cal */
#define PACKEY	  "pac="	/*    file holding pac data for cal */

/* DATA STRUCTURES */

typedef struct {

	char filename[FILEMAX];	/* name of file supplying the data */
	char lastname[21];	/* patient's last name */
	char firstname[21];	/* patient's first name */
	char radiopharm[21];	/* radiopharmaceutical */
	char isotope[11];	/* isotope */

	int date[3];		/* date of study */
	int time[3];		/* time when data collection started */

	float delay;		/* relative delay time (s) of data from actual occurence */
	float disp;		/* dispersion time constant (s) associated with data smear */
	float crit;		/* fraction of RBC in the volume of these samples */
	float cap_factor;	/* ratio of cap blood act:(plasma act or whole blood act) */
	float tissue_factor;	/* ratio of plasma act:(plasma act or whole blood) */

	char xunits[11];	/* units used to express time base */
	char yunits[41];	/* units used to express signal intensity */
	int plane;		/* plane from which data was taken, 0 = blood draw */

	int n_samples;		/* number of data points  */
	float xinit[NBLOOD];	/* array of times when data samplings were initiated */
	float xdur[NBLOOD];	/* array of time durations of sampling */
	float xtime[NBLOOD];	/* array of times referring to middle of sample interval */
	float ysignal[NBLOOD];	/* array of signal intensity data */
	float ystdev[NBLOOD];	/* array of standard deviations associated with signal */

} blood_data;


typedef struct {

	char filename[FILEMAX];	/* name of file supplying the data */
	char lastname[21];	/* patient's last name */
	char firstname[21];	/* patient's first name */
	char radiopharm[21];	/* radiopharmaceutical */
	char isotope[11];	/* isotope */

	int date[3];		/* date of study */
	int time[3];		/* time when data collection started */

	char xunits[11];	/* units used to express time base */
	char yunits[41];	/* units used to express signal intensity */
	int plane;		/* plane from which data was taken */

	int n_samples;		/* number of data points  */
	float xinit[NROI];	/* array of times when data samplings were initiated */
	float xdur[NROI];	/* array of time durations of sampling */
	float xtime[NROI];	/* array of times referring to middle of sample interval */
	float ysignal[NROI];	/* array of signal intensity data */
	float ystdev[NROI];	/* array of standard deviations associated with signal */

} ROI_data;


typedef struct {

	char filename[FILEMAX];	/* name of cal file */
	char isotope[11];	/* isotope */
	char rcl_file[FILEMAX]; /* name of rcl file used in creating cal file */
	char pac_file[FILEMAX]; /* name of pac file used to create cal file */

	int date[3];		/* date of study */
	float specific_act;	/* specific activity of phantom (uCi/ml) */

	char Wellunits[41];	/* units used to express Well counter data*/
	char Ecatunits[41];	/* units used to express PET scanner data */

	int n_planes;		/* number of planes represented  */
	float ratio_W2E[32];	/* ratios of well units to ecat units for every plane*/

} cal_data;


typedef struct {

	char filename[FILEMAX];	/* name of file supplying the data */
	char lastname[21];	/* patient's last name */
	char firstname[21];	/* patient's first name */
	char radiopharm[21];	/* radiopharmaceutical */
	char isotope[11];	/* isotope */
	int date[3];		/* date of study */
	int time[3];		/* time when data collection started */

	char Transunits[41];	/* units used to express Transformed image*/
	char Ecatunits[41];	/* units used to express PET scanner data */
	float glucose;		/* glucose concentration used to create this file */
	float auto_time;	/* time at which transformation is to be applied */
	char method[21];	/* method used to create the transformation */

	int n_planes;		/* number of planes represented  */
	float coef0[32];	/* zeroth order coefficient for linear transformation */
	float coef1[32];	/* first order coefficient for linear transformation */

} trans_data;


typedef struct {

	char filename[FILEMAX];	/* name of pac file */
	char isotope[11];	/* isotope */

	int date[3];		/* date of study */
	int time[3];		/* time of study */

	float duration;		/* duration of frame */
	char xunits[11];	/* units used to express time */
	char Ecatunits[41];	/* units used to express PET scanner data */

	int n_planes;		/* number of planes represented  */
	float signal[32];	/* total signal in ecat units for every plane */

} plane_data;

#endif
