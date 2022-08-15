#include "header.h"

void compute_image_moment(
 double *image_arr,
 int width,
 int height,
 int l,
 int m,
 double *pmoment
)

/*
image_arr is a width*height grayscale image with values between 0.0 and 1.0
*/

/*
l is the degree of the image moment about the x axis
m is the degree of the image moment about the y axis
*/

{

 double a;
 double b;
 int i;
 int j;
 int pixel;
 double intensity_dbl;
 double moment;
 double x;
 double y;

 /*
 Compute the moment
 */

 /*
 Initialize the moment
 */

 moment= 0.0;

 /*
 Process the image pixels
 */

 for ( i= 0 ; i< height ; i++ ) {
    y= (double)i; 
    for ( j= 0 ; j< width ; j++ ) {
       x= (double)j;
       pixel= i*width+j;
       intensity_dbl= image_arr[pixel];
       a= pow(x,(double)l);
       b= pow(y,(double)m);

       /*
       Add to the moment
       */

       moment+= a*b*intensity_dbl;
    }
 }

 (*pmoment)= moment;

}
