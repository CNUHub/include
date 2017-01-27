#ifndef __cnunifti_h
#define __cnunifti_h
#include "psyanalyze.h"

enum cnuniftiform { niiform, ni1form };

/*----- another set of names for standard analyze codes ---*/
#define DT_UINT8 2
#define DT_INT16 4
#define DT_INT32 8
#define DT_FLOAT32 16
#define DT_COMPLEX64 32
#define DT_FLOAT64 64
#define DT_RGB24 128
/*--- This code most be from Analyze 7.5 */
#define DT_ALL                   255     // not very useful (?)          /

/*------------------- new codes for NIFTI ---*/
#define DT_INT8 256 // signed char (8 bits) /
#define DT_UINT16 512 // unsigned short (16 bits) /
#define DT_UINT32 768 // unsigned int (32 bits) /
#define DT_INT64 1024 // long long (64 bits) /
#define DT_UINT64 1280 // unsigned long long (64 bits) /
#define DT_FLOAT128 1536 // long double (128 bits) /
#define DT_COMPLEX128 1792 // double pair (128 bits) /
#define DT_COMPLEX256 2048 // long double pair (256 bits) /

/*------- aliases for all the above codes ---*/
#define NIFTI_TYPE_UINT8 2 // unsigned char. /
#define NIFTI_TYPE_INT16 4 // signed short. /
#define NIFTI_TYPE_INT32 8 // signed int. /
#define NIFTI_TYPE_FLOAT32 16 // 32 bit float. /
#define NIFTI_TYPE_COMPLEX64 32 // 64 bit complex = 2 32 bit floats. /
#define NIFTI_TYPE_FLOAT64 64 // 64 bit float = double. /
#define NIFTI_TYPE_RGB24 128 // 3 8 bit bytes. /
#define NIFTI_TYPE_INT8 256 // signed char. /
#define NIFTI_TYPE_UINT16 512 // unsigned short. /
#define NIFTI_TYPE_UINT32 768 // unsigned int. /
#define NIFTI_TYPE_INT64 1024 // signed long long. /
#define NIFTI_TYPE_UINT64 1280 // unsigned long long. /
#define NIFTI_TYPE_FLOAT128 1536 // 128 bit float = long double. /
#define NIFTI_TYPE_COMPLEX128 1792 // 128 bit complex = 2 64 bit floats. /
#define NIFTI_TYPE_COMPLEX256 2048 // 256 bit complex = 2 128 bit floats / 


#define NIFTI_UNITS_UNKNOWN 0 // NIFTI code for unspecified units. /

// Space codes are multiples of 1. / 
#define NIFTI_UNITS_METER 1 // NIFTI code for meters. / 
#define NIFTI_UNITS_MM 2 // NIFTI code for millimeters. / 
#define NIFTI_UNITS_MICRON 3 // NIFTI code for micrometers. /

// Time codes are multiples of 8. / 
#define NIFTI_UNITS_SEC 8 // NIFTI code for seconds. / 
#define NIFTI_UNITS_MSEC 16 // NIFTI code for milliseconds. / 
#define NIFTI_UNITS_USEC 24 // NIFTI code for microseconds. /

// These units are for spectral data.  /
#define NIFTI_UNITS_HZ 32 // NIFTI code for Hertz. / 
#define NIFTI_UNITS_PPM 40 // NIFTI code for ppm. / 
#define NIFTI_UNITS_RADS 48 // NIFTI code for radians per second.

#define XYZT_TO_SPACE(xyzt)       ( (xyzt) & 0x07 )
#define XYZT_TO_TIME(xyzt)        ( (xyzt) & 0x38 )
#define SPACE_TIME_TO_XYZT(ss,tt) (  (((char)(ss)) & 0x07)   \
                                   | (((char)(tt)) & 0x38) )

