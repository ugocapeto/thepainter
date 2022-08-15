#include "header.h"

void compute_difference_image_shiraishi(
 int *rgb_image_arr,
 int width,
 int height,
 int rgb_color[3],
 double **pdifference_image_arr
)

/*
difference_image_arr is a grayscale image with values between 0.0 and 1.0
*/

{ 

 double *Lab_image_arr;
 double x;
 double y;
 double z;
 double Lab_color[3];
 double *difference_image_arr;
 int i;
 int j;
 int pixel;
 double diff2_dbl;
 double d;
 double d0= 150.0;
 int cind;
 double diff_dbl;
 double temp_dbl;
 double intensity_dbl;

 /*
 Allocate memory for the Lab image
 */

 Lab_image_arr= (double *)calloc(width*height,3*sizeof(double));

 /*
 Convert rgb image to Lab image
 */

 rgb_image_to_Lab(
  rgb_image_arr,
  Lab_image_arr,
  width,
  height
 );

 /*
 Convert rgb color to Lab color
 */

 rgb2xyz(
  rgb_color[0],
  rgb_color[1],
  rgb_color[2],
  &x,
  &y,
  &z
 );
 xyz2Lab(
  x,
  y,
  z,
  &Lab_color[0],
  &Lab_color[1],
  &Lab_color[2]
 );

 /*
 Allocate memory for the difference image
 */

 difference_image_arr= (double *)calloc(width*height,sizeof(double));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       diff2_dbl= 0.0;
       for ( cind= 0 ; cind< 3 ; cind++ ) {
          diff2_dbl+= (Lab_image_arr[3*pixel+cind]-Lab_color[cind])*
                      (Lab_image_arr[3*pixel+cind]-Lab_color[cind]);
       }
       diff_dbl= sqrt(diff2_dbl);
       d= diff_dbl;
       if ( d < d0 ) {
          temp_dbl= d/d0;
          intensity_dbl= 1.0-temp_dbl*temp_dbl;
          intensity_dbl*= intensity_dbl;
       }
       else {
          intensity_dbl= 0.0;
       }
       difference_image_arr[pixel]= intensity_dbl;
    }
 }

 (*pdifference_image_arr)= difference_image_arr;

}
