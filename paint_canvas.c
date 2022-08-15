#include "header.h"

void paint_canvas(
 int *reference_rgb_image_arr,
 int width,
 int height,
 int *initial_canvas_rgb_image_arr,
 int initial_canvas_rgb_image_width,
 int initial_canvas_rgb_image_height,
 int *initial_canvas_bumpity_image_arr,
 int initial_canvas_bumpity_image_width,
 int initial_canvas_bumpity_image_height,
 int *brush_radius_arr,
 int brush_radius_nbr,
 double *opacity_strength_arr,
 double *bumpity_strength_arr,
 double *error_threshold_arr,
 double *grid_size_factor_arr,
 int *texture_ind_arr,
 texture_struct *texture_arr,
 int texture_nbr,
 int **pcanvas_rgb_image_arr,
 int **pcanvas_bumpity_image_arr
)

{

 int *canvas_rgb_image_arr;
 int brush_radius_ind;
 int brush_radius;
 int debug_flag= 0;
 int err_flag;
 int *canvas_bumpity_image_arr;
 double error_threshold;
 double opacity_strength;
 double bumpity_strength;
 char scale_method[256];
 char scale_gaussian[256];
 double grid_size_factor;
 int texture_ind;

 /*
 Allocate memory for canvas_rgb_image_arr
 */

 canvas_rgb_image_arr= (int *)calloc(width*height,3*sizeof(int));

 /*
 Initialize the canvas rgb image with the input initial canvas rgb image
 */

 strcpy(scale_method,"cubic");
 strcpy(scale_gaussian,"no");
 scale_rgb_image(
  initial_canvas_rgb_image_arr,
  initial_canvas_rgb_image_width,
  initial_canvas_rgb_image_height,
  canvas_rgb_image_arr,
  width,
  height,
  scale_method,
  scale_gaussian
 );

 if ( debug_flag == 1 ) {

    /*
    Print the canvas rgb image
    */

    err_flag= write_rgb_image(
     (char *)"canvas_rgb_image.png",
     canvas_rgb_image_arr,
     width,
     height
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_canvas");
    }
 }

 /*
 Allocate memory for canvas_bumpity_image_arr
 */

 canvas_bumpity_image_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Initialize the canvas bumpity image with the input initial canvas bumpity image
 */

 strcpy(scale_method,"cubic");
 strcpy(scale_gaussian,"no");
 scale_image(
  initial_canvas_bumpity_image_arr,
  initial_canvas_bumpity_image_width,
  initial_canvas_bumpity_image_height,
  canvas_bumpity_image_arr,
  width,
  height,
  scale_method,
  scale_gaussian
 );

 if ( debug_flag == 1 ) {

    /*
    Print the canvas bumpity image
    */

    err_flag= write_image(
     (char *)"canvas_bumpity_image.png",
     canvas_bumpity_image_arr,
     width,
     height
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_canvas");
    }
 }

 /*
 Paint the canvas layer by layer
 */

 for ( brush_radius_ind= 0 ;
       brush_radius_ind< brush_radius_nbr ;
       brush_radius_ind++ ) {
    brush_radius= brush_radius_arr[brush_radius_ind];
    opacity_strength= opacity_strength_arr[brush_radius_ind];
    bumpity_strength= bumpity_strength_arr[brush_radius_ind];
    error_threshold= error_threshold_arr[brush_radius_ind];
    grid_size_factor= grid_size_factor_arr[brush_radius_ind];
    texture_ind= texture_ind_arr[brush_radius_ind];

    fprintf(stdout,"Painting canvas layer using brush_radius_ind = %2d brush_radius = %3d opacity_strength = %.2f bumpity_strength = %.2f error_threshold = %6.2f grid_size_factor = %.2f texture_ind = %2d...\n",
     brush_radius_ind,brush_radius,opacity_strength,bumpity_strength,error_threshold,grid_size_factor,texture_ind);

    /*
    Paint the canvas layer
    */

    paint_canvas_layer(
     reference_rgb_image_arr,
     width,
     height,
     brush_radius,
     opacity_strength,
     bumpity_strength,
     texture_arr,
     texture_nbr,
     error_threshold,
     grid_size_factor,
     texture_ind,
     canvas_rgb_image_arr,
     canvas_bumpity_image_arr
    );

    if ( debug_flag == 1 ) {

       /*
       Print the canvas image
       */

       err_flag= write_rgb_image(
        (char *)"canvas_rgb_image.png",
        canvas_rgb_image_arr,
        width,
        height
       );
       if ( err_flag == 1 ) {
          error_handler((char *)"paint_canvas");
       }
    }

    if ( debug_flag == 1 ) {

       /*
       Print the canvas bumpity image
       */

       err_flag= write_image(
        (char *)"canvas_bumpity_image.png",
        canvas_bumpity_image_arr,
        width,
        height
       );
       if ( err_flag == 1 ) {
          error_handler((char *)"paint_canvas");
       }
    }

    fprintf(stdout,"Painting canvas layer using brush_radius_ind = %2d brush_radius = %3d opacity_strength = %.2f bumpity_strength = %.2f error_threshold = %6.2f grid_size_factor = %.2f texture_ind = %2d... done.\n",
     brush_radius_ind,brush_radius,opacity_strength,bumpity_strength,error_threshold,grid_size_factor,texture_ind);

 }

 (*pcanvas_rgb_image_arr)= canvas_rgb_image_arr;
 (*pcanvas_bumpity_image_arr)= canvas_bumpity_image_arr;

}
