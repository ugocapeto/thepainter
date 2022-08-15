#include "header.h"

void compute_difference_image_shiraishi_2(
 int *rgb_image_arr,
 int width,
 int height,
 int rgb_color[3],
 double **pdifference_image_arr
)

/*
difference_image_arr is a grayscale image with values between 0.0 and 1.0
If difference_image_arr[pixel] = 1.0,
pixel has same color as input color rgb_color
It's a bit counter-intuitive as we are talking about a difference image
*/

{ 

 double *difference_image_arr;
 int i;
 int j;
 int pixel;
 int diff2_int;
 double diff_dbl;
 int cind;
 double max_diff_dbl;
 double min_diff_dbl;
 double normalized_diff_dbl;

 /*
 Allocate memory for the difference image
 */

 difference_image_arr= (double *)calloc(width*height,sizeof(double));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       diff2_int= 0;
       for ( cind= 0 ; cind< 3 ; cind++ ) {
          diff2_int+= (rgb_image_arr[3*pixel+cind]-rgb_color[cind])*
                      (rgb_image_arr[3*pixel+cind]-rgb_color[cind]);
       }
       diff_dbl= sqrt((double)diff2_int);
       difference_image_arr[pixel]= diff_dbl;
    }
 }

 /*
 Normalize the difference image so that it has values between 0.0 and 1.0
 */

 max_diff_dbl=-1.0e32;
 min_diff_dbl=+1.0e32;

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       diff_dbl= difference_image_arr[pixel];
       if ( diff_dbl < min_diff_dbl )
        min_diff_dbl= diff_dbl;
       if ( diff_dbl > max_diff_dbl )
        max_diff_dbl= diff_dbl;
    }
 }

 /*
 We have to check for the special case
 when all color differences are exactly the same
 This can happen when all pixels in rgb_image_arr have the same color
 */

 if ( max_diff_dbl == min_diff_dbl ) {

    /*
    Do as if all pixels had same color as input color, that is,
    give a value of 1.0 to all pixels
    */

    for ( i= 0 ; i< height ; i++ ) {
       for ( j= 0 ; j< width ; j++ ) {
          pixel= i*width+j;
          difference_image_arr[pixel]= 1.0;
       }
    }

    goto END;
 }

 /*
 The closer the pixel color is to the input color,
 the closer to 1.0 its value is gonna be
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       diff_dbl= difference_image_arr[pixel];
       normalized_diff_dbl= (diff_dbl-min_diff_dbl)/(max_diff_dbl-min_diff_dbl);

       normalized_diff_dbl= 1.0-normalized_diff_dbl;

       if ( !(normalized_diff_dbl >= 0.0) ) {
          error_handler((char *)"compute_difference_image_shiraishi_2");
       }
       if ( !(normalized_diff_dbl <= 1.0) ) {
          error_handler((char *)"compute_difference_image_shiraishi_2");
       }
       difference_image_arr[pixel]= normalized_diff_dbl;
    }
 }

 END:

 (*pdifference_image_arr)= difference_image_arr;

}