#define NIFTI_SLICE_UNKNOWN  0
#define NIFTI_SLICE_SEQ_INC  1
#define NIFTI_SLICE_SEQ_DEC  2
#define NIFTI_SLICE_ALT_INC  3
#define NIFTI_SLICE_ALT_DEC  4

#define DIM_INFO_TO_FREQ_DIM(di)   ( ((di)     ) & 0x03 )
#define DIM_INFO_TO_PHASE_DIM(di)  ( ((di) >> 2) & 0x03 )
#define DIM_INFO_TO_SLICE_DIM(di)  ( ((di) >> 4) & 0x03 )

#define FPS_INTO_DIM_INFO(fd,pd,sd) ( ( ( ((char)(fd)) & 0x03) ) | ( ( ((char)(pd)) & 0x03) << 2 ) | ( ( ((char)(sd)) & 0x03) << 4 ) )

/*! Arbitrary coordinates (Method 1). */
#define NIFTI_XFORM_UNKNOWN      0
/*! Scanner-based anatomical coordinates */
#define NIFTI_XFORM_SCANNER_ANAT 1
/*! Coordinates aligned to another file's, or to anatomical "truth".            */
#define NIFTI_XFORM_ALIGNED_ANAT 2
/*! Coordinates aligned to Talairach-Tournoux Atlas; (0,0,0)=AC, etc. */
#define NIFTI_XFORM_TALAIRACH    3
/*! MNI 152 normalized coordinates. */
#define NIFTI_XFORM_MNI_152      4

 /*! default: no intention is indicated in the header. */
#define NIFTI_INTENT_NONE        0
    /*-------- These codes are for probability distributions ---------------*/
    /* Most distributions have a number of parameters,
       below denoted by p1, p2, and p3, and stored in
        - intent_p1, intent_p2, intent_p3 if dataset doesn't have 5th dimension
        - image data array                if dataset does have 5th dimension

       Functions to compute with many of the distributions below can be found
       in the CDF library from U Texas.

       Formulas for and discussions of these distributions can be found in the
       following books:

        [U] Univariate Discrete Distributions,
            NL Johnson, S Kotz, AW Kemp.

        [C1] Continuous Univariate Distributions, vol. 1,
             NL Johnson, S Kotz, N Balakrishnan.

        [C2] Continuous Univariate Distributions, vol. 2,
             NL Johnson, S Kotz, N Balakrishnan.                            */
    /*----------------------------------------------------------------------*/
  /*! [C2, chap 32] Correlation coefficient R (1 param):
       p1 = degrees of freedom
       R/sqrt(1-R*R) is t-distributed with p1 DOF. */
/*! \defgroup NIFTI1_INTENT_CODES
    \brief nifti1 intent codes, to describe intended meaning of dataset contents
    @{
 */
#define NIFTI_INTENT_CORREL      2
  /*! [C2, chap 28] Student t statistic (1 param): p1 = DOF. */
#define NIFTI_INTENT_TTEST       3
  /*! [C2, chap 27] Fisher F statistic (2 params):
       p1 = numerator DOF, p2 = denominator DOF. */
#define NIFTI_INTENT_FTEST       4
  /*! [C1, chap 13] Standard normal (0 params): Density = N(0,1). */
#define NIFTI_INTENT_ZSCORE      5
  /*! [C1, chap 18] Chi-squared (1 param): p1 = DOF.
      Density(x) proportional to exp(-x/2) * x^(p1/2-1). */
#define NIFTI_INTENT_CHISQ       6
  /*! [C2, chap 25] Beta distribution (2 params): p1=a, p2=b.
      Density(x) proportional to x^(a-1) * (1-x)^(b-1). */
#define NIFTI_INTENT_BETA        7
  /*! [U, chap 3] Binomial distribution (2 params):
       p1 = number of trials, p2 = probability per trial.
      Prob(x) = (p1 choose x) * p2^x * (1-p2)^(p1-x), for x=0,1,...,p1. */
