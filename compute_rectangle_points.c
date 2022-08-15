#include "header.h"

void compute_rectangle_points(
 double xc,
 double yc,
 double theta,
 double rectw,
 double rectl,
 int point_arr[4*2]
)

{

 int i;
 int j;
 double P[2*2];
 int point_ind;
 double x_prime_dbl;
 double y_prime_dbl;
 double X_prime[2];
 double temp_X[2];
 double x_dbl;
 double y_dbl;
 int x;
 int y;

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
 Get the point coordinates in global image reference system
 */

 for ( point_ind= 0 ; point_ind< 4 ; point_ind++ ) {

    if ( point_ind == 0 ) {
       x_prime_dbl=-rectl/2.0;
       y_prime_dbl=-rectw/2.0;
    }
    if ( point_ind == 1 ) {
       x_prime_dbl=+rectl/2.0;
       y_prime_dbl=-rectw/2.0;
    }
    if ( point_ind == 2 ) {
       x_prime_dbl=+rectl/2.0;
       y_prime_dbl=+rectw/2.0;
    }
    if ( point_ind == 3 ) {
       x_prime_dbl=-rectl/2.0;
       y_prime_dbl=+rectw/2.0;
    }

    X_prime[0]= x_prime_dbl;
    X_prime[1]= y_prime_dbl;

    math_matrix_vector_product(
     P,
     2,
     2,
     X_prime,
     2,
     temp_X
    );

    x_dbl= temp_X[0]+xc;
    y_dbl= temp_X[1]+yc;

    x= (int)round(x_dbl);
    y= (int)round(y_dbl);

    point_arr[2*point_ind+0]= x;
    point_arr[2*point_ind+1]= y;
 }

}
