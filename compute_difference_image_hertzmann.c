#include "header.h"

void compute_difference_image_hertzmann(
 int *rgb_image_arr1,
 int *rgb_image_arr2,
 int width,
 int height,
 double **pdifference_image_arr
)

{

 double *difference_image_arr;
 int i;
 int j;
 int pixel;
 int diff2_int;
 double diff_dbl;
 int cind;

 /*
 Allocate memory for the difference image
 */

 difference_image_arr= (double *)calloc(width*height,sizeof(double));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       diff2_int= 0;
       for ( cind= 0 ; cind< 3 ; cind++ ) {
          diff2_int+= (rgb_image_arr1[3*pixel+cind]-rgb_image_arr2[3*pixel+cind])*
                      (rgb_image_arr1[3*pixel+cind]-rgb_image_arr2[3*pixel+cind]);
       }
       diff_dbl= sqrt((double)diff2_int);
       difference_image_arr[pixel]= diff_dbl;
    }
 }

 (*pdifference_image_arr)= difference_image_arr;

}