#define NIFTI_INTENT_BINOM       8
  /*! [C1, chap 17] Gamma distribution (2 params):
       p1 = shape, p2 = scale.
      Density(x) proportional to x^(p1-1) * exp(-p2*x). */
#define NIFTI_INTENT_GAMMA       9
  /*! [U, chap 4] Poisson distribution (1 param): p1 = mean.
      Prob(x) = exp(-p1) * p1^x / x! , for x=0,1,2,.... */
#define NIFTI_INTENT_POISSON    10
  /*! [C1, chap 13] Normal distribution (2 params):
       p1 = mean, p2 = standard deviation. */
#define NIFTI_INTENT_NORMAL     11
  /*! [C2, chap 30] Noncentral F statistic (3 params):
       p1 = numerator DOF, p2 = denominator DOF,
       p3 = numerator noncentrality parameter.  */
#define NIFTI_INTENT_FTEST_NONC 12
  /*! [C2, chap 29] Noncentral chi-squared statistic (2 params):
       p1 = DOF, p2 = noncentrality parameter.     */
#define NIFTI_INTENT_CHISQ_NONC 13
  /*! [C2, chap 23] Logistic distribution (2 params):
       p1 = location, p2 = scale.
      Density(x) proportional to sech^2((x-p1)/(2*p2)). */
#define NIFTI_INTENT_LOGISTIC   14
  /*! [C2, chap 24] Laplace distribution (2 params):
       p1 = location, p2 = scale.
      Density(x) proportional to exp(-abs(x-p1)/p2). */
#define NIFTI_INTENT_LAPLACE    15
  /*! [C2, chap 26] Uniform distribution: p1 = lower end, p2 = upper end. */
#define NIFTI_INTENT_UNIFORM    16
  /*! [C2, chap 31] Noncentral t statistic (2 params):
       p1 = DOF, p2 = noncentrality parameter. */
#define NIFTI_INTENT_TTEST_NONC 17
  /*! [C1, chap 21] Weibull distribution (3 params):
       p1 = location, p2 = scale, p3 = power.
      Density(x) proportional to
       ((x-p1)/p2)^(p3-1) * exp(-((x-p1)/p2)^p3) for x > p1. */
#define NIFTI_INTENT_WEIBULL    18
  /*! [C1, chap 18] Chi distribution (1 param): p1 = DOF.
      Density(x) proportional to x^(p1-1) * exp(-x^2/2) for x > 0.
       p1 = 1 = 'half normal' distribution
       p1 = 2 = Rayleigh distribution
       p1 = 3 = Maxwell-Boltzmann distribution.                  */
#define NIFTI_INTENT_CHI        19
  /*! [C1, chap 15] Inverse Gaussian (2 params):
       p1 = mu, p2 = lambda
      Density(x) proportional to
       exp(-p2*(x-p1)^2/(2*p1^2*x)) / x^3  for x > 0. */
#define NIFTI_INTENT_INVGAUSS   20
  /*! [C2, chap 22] Extreme value type I (2 params):
       p1 = location, p2 = scale
      cdf(x) = exp(-exp(-(x-p1)/p2)). */
#define NIFTI_INTENT_EXTVAL     21
  /*! Data is a 'p-value' (no params). */
#define NIFTI_INTENT_PVAL       22
  /*! Data is ln(p-value) (no params).
      To be safe, a program should compute p = exp(-abs(this_value)).
      The nifti_stats.c library returns this_value
      as positive, so that this_value = -log(p). */
#define NIFTI_INTENT_LOGPVAL    23
  /*! Data is log10(p-value) (no params).
      To be safe, a program should compute p = pow(10.,-abs(this_value)).
      The nifti_stats.c library returns this_value
      as positive, so that this_value = -log10(p). */
#define NIFTI_INTENT_LOG10PVAL  24
  /*! Smallest intent_code that indicates a statistic. */
#define NIFTI_FIRST_STATCODE     2
  /*! Largest intent_code that indicates a statistic. */
