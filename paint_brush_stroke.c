#include "header.h"

void paint_brush_stroke(
 int *reference_rgb_image_arr,
 int width,
 int height,
 int brush_radius,
 brush_stroke_struct brush_stroke_data,
 texture_struct texture_data,
 double opacity_strength,
 double bumpity_strength,
 int *canvas_rgb_image_arr,
 int *canvas_bumpity_image_arr
)

{

 int local_origin_x;
 int local_origin_y;
 double xc;
 double yc;
 double theta;
 double rectw;
 double rectl;
 int cind;
 int brush_stroke_color[3];
 int map_width;
 int map_height;
 int *opacity_map;
 int *bumpity_map;
 int i;
 int j;
 int pixel;
 int map_width2;
 int map_height2;
 int *opacity_map2;
 int map_origin2_i;
 int map_origin2_j;
 int *opacity_map3;
 int map_origin3_i;
 int map_origin3_j;
 int map_width3;
 int map_height3;
 int i3;
 int j3;
 int pixel3;
 int brush_stroke_opacity;
 int canvas_color[3];
 double alpha_dbl;
 double temp_dbl;
 int temp_int;
 int *bumpity_map2;
 int *bumpity_map3;
 int canvas_bumpity;
 int debug_flag= 0;
 int err_flag;
 int brush_stroke_bumpity;
 char scale_method[256];
 char scale_gaussian[256];
 char rotate_method[256];
 double map_width2height_ratio;

 local_origin_x= brush_stroke_data.origin_x;
 local_origin_y= brush_stroke_data.origin_y;
 xc= brush_stroke_data.xc;
 yc= brush_stroke_data.yc;
 theta= brush_stroke_data.theta;
 rectw= brush_stroke_data.rectw;
 rectl= brush_stroke_data.rectl;
 for ( cind= 0 ; cind< 3 ; cind++ )
  brush_stroke_color[cind]= brush_stroke_data.color[cind];

 opacity_map= texture_data.opacity_image_arr;
 bumpity_map= texture_data.bumpity_image_arr;
 map_width= texture_data.width;
 map_height= texture_data.height;

 map_width2height_ratio= (double)map_width/(double)map_height;

 if ( debug_flag == 1 ) {

    /*
    Print the opacity map
    */

    err_flag= write_image(
     (char *)"opacity_map.png",
     opacity_map,
     map_width,
     map_height
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_brush_stroke");
    }
 }

 if ( debug_flag == 1 ) {

    /*
    Print the bumpity map
    */

    err_flag= write_image(
     (char *)"bumpity_map.png",
     bumpity_map,
     map_width,
     map_height
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_brush_stroke");
    }
 }

 if ( !(rectl >= 0.0) ) {
    error_handler((char *)"paint_brush_stroke"); 
 }
 if ( !(rectw >= 0.0) ) {
    error_handler((char *)"paint_brush_stroke"); 
 }

 /*
 Scale the opacity map and the bumpity map
 */

 /*
 map_width2= (int)round(rectl);
 if ( map_width2 == 0 )
  map_width2= 1;
 */
 map_height2= (int)round(rectw);
 if ( map_height2 == 0 )
  map_height2= 1;

 /*
 map_height2= 2*brush_radius+1;
 map_width2= (int)round( map_width2height_ratio*(double)map_height2 );
 */

 map_width2= (int)round( map_width2height_ratio*(double)map_height2 );

 opacity_map2= (int *)calloc(map_width2*map_height2,sizeof(int));

 strcpy(scale_method,"cubic");
 strcpy(scale_gaussian,"no");
 scale_image(
  opacity_map,
  map_width,
  map_height,
  opacity_map2,
  map_width2,
  map_height2,
  scale_method,
  scale_gaussian
 );

 if ( debug_flag == 1 ) {

    /* 
    Print the scaled opacity map
    */

    err_flag= write_image(
     (char *)"opacity_map2.png",
     opacity_map2,
     map_width2,
     map_height2
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_brush_stroke");
    }
 }

 bumpity_map2= (int *)calloc(map_width2*map_height2,sizeof(int));

 strcpy(scale_method,"cubic");
 strcpy(scale_gaussian,"no");
 scale_image(
  bumpity_map,
  map_width,
  map_height,
  bumpity_map2,
  map_width2,
  map_height2,
  scale_method,
  scale_gaussian
 );

 if ( debug_flag == 1 ) {

    /*
    Print the scaled bumpity map
    */

    err_flag= write_image(
     (char *)"bumpity_map2.png",
     bumpity_map2,
     map_width2,
     map_height2
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_brush_stroke");
    }
 }

 map_origin2_i= (int)round(yc);
 map_origin2_j= (int)round(xc);

 /*
 Rotate the opacity map and the bumpity map
 */

 strcpy(rotate_method,"cubic");
 rotate_image(
  opacity_map2,
  map_width2,
  map_height2,
  theta,
  rotate_method,
  &opacity_map3,
  &map_origin3_i,
  &map_origin3_j,
  &map_width3,
  &map_height3
 );

 if ( debug_flag == 1 ) {

    /*
    Print the scaled and rotated opacity map
    */

    err_flag= write_image(
     (char *)"opacity_map3.png",
     opacity_map3,
     map_width3,
     map_height3
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_brush_stroke");
    }
 }

 strcpy(rotate_method,"cubic");
 rotate_image(
  bumpity_map2,
  map_width2,
  map_height2,
  theta,
  rotate_method,
  &bumpity_map3,
  &map_origin3_i,
  &map_origin3_j,
  &map_width3,
  &map_height3
 );

 if ( debug_flag == 1 ) {

    /*
    Print the scaled and rotated bumpity map
    */

    err_flag= write_image(
     (char *)"bumpity_map3.png",
     bumpity_map3,
     map_width3,
     map_height3
    );
    if ( err_flag == 1 ) {
       error_handler((char *)"paint_brush_stroke");
    }
 }

 /*
 Paint the brush stroke on the canvas
 */

 for ( i3= 0 ; i3< map_height3 ; i3++ ) {
    for ( j3= 0 ; j3< map_width3 ; j3++ ) {
       pixel3= i3*map_width3+j3; 
       brush_stroke_opacity= opacity_map3[pixel3];
       brush_stroke_bumpity= bumpity_map3[pixel3];

       /*
       Adjust brush_stroke_opacity using bumpity_strength
       Recall that the opacity is supposed to be between 0 and 255
       */

       brush_stroke_opacity= (int)(opacity_strength*(double)brush_stroke_opacity);
       if ( !(brush_stroke_opacity >= 0) )
        brush_stroke_opacity= 0;
       if ( !(brush_stroke_opacity <= 255) )
        brush_stroke_opacity= 255;

       /*
       Adjust brush_stroke_bumpity using bumpity_strength
       Recall that the bumpity is supposed to be between 0 and 255
       */

       brush_stroke_bumpity= (int)(bumpity_strength*(double)(brush_stroke_bumpity));
       if ( !(brush_stroke_bumpity >= 0) )
        brush_stroke_bumpity= 0;
       if ( !(brush_stroke_bumpity <= 255) )
        brush_stroke_bumpity= 255;

       /*
       Need to get the corresponding pixel on the canvas
       */

       i= i3+map_origin3_i+map_origin2_i+local_origin_y;
       j= j3+map_origin3_j+map_origin2_j+local_origin_x;
       pixel= i*width+j;

       /* 
       Make sure the pixel falls onto the canvas
       */

       if ( !(i >= 0) )
        continue;
       if ( !(i < height) )
        continue;
       if ( !(j >= 0) )
        continue;
       if ( !(j < width) )
        continue;

       /* 
       Get canvas color
       */

       for ( cind= 0 ; cind< 3 ; cind++ )
        canvas_color[cind]= canvas_rgb_image_arr[3*pixel+cind];

       /*
       Alpha blend the brush stroke color and the canvas color
       */

       alpha_dbl= (double)brush_stroke_opacity/255.0;
       for ( cind= 0 ; cind< 3 ; cind++ ) {
          temp_dbl= (1.0-alpha_dbl)*(double)canvas_color[cind]+
                         alpha_dbl *(double)brush_stroke_color[cind];
          temp_int= (int)round(temp_dbl);
          if ( temp_int < 0 )
           temp_int= 0;
          if ( temp_int > 255 )
           temp_int= 255;
          canvas_rgb_image_arr[3*pixel+cind]= temp_int;
       }

       /*
       Get canvas bumpity
       */

       canvas_bumpity= canvas_bumpity_image_arr[pixel];

       /*
       Alpha blend the brush stroke bumpity and the canvas bumpity
       */

       /*
       alpha_dbl= (double)brush_stroke_opacity/255.0;
       */
       alpha_dbl= (double)brush_stroke_bumpity/255.0;
       temp_dbl= (1.0-alpha_dbl)*(double)canvas_bumpity+
                      alpha_dbl *(double)brush_stroke_bumpity;
       temp_int= (int)round(temp_dbl);
       if ( temp_int < 0 )
        temp_int= 0;
       if ( temp_int > 255 )
        temp_int= 255;
       canvas_bumpity_image_arr[pixel]= temp_int;
    }
 }

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
       error_handler((char *)"paint_brush_stroke");
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
       error_handler((char *)"paint_brush_stroke");
    }
 }

 /*
 Free opacity_map2
 */

 free(opacity_map2);

 /*
 Free bumpity_map2
 */

 free(bumpity_map2);

 /*
 Free opacity_map3
 */

 free(opacity_map3);

 /*
 Free bumpity_map3
 */

 free(bumpity_map3);

}
