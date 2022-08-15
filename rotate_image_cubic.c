#include "header.h"

void rotate_image_cubic(
 int *image_arr1,
 int width1,
 int height1,
 double theta,
 int **pimage_arr2,
 int *porigin2_i,
 int *porigin2_j,
 int *pwidth2,
 int *pheight2
)

/*
Rotation of image_arr1 w/r to its center
theta = angle of rotation w/r to x-axis
*/

/*
The top left corner of image_arr2 is at
(origin2_i,origin2_j), which are coordinates w/r to center of image_arr1
The width of image_arr2 is width2
The height of image_arr2 is height2
*/

{

 int i;
 int j;
 double P[2*2];
 int min_i;
 int min_j;
 int max_i;
 int max_j;
 int point_ind;
 double x_prime_dbl;
 double y_prime_dbl;
 double X_prime[2];
 double X[2];
 double x_dbl;
 double y_dbl;
 int x;
 int y;
 int origin2_i;
 int origin2_j;
 int width2;
 int height2;
 double P1[2*2];
 int i2;
 int j2;
 int pixel2;
 int *image_arr2;
 double x1;
 double y1;
 double intensity_dbl;
 int intensity_int;

 /*
 Compute the rotation matrix
 */

 i= 0;
 j= 0;
 P[2*i+j]= cos(theta);
 i= 0;
 j= 1;
 P[2*i+j]=-sin(theta);
 i= 1;
 j= 0;
 P[2*i+j]= sin(theta);
 i= 1;
 j= 1;
 P[2*i+j]= cos(theta);

 /*
 Get bounding box for image_arr2
 */

 min_i= +INT_MAX;
 min_j= +INT_MAX;
 max_i= -INT_MAX;
 max_j= -INT_MAX;

 for ( point_ind= 0 ; point_ind< 4 ; point_ind++ ) {

    if ( point_ind == 0 ) {
       x_prime_dbl=-(double)width1/2.0;
       y_prime_dbl=-(double)height1/2.0;
    }
    if ( point_ind == 1 ) {
       x_prime_dbl=+(double)width1/2.0;
       y_prime_dbl=-(double)height1/2.0;
    }
    if ( point_ind == 2 ) {
       x_prime_dbl=+(double)width1/2.0;
       y_prime_dbl=+(double)height1/2.0;
    }
    if ( point_ind == 3 ) {
       x_prime_dbl=-(double)width1/2.0;
       y_prime_dbl=+(double)height1/2.0;
    }

    X_prime[0]= x_prime_dbl;
    X_prime[1]= y_prime_dbl;

    math_matrix_vector_product(
     P,
     2,
     2,
     X_prime,
     2,
     X
    );

    x_dbl= X[0];
    y_dbl= X[1];

    x= (int)round(x_dbl);
    y= (int)round(y_dbl);

    i= y;
    j= x;

    if ( i < min_i )
     min_i= i;
    if ( j < min_j )
     min_j= j;
    if ( i > max_i )
     max_i= i;
    if ( j > max_j )
     max_j= j;
 }

 /*
 Get the top-left corner of the image_arr2
 w/r to center of image_arr1
 */

 origin2_i= min_i;
 origin2_j= min_j;

 /*
 Get the width anf height of image_arr2
 */

 width2= max_j-min_j+1;
 height2= max_i-min_i+1;

 /*
 Allocate memory for image_arr2
 */

 image_arr2= (int *)calloc(width2*height2,sizeof(int));

 /*
 All that's left now is to fill image_arr2
 */

 /*
 Compute the inverse of the rotation matrix
 */

 math_matrix_transpose(
  P,
  2,
  2,
  P1
 );

 /*
 For each pixel in image_arr2,
 we get corresponding pixel in image_arr1
 If there's no such pixel in image_arr1,
 we do nothing, that is, pixel stays black (intensity = 0)
 */

 for ( i2= 0 ; i2< height2 ; i2++ ) {
    for ( j2= 0 ; j2< width2 ; j2++ ) {

       /*
       We need to get the corresponding pixel (i1,j1) in image1
       */

       x_dbl= (double)j2+(double)origin2_j;
       y_dbl= (double)i2+(double)origin2_i;

       X[0]= x_dbl;
       X[1]= y_dbl;

       math_matrix_vector_product(
        P1,
        2,
        2,
        X,
        2,
        X_prime
       );

       x_prime_dbl= X_prime[0];
       y_prime_dbl= X_prime[1];

       /*
       (x_prime,y_prime) are pixel coordinates w/r to center of image_arr1
       We need to get pixel coordinates w/r to origin of image_arr1
       */

       x_prime_dbl+= (double)width1/2.0;
       y_prime_dbl+= (double)height1/2.0;

       x1= x_prime_dbl;
       y1= y_prime_dbl;

       /*
       if ( !(x1 >= 0.0) )
        x1= 0.0;
       if ( !(x1 <= (double)(width1-1)) )
        x1= (double)(width1-1);
       if ( !(y1 >= 0.0) )
        y1= 0.0;
       if ( !(y1 <= (double)(height1-1)) )
        y1= (double)(height1-1);
       */

       if ( !(x1 >= 0.0) )
        continue;
       if ( !(x1 <= (double)(width1-1)) )
        continue; 
       if ( !(y1 >= 0.0) )
        continue;
       if ( !(y1 <= (double)(height1-1)) )
        continue; 

       intensity_dbl= bicubic_interpolation_on_image_int(
        image_arr1,
        x1,
        y1,
        width1,
        height1
       );

       intensity_int= (int)round(intensity_dbl);

       if ( !(intensity_int >= 0) )
        intensity_int= 0;
       if ( !(intensity_int <= 255) )
        intensity_int= 255;

       pixel2= i2*width2+j2;
       image_arr2[pixel2]= intensity_int;
    }
 }

 (*pimage_arr2)= image_arr2;
 (*porigin2_i)= origin2_i;
 (*porigin2_j)= origin2_j;
 (*pwidth2)= width2;
 (*pheight2)= height2;

}