#define NIFTI_LAST_STATCODE     24
 /*---------- these values for intent_code aren't for statistics ----------*/
 /*! To signify that the value at each voxel is an estimate
     of some parameter, set intent_code = NIFTI_INTENT_ESTIMATE.
     The name of the parameter may be stored in intent_name.     */
#define NIFTI_INTENT_ESTIMATE  1001
 /*! To signify that the value at each voxel is an index into
     some set of labels, set intent_code = NIFTI_INTENT_LABEL.
     The filename with the labels may stored in aux_file.        */
#define NIFTI_INTENT_LABEL     1002
 /*! To signify that the value at each voxel is an index into the
     NeuroNames labels set, set intent_code = NIFTI_INTENT_NEURONAME. */
#define NIFTI_INTENT_NEURONAME 1003
 /*! To store an M x N matrix at each voxel:
       - dataset must have a 5th dimension (dim[0]=5 and dim[5]>1)
       - intent_code must be NIFTI_INTENT_GENMATRIX
       - dim[5] must be M*N
       - intent_p1 must be M (in float format)
       - intent_p2 must be N (ditto)
       - the matrix values A[i][[j] are stored in row-order:
         - A[0][0] A[0][1] ... A[0][N-1]
         - A[1][0] A[1][1] ... A[1][N-1]
         - etc., until
         - A[M-1][0] A[M-1][1] ... A[M-1][N-1]        */
#define NIFTI_INTENT_GENMATRIX 1004
 /*! To store an NxN symmetric matrix at each voxel:
       - dataset must have a 5th dimension
       - intent_code must be NIFTI_INTENT_SYMMATRIX
       - dim[5] must be N*(N+1)/2
       - intent_p1 must be N (in float format)
       - the matrix values A[i][[j] are stored in row-order:
         - A[0][0]
         - A[1][0] A[1][1]
         - A[2][0] A[2][1] A[2][2]
         - etc.: row-by-row                           */
#define NIFTI_INTENT_SYMMATRIX 1005
 /*! To signify that the vector value at each voxel is to be taken
     as a displacement field or vector:
       - dataset must have a 5th dimension
       - intent_code must be NIFTI_INTENT_DISPVECT
       - dim[5] must be the dimensionality of the displacment
         vector (e.g., 3 for spatial displacement, 2 for in-plane) */
#define NIFTI_INTENT_DISPVECT  1006   /* specifically for displacements */
#define NIFTI_INTENT_VECTOR    1007   /* for any other type of vector */
 /*! To signify that the vector value at each voxel is really a
     spatial coordinate (e.g., the vertices or nodes of a surface mesh):
       - dataset must have a 5th dimension
       - intent_code must be NIFTI_INTENT_POINTSET
       - dim[0] = 5
       - dim[1] = number of points
       - dim[2] = dim[3] = dim[4] = 1
       - dim[5] must be the dimensionality of space (e.g., 3 => 3D space).
       - intent_name may describe the object these points come from
         (e.g., "pial", "gray/white" , "EEG", "MEG").                   */
#define NIFTI_INTENT_POINTSET  1008
 /*! To signify that the vector value at each voxel is really a triple
     of indexes (e.g., forming a triangle) from a pointset dataset:
       - dataset must have a 5th dimension
       - intent_code must be NIFTI_INTENT_TRIANGLE
       - dim[0] = 5
       - dim[1] = number of triangles
       - dim[2] = dim[3] = dim[4] = 1
       - dim[5] = 3
       - datatype should be an integer type (preferably DT_INT32)
       - the data values are indexes (0,1,...) into a pointset dataset. */
#define NIFTI_INTENT_TRIANGLE  1009
 /*! To signify that the vector value at each voxel is a quaternion:
       - dataset must have a 5th dimension
       - intent_code must be NIFTI_INTENT_QUATERNION
       - dim[0] = 5
       - dim[5] = 4
       - datatype should be a floating point type     */
