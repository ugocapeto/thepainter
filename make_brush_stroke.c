#include "header.h"

void make_brush_stroke(
 int *rgb_image_arr,
 int width,
 int height,
 int origin_x,
 int origin_y,
 int brush_radius,
 int brush_stroke_color[3],
 double *pxc,
 double *pyc,
 double *ptheta,
 double *prectw,
 double *prectl,
 int *perr_flag
)

/*
rgb_image_arr is the local reference image
(a cropped version of the reference image)
(width,height) are the dimensions of the local reference image
(origin_x,origin_y) is the origin (top-left corner) of the local reference image
*/

{

 double *difference_image_arr;
 double xc;
 double yc;
 double theta;
 double rectw;
 double rectl;
 int debug_flag= 0;
 int *normalized_difference_image_arr;
 int pixel;
 int i;
 int j;
 double temp_dbl;
 int temp_int;
 int err_flag;

 err_flag= 0;
 xc= 0.0;
 yc= 0.0;
 theta= 0.0;
 rectw= 0.0;
 rectl= 0.0;

 /*
 Compute the difference image
 */

 /*
 compute_difference_image_shiraishi(
  rgb_image_arr,
  width,
  height,
  brush_stroke_color,
  &difference_image_arr
 );
 */

 compute_difference_image_shiraishi_2(
  rgb_image_arr,
  width,
  height,
  brush_stroke_color,
  &difference_image_arr
 );

 if ( debug_flag == 1 ) {

    /*
    Print the difference image
    */

    normalized_difference_image_arr= (int *)calloc(width*height,sizeof(int));

    for ( i= 0 ; i< height ; i++ ) {
       for ( j= 0 ; j< width ; j++ ) {
          pixel= i*width+j;
          temp_dbl= difference_image_arr[pixel]*255.0;
          temp_int= (int)round(temp_dbl);
          normalized_difference_image_arr[pixel]= temp_int;
       }
    }

    err_flag= write_image(
     (char *)"normalized_difference_image.png",
     normalized_difference_image_arr,
     width,
     height
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_canvas_layer");
    }

    free(normalized_difference_image_arr);
 }

 /*
 Compute the equivalent rectangle
 */

 compute_equivalent_rectangle(
  difference_image_arr,
  width,
  height,
  &xc,
  &yc,
  &theta,
  &rectw,
  &rectl,
  &err_flag
 );

 if ( err_flag == 1 ) {

    /*
    We could not get the equivalent rectangle
    Let's forget about making the brush stroke
    */

    goto END;
 }

 END:

 /*
 Free difference_image_arr
 */
 
 free(difference_image_arr);

 (*pxc)= xc;
 (*pyc)= yc;
 (*ptheta)= theta;
 (*prectw)= rectw;
 (*prectl)= rectl;
 (*perr_flag)= err_flag;

}
