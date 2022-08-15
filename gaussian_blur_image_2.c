#include "header.h"

void gaussian_blur_image_2(
 int *I,
 int xdim,
 int ydim,
 double sigma_x,
 double sigma_y,
 int precision,
 int *I_out
)

{

 int size_x;
 int size_y;
 double *G_x;
 double *G_y;
 int i;
 double x;
 double y;
 double pi=acos(-1);
 double *row;
 int j;
 double norm;
 int k;
 double val;
 double *col;
 double *I_dbl;
 double val_dbl;
 int val_int;

 /*
 Allocate memory for output image in double form
 */

 I_dbl= (double *)calloc(xdim*ydim,sizeof(double));

 /*
 Copy input image into output image
 */

 for ( i= 0 ; i< ydim ; i++ ) {
    for ( j= 0 ; j< xdim ; j++ ) {
       I_dbl[i*xdim+j]= (double)I[i*xdim+j];
    }
 }

 /*
 We are gonna apply a 1d kernel
 (defined by sigma and precision)
 in both directions
 */

 size_x= (int)((double)precision*sigma_x)+1;

 G_x= (double *)calloc(size_x,sizeof(double));
 for ( j= 0 ; j< size_x ; j++ ) {
    x= (double)j;
    G_x[j]= 1/(sqrt(2*pi)*sigma_x)*exp(-x*x/(2*sigma_x*sigma_x));
 }

 size_y= (int)((double)precision*sigma_y)+1;

 G_y= (double *)calloc(size_y,sizeof(double));
 for ( i= 0 ; i< size_y ; i++ ) {
    y= (double)i;
    G_y[i]= 1/(sqrt(2*pi)*sigma_y)*exp(-y*y/(2*sigma_y*sigma_y));
 }

 /*
 We are gonna copy the image row by row,
 convolute each row, and
 put the results back in I
 */

 row= (double *)calloc(xdim,sizeof(double));
 for ( i= 0 ; i< ydim ; i++ ) {
    for ( j= 0 ; j< xdim ; j++ ) {
       norm= 0.0;
       k= 0;
       val= G_x[k]*I_dbl[i*xdim+j];
       norm+= G_x[k];
       for ( k= 1 ; k< size_x ; k++ ) {
          if ( !( (j+k)<xdim ) )
           continue;
          val+= G_x[k]*I_dbl[i*xdim+(j+k)];
          norm+= G_x[k];
       }
       for ( k= 1 ; k< size_x ; k++ ) {
          if ( !( (j-k)>=0 ) )
           continue;
          val+= G_x[k]*I_dbl[i*xdim+(j-k)];
          norm+= G_x[k];
       }
       row[j]= val/norm;
    }
    for ( j= 0 ; j< xdim ; j++ ) {
       I_dbl[i*xdim+j]= row[j];
    }
 }
 free(row);

 /*
 We are gonna copy the image col by col,
 convolute each col, and
 put the results back in I
 */

 col= (double *)calloc(ydim,sizeof(double));
 for ( j= 0 ; j< xdim ; j++ ) {
    for ( i= 0 ; i< ydim ; i++ ) {
       norm= 0.0;
       k= 0;
       val= G_y[k]*I_dbl[i*xdim+j];
       norm+= G_y[k];
       for ( k= 1 ; k< size_y ; k++ ) {
          if ( !( (i+k)<ydim ) )
           continue;
          val+= G_y[k]*I_dbl[(i+k)*xdim+j];
          norm+= G_y[k];
       }
       for ( k= 1 ; k< size_y ; k++ ) {
          if ( !( (i-k)>=0 ) )
           continue;
          val+= G_y[k]*I_dbl[(i-k)*xdim+j];
          norm+= G_y[k];
       }
       col[i]= val/norm;
    }
    for ( i= 0 ; i< ydim ; i++ ) {
       I_dbl[i*xdim+j]= col[i];
    }
 }
 free(col);

 for ( i= 0 ; i< ydim ; i++ ) {
    for ( j= 0 ; j< xdim ; j++ ) {
       val_dbl= I_dbl[i*xdim+j];
       val_int= (int)(val_dbl+0.5);
       if ( val_int < 0 )
        val_int= 0;
       if ( val_int > 255 )
        val_int= 255;
       I_out[i*xdim+j]= val_int;
    }
 }

 free(G_x);

 free(G_y);

 /*
 Free memory for output image in double form
 */

 free(I_dbl);

}