#define NIFTI_INTENT_QUATERNION 1010
 /*! Dimensionless value - no params - although, as in _ESTIMATE 
     the name of the parameter may be stored in intent_name.     */
#define NIFTI_INTENT_DIMLESS    1011
 /*---------- these values apply to GIFTI datasets ----------*/
 /*! To signify that the value at each location is from a time series. */
#define NIFTI_INTENT_TIME_SERIES  2001
 /*! To signify that the value at each location is a node index, from
     a complete surface dataset.                                       */
#define NIFTI_INTENT_NODE_INDEX   2002
 /*! To signify that the vector value at each location is an RGB triplet,
     of whatever type.
       - dataset must have a 5th dimension
       - dim[0] = 5
       - dim[1] = number of nodes
       - dim[2] = dim[3] = dim[4] = 1
       - dim[5] = 3
    */
#define NIFTI_INTENT_RGB_VECTOR   2003
 /*! To signify that the vector value at each location is a 4 valued RGBA
     vector, of whatever type.
       - dataset must have a 5th dimension
       - dim[0] = 5
       - dim[1] = number of nodes
       - dim[2] = dim[3] = dim[4] = 1
       - dim[5] = 4
    */
#define NIFTI_INTENT_RGBA_VECTOR  2004
 /*! To signify that the value at each location is a shape value, such
     as the curvature.  */
#define NIFTI_INTENT_SHAPE        2005
/* @} */


/**
  * Stores the header key portion of an NIFTI header.
  *
  * @author	Joel T. Lee
  * @version %I%, %G%
  */
struct nifti_1_header {
  /* off + size*/
  int sizeof_hdr;			/* 0 + 4     */ /*!< MUST be 348           */
  char data_type[10];	/* 4 + 10    */ /* nifti unused */
  char db_name[18];	/* 14 + 18   */ /* nifti unused */
  int extents;			/* 32 + 4    */ /* nifti unused */
  short session_error;		/* 36 + 2    */ /* nifti unused */
  char regular;			/* 38 + 1    */ /* nifti unused */
  //char hkey_un0;			/* 39 + 1    */
  char dim_info;			/* 39 + 1    */
 /* MRI slice ordering */
  short dim[8];	        /* 40 + 16    */
  //char[] vox_units=new char[4];	/* 40 + 4    */
  float intent_p1;                    /* 56 + 4    */ /* 1st intent parameter */
  //char[] cal_units=new char[8];	/* 60 + 4    */
  float intent_p2;                    /* 60 + 4    */ /* 2nd intent parameter */
  float intent_p3;                    /* 64 + 4    */ /* 3rd intent parameter */
  //short unused1;			/* 68 + 2    */
  short intent_code;			/* 68 + 2    */ /* NIFTI INTENT code. */
  short datatype;			/* 70 + 2    */
  short bitpix;			/* 72 + 2    */
  //short dim_un0;			/* 74 + 2    */
  short slice_start;			/* 74 + 2    */
  float pixdim[8];	/* 76 + 32   */
  /* 
   * pixdim[] specifies the voxel dimensions:
   * pixdim[0] - quantification - my own invent jtl
   * pixdim[1] - voxel width
   * pixdim[2] - voxel height
   * pixdim[3] - interslice distance
   * ..etc
  */
  float vox_offset;		        /* 108 + 4    */
  float scl_slope;			/* 112 + 4    */ /* Data scaling: slope. */
  //float funused1;			/* 112 + 4    */
  float scl_inter;			/* 116 + 4    */ /* Data scaling: offset. */
  //float funused2;			/* 116 + 4    */
  short slice_end;			/* 120 + 2    */ /* Last slice index. */
  char slice_code;			/* 122 + 1    */ /* Slice timing order. */
  char xyzt_units;			/* 123 + 1    */ /* Units of pixdim[1..4]. */
  //float funused3;			/* 120 + 4    */
  float cal_max; 			/* 124 + 4    */ /* Max display intensity */
  float cal_min;			/* 128 + 4    */ /* Min display intensity */
  //int compressed;			/* 132 + 4    */
  float slice_duration;		/* 132 + 4    */ /* Time for 1 slice. */
  float toffset;		        /* 136 + 4    */ /* Time axis shirt. */
  //int verified;			/* 136 + 4    */
  int glmax, glmin;			/* 140 + 8    */ /* unused */

