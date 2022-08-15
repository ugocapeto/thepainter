#include "header.h"

void scale_image(
 int *image_arr1,
 int width1,
 int height1,
 int *image_arr2,
 int width2,
 int height2,
 char *method,
 char *gaussian
)

{

 int *imageb_arr1;
 double factor_x;
 double factor_y;
 double zoom_sigma_zero= 0.6;
 double sigma_x;
 double sigma_y;
 int precision= 5;
 int debug_flag= 0;
 int err_flag;
 int i1;
 int j1;
 int pixel1;

 if ( debug_flag == 1 ) {

    /*
    Print image_arr1
    */

    err_flag= write_image(
     (char *)"image_arr1.png",
     image_arr1,
     width1,
     height1
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"scale_image");
    }
 }

 factor_x= (double)width2/(double)width1;
 factor_y= (double)height2/(double)height1;

 if ( factor_x < 1.0 ) {

    /*
    We are downsampling along the x direction
    This requires a Gaussian blur in the x direction
    */
    
    sigma_x= zoom_sigma_zero*sqrt(1./(factor_x*factor_x)-1.);
 }
 else {

    /*
    We are upampling along the x direction
    This doesn not require a Gaussian blur in the x direction
    We are gonna apply a Gaussian blur in the x direction
    using a very small sigma in the x direction
    */

    sigma_x= 0.00001;
 }

 if ( factor_y < 1.0 ) {

    /*
    We are downsampling along the y direction
    This requires a Gaussian blur in the y direction
    */
    
    sigma_y= zoom_sigma_zero*sqrt(1./(factor_y*factor_y)-1.);
 }
 else {

    /*
    We are upampling along the y direction
    This doesn not require a Gaussian blur in the y direction
    We are gonna apply a Gaussian blur in the y direction 
    using a very small sigma in the y direction
    */
    
    sigma_y= 0.00001;
 }

 if ( strcmp(gaussian,"yes") == 0 ) {

    /*
    Apply a Gaussian blur to image_arr1
    */

    imageb_arr1= (int *)calloc(width1*height1,sizeof(int));

    gaussian_blur_image_2(
     image_arr1,
     width1,
     height1,
     sigma_x,
     sigma_y,
     precision,
     imageb_arr1
    );
 }
 else if ( strcmp(gaussian,"no") == 0 ) {

    /*
    Do not apply a Gaussian blur to image_arr1
    */

    imageb_arr1= (int *)calloc(width1*height1,sizeof(int));

    for ( i1= 0 ; i1< height1 ; i1++ ) {
       for ( j1= 0 ; j1< width1 ; j1++ ) {
          pixel1= i1*width1+j1;
          imageb_arr1[pixel1]= image_arr1[pixel1];
       }
    }
 }
 else {
    error_handler((char *)"scale_image");
 }

 if ( debug_flag == 1 ) {

    /*
    Print imageb_arr1
    */

    err_flag= write_image(
     (char *)"imageb_arr1.png",
     imageb_arr1,
     width1,
     height1
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"scale_image");
    }
 }

 /*
 Scale down imageb_arr1
 */

 if ( strcmp(method,"nearest_neighbor") == 0 ) {

    scale_image_nearest_neighbor(
     imageb_arr1,
     width1,
     height1,
     image_arr2,
     width2,
     height2
    );
 }
 else if ( strcmp(method,"linear") == 0 ) {

    scale_image_linear(
     imageb_arr1,
     width1,
     height1,
     image_arr2,
     width2,
     height2
    );
 }
 else if ( strcmp(method,"cubic") == 0 ) {

    scale_image_cubic(
     imageb_arr1,
     width1,
     height1,
     image_arr2,
     width2,
     height2
    );
 }
 else {
    error_handler((char *)"scale_image");
 }

 if ( debug_flag == 1 ) {

    /*
    Print image_arr2
    */

    err_flag= write_image(
     (char *)"image_arr2.png",
     image_arr2,
     width2,
     height2
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"scale_image");
    }
 }

 /*
 Free imageb_arr1
 */

 free(imageb_arr1);

}
