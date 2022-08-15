#include "header.h"

void paint_canvas_layer(
 int *reference_rgb_image_arr,
 int width,
 int height,
 int brush_radius,
 double opacity_strength,
 double bumpity_strength,
 texture_struct *texture_arr,
 int texture_nbr,
 double error_threshold,
 double grid_size_factor,
 int texture_ind,
 int *canvas_rgb_image_arr,
 int *canvas_bumpity_image_arr
)

{

 brush_stroke_struct brush_stroke_data;
 int brush_stroke_nbr;
 double grid_dbl;
 int grid;
 int i;
 int j;
 int local_pixel_nbr;
 int i2;
 int j2;
 int local_width;
 int local_height;
 int *local_rgb_image_arr;
 int local_pixel;
 int radius_i;
 int radius_j;
 int i3;
 int j3;
 int pixel3;
 int cind;
 int brush_stroke_color[3];
 int debug_flag= 0;
 int err_flag;
 int local_origin_x;
 int local_origin_y;
 texture_struct texture_data;
 double diff_dbl;
 int reference_rgb[3];
 int canvas_rgb[3];
 int diff2;
 double xc;
 double yc;
 double theta;
 double rectw;
 double rectl;
 int *local_rgb_image_arr2;

 brush_stroke_nbr= 0;

 /*
 Get the grid cell size (grid)
 */

 grid= 2*brush_radius+1;
 grid_dbl= grid_size_factor*(double)grid;
 /*
 grid= (int)round(grid_dbl);
 */
 grid= (int)grid_dbl;

 /*
 For each grid cell,
 determine where (xc,yc) and how (theta,rectw,rectl)
 the brush stroke should be applied
 */

 for ( i= 0 ; i< height ; i+= grid ) {
    for ( j= 0 ; j< width ; j+= grid ) {

       /*
       Get the median color in the grid cell
       looking at the reference image
       */

       get_grid_cell_median_color(
        reference_rgb_image_arr,
        width,
        height,
        i,
        j,
        grid,
        reference_rgb
       );

       /*
       Get the median color in the grid cell
       looking at the canvas image
       */

       get_grid_cell_median_color(
        canvas_rgb_image_arr,
        width,
        height,
        i,
        j,
        grid,
        canvas_rgb
       );

       diff2= 0;
       for ( cind= 0 ; cind< 3 ; cind++ ) {
          diff2+= (canvas_rgb[cind]-reference_rgb[cind])*
                  (canvas_rgb[cind]-reference_rgb[cind]);
       }
       diff_dbl= sqrt((double)diff2);

       if ( diff_dbl < error_threshold ) {

          /*
          Do nothing!
          */

          continue;
       }

       /*
       If here,
       a brush stroke needs to be applied for that grid cell
       */

       /*
       Let's consider the grid cell center
       as the center of the local reference image
       */

       i2= i+grid/2;
       j2= j+grid/2;

       /*
       Define the local reference image centered at pixel (i2,j2)
       */

       local_width= 2*brush_radius+1;
       local_height= 2*brush_radius+1;

       local_rgb_image_arr= (int *)calloc(local_width*local_height,3*sizeof(int));

       local_pixel= 0;
       local_pixel_nbr= 0;
       for ( radius_i= -brush_radius ; radius_i<= +brush_radius ; radius_i++ ) {
          i3= i2+radius_i;
          for ( radius_j= -brush_radius ; radius_j<= +brush_radius ; radius_j++ ) {
             j3= j2+radius_j;
             pixel3= i3*width+j3;
             if ( !(i3 >= 0) ) {
                local_pixel++;
                continue;
             }
             if ( !(i3 < height) ) {
                local_pixel++;
                continue;
             }
             if ( !(j3 >= 0) ) {
                local_pixel++;
                continue;
             }
             if ( !(j3 < width) ) {
                local_pixel++;
                continue;
             }
             for ( cind= 0 ; cind< 3 ; cind++ )
              local_rgb_image_arr[3*local_pixel+cind]= reference_rgb_image_arr[3*pixel3+cind];
             local_pixel++;
             local_pixel_nbr++;
          }
       }
       if ( !(local_pixel == local_width*local_height) ) {
          error_handler((char *)"paint_canvas_layer");
       }

       /*
       Do not consider a brush stroke for that grid cell
       if the local reference image is not fully within the reference image
       */

       if ( !(local_pixel_nbr == local_width*local_height) ) {

          /*
          Free local_rgb_image_arr
          */

          free(local_rgb_image_arr);

          continue;
       }

       if ( debug_flag == 1 ) {

          /*
          Print the local image
          */

          err_flag= write_rgb_image(
           (char *)"local_rgb_image.png",
           local_rgb_image_arr,
           local_width,
           local_height
          );
          if ( err_flag == 1 ) {
             error_handler((char *)"paint_canvas_layer");
          }
       }

       if ( debug_flag == 1 ) {

          /*
          Print the local image replacing actual color with dominant color
          */

          local_rgb_image_arr2= (int *)calloc(local_width*local_height,3*sizeof(int));
          for ( i3= 0 ; i3< local_height ; i3++ ) {
             for ( j3= 0 ; j3< local_width ; j3++ ) {
                pixel3= i3*local_width+j3;
                for ( cind= 0 ; cind< 3 ; cind++ )
                 local_rgb_image_arr2[3*pixel3+cind]= reference_rgb[cind];
             }
          }

          err_flag= write_rgb_image(
           (char *)"local_rgb_image2.png",
           local_rgb_image_arr2,
           local_width,
           local_height
          );
          if ( err_flag == 1 ) {
             error_handler((char *)"paint_canvas_layer");
          }

          free(local_rgb_image_arr2);
       }

       /*
       Get the brush stroke color
       */

       for ( cind= 0 ; cind< 3 ; cind++ )
        brush_stroke_color[cind]= reference_rgb[cind];

       /*
       Define the origin of the local reference image, that is,
       its top-left corner
       */

       local_origin_x= j2-brush_radius;
       local_origin_y= i2-brush_radius;

       /*
       Make the brush stroke
       */

       make_brush_stroke(
        local_rgb_image_arr,
        local_width,
        local_height,
        local_origin_x,
        local_origin_y,
        brush_radius,
        brush_stroke_color,
        &xc,
        &yc,
        &theta,
        &rectw,
        &rectl,
        &err_flag
       );

       /*
       Free local_rgb_image_arr
       */

       free(local_rgb_image_arr);

       if ( err_flag == 1 ) {

          /*
          We were not able to compute the equivalent rectangle
          */

          continue;
       }

       brush_stroke_data.dummy_int= 0;
       brush_stroke_data.origin_x= local_origin_x;
       brush_stroke_data.origin_y= local_origin_y;
       brush_stroke_data.xc= xc;
       brush_stroke_data.yc= yc;
       brush_stroke_data.theta= theta;
       brush_stroke_data.rectw= rectw;
       brush_stroke_data.rectl= rectl;
       for ( cind= 0 ; cind< 3 ; cind++ )
        brush_stroke_data.color[cind]= brush_stroke_color[cind];

       /*
       Get brush texture corresponding to texture_ind
       */

       texture_data= texture_arr[texture_ind];

       /*
       Paint the brush stroke on canvas
       */

       paint_brush_stroke(
        reference_rgb_image_arr,
        width,
        height,
        brush_radius,
        brush_stroke_data,
        texture_data,
        opacity_strength,
        bumpity_strength,
        canvas_rgb_image_arr,
        canvas_bumpity_image_arr
       );

       brush_stroke_nbr++; 
    }
 }

 fprintf(stdout,"Number of brush strokes created = %d\n",
  brush_stroke_nbr);

}