  char descrip[80];	/* 148 + 80   */ /* any text you like. */
  char aux_file[24];	/* 228 + 24   */ /* auxiliary filename */
  short qform_code;                   /* 252 + 2    */ /*!< NIFTIXFORM code. */ /*-- all ANALYZE 7.5 ---*/
  short sform_code;                   /* 254 + 2    */ /*!< NIFTIXFORM code. */ /* fields below here */
                                                                                  /* are replaced */
  float quatern_b;			/* 256 + 4    */ /*!< Quaternion b param. */
  float quatern_c;		        /* 260 + 4    */ /*!< Quaternion c param. */
  float quatern_d; 			/* 264 + 4    */ /*!< Quaternion d param. */
  float qoffset_x;			/* 268 + 4    */ /*!< Quaternion x shift. */
  float qoffset_y;			/* 272 + 4    */ /*!< Quaternion y shift. */
  float qoffset_z;			/* 276 + 4    */ /*!< Quaternion z shift. */

  float srow_x[4];	/* 280 + 16    */ /*!< 1st row affine transform. */
  float srow_y[4]; 	/* 296 + 16    */ /*!< 2nd row affine transform. */
  float srow_z[4]; 	/* 312 + 16    */ /*!< 3rd row affine transform. */

  char intent_name[16];	/* 328 + 16    */ /*!< name or meaning of data. */

  char magic[4];		/* 344 + 4    */ /*< MUST be "ni1\0" or "n+1\0". */
  char extender[4];
};

cnuniftiform bldniftifilenames(string primaryname, string *imgname=NULL,
			       string *hdrname=NULL, string *combinedname=NULL);

int validniftihdr(nifti_1_header *rawhdr);

int isniftifile(string filename);

psytype getnifticlosesttype(psytype type);

nifti_1_header *readNiftiHeader(string primaryname, nifti_1_header *rawhdr=NULL,
				fstream **fdptrptr=NULL,
				psyswaptype *swaptypeptr=NULL);

int writeNiftiHeader(nifti_1_header *rawhdr, string primaryname, fstream **fdptrptr);

void outputNiftiSliceCodeName(int slice_code, ostream *out);

void outputNiftiIntentName(int niftiIntent, ostream *out);

void outputNiftiDataTypeName(int datatype, ostream *out);

void outputNiftiSpaceUnitsName(int xyzt_units, ostream *out);

imagespacecode niftiformcode2spacecode(int niftiformcode);

int spacecode2niftiformcode(imagespacecode spacecode);

void outputNiftiTimeUnitsName(int xyzt_units, ostream *out);

class niftifile : public rawfile {
 protected:
  fstream *hdrfdptr;
  string hdrfilename;
  nifti_1_header rawhdr;
  cnuniftiform niftiform;
  void writetofiles();
 public:
  niftifile(string fname, const char *mode=NULL, int ignore_valid=0);
  niftifile(string fname, psyimg *psyimgptr, psytype pixeltype=psynotype, nifti_1_header *inheader=NULL);
  virtual ~niftifile();
  void output_tree(ostream *out) {rawfile::output_tree(out);*out<<"::niftifile";};
  void openniftifiles(string fname, const char *mode);
  void buildniftiheader(nifti_1_header *niftihdrptr=NULL);
  nifti_1_header  *getniftiheader(nifti_1_header *niftihdrptr=NULL);
  static void showhdr( nifti_1_header *rawhdr, ostream *out= &cout);
  static void showhdr( nifti_1_header rawhdr);
  void showhdr();
};

#endif
