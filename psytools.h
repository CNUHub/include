#ifndef __psytools_h
#define __psytools_h

/* Sort array a[] in place
   n = (input) size of arrays a[] and b[]
   a[] = (input/output) array to sort in place
*/
void shellsort(unsigned int n, double a[]);
/* Sort array a[] in place with values in b[] also swapped to maintain
 same relative order
  n = (input) size of arrays a[] and b[]
  a[] = (input/output) array to sort in place
  b[] = (input/output) array to order in place with the same
  re-ordering as a[]
*/
void shellsort(unsigned int n, double a[], double b[]);
/* Replace values in sorted array w[] with rank values
   n = (input) size of array w[]
   w[] = (input/output) array already sorted in increasing order whose
                        values are to be replaced with rank numbers
   *s = (output) returns the sum of (f^3 - f) where f is the number
                 of elements in each tie
 */
void crank(unsigned int n, double w[], double *s);
/* Calculate the Spearman Rank-Order Correlation Coefficient for two
 arrays of ranked data
 n = (input) size of arrays rank1[] and rank2[]
 rank1[] = (input) array of rank values
 sf = (input) sum of (f^3 - f) where f is the number of elements
 in each tie from rank1
 rank2[] = (input) array of rank values
 sg = (input) sum of (f^3 - f) where f is the number of elements
 in each tie from rank2
 *d = (output) returns sum of square difference of rank
 return = (output) returns linear correlation coefficient of the ranks
*/
double spear(unsigned int n,
	     double rank1[], double sf, double rank2[], double sg);
/* Calculate natural log of gamma function */
double gammln(double xx);
/* Evaluates continued fraction for incomplete beta function */
double betacf( double a, double b, double x);
/* Calculate the incomplete Beta Function Ix(a,b) */
double betai(double a, double b, double x);

#endif
