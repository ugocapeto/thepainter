#include "header.h"

int main(
 int argc,
 char* argv[]
)

{

 FILE *fp;
 char filename[256];
 char filename_source_rgb_image[256];
 char filename_canvas_rgb_image[256];
 char filename_canvas_bumpity_image[256];
 int err_flag;
 int *source_rgb_image_arr;
 int *canvas_rgb_image_arr;
 int *canvas_bumpity_image_arr;
 int width;
 int height;
 int *brush_radius_arr;
 int brush_radius_nbr;
 int brush_radius;
 int brush_radius_ind;
 double error_threshold;
 double *opacity_strength_arr;
 double opacity_strength;
 double *bumpity_strength_arr;
 double bumpity_strength;
 texture_struct *texture_arr;
 int texture_nbr;
 int texture_ind;
 int *opacity_image_arr;
 int opacity_image_width;
 int opacity_image_height;
 int *bumpity_image_arr;
 int bumpity_image_width;
 int bumpity_image_height;
 texture_struct texture_data;
 char filename_initial_canvas_bumpity_image[256];
 int *initial_canvas_bumpity_image_arr;
 int initial_canvas_bumpity_image_width;
 int initial_canvas_bumpity_image_height;
 char filename_initial_canvas_rgb_image[256];
 int *initial_canvas_rgb_image_arr;
 int initial_canvas_rgb_image_width;
 int initial_canvas_rgb_image_height;
 double grid_size_factor;
 double *error_threshold_arr;
 double *grid_size_factor_arr;
 int *texture_ind_arr;

 /*
 Let's read in the input file
 */

 fp= fopen("thepainter_input.txt","r");
 if ( fp == NULL ) {
    fprintf(stdout,"thepainter_input.txt not found!\n");
    return 1;
 }

 /*
 Get filename for source rgb image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"source rgb image = %s\n",filename);

 strcpy(filename_source_rgb_image,filename);

 /*
 Get filename for initial canvas rgb image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"initial canvas rgb image = %s\n",filename);

 strcpy(filename_initial_canvas_rgb_image,filename);

 /*
 Get filename for initial canvas bumpity image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"initial canvas bumpity image = %s\n",filename);

 strcpy(filename_initial_canvas_bumpity_image,filename);

 /*
 Get the number of brush radius
 */

 fscanf(fp,"%d",&brush_radius_nbr);

 fprintf(stdout,"number of brush radius = %d\n",brush_radius_nbr);

 /*
 Get the brush radius for each brush
 */

 brush_radius_arr= (int *)calloc(brush_radius_nbr,sizeof(int));
 opacity_strength_arr= (double *)calloc(brush_radius_nbr,sizeof(double));
 bumpity_strength_arr= (double *)calloc(brush_radius_nbr,sizeof(double));
 error_threshold_arr= (double *)calloc(brush_radius_nbr,sizeof(double));
 grid_size_factor_arr= (double *)calloc(brush_radius_nbr,sizeof(double));
 texture_ind_arr= (int *)calloc(brush_radius_nbr,sizeof(int));

 for ( brush_radius_ind= 0 ;
       brush_radius_ind< brush_radius_nbr ;
       brush_radius_ind++ ) {
    fscanf(fp,"%d %lg %lg %lg %lg %d",
     &brush_radius,&opacity_strength,&bumpity_strength,&error_threshold,&grid_size_factor,&texture_ind);

    fprintf(stdout,"brush_radius_ind = %2d brush_radius = %3d opacity_strength = %.2f bumpity_strength = %.2f error_threshold = %6.2f grid_size_factor = %.2f texture_ind = %2d\n",
     brush_radius_ind,brush_radius,opacity_strength,bumpity_strength,error_threshold,grid_size_factor,texture_ind);

    brush_radius_arr[brush_radius_ind]= brush_radius;
    opacity_strength_arr[brush_radius_ind]= opacity_strength;
    bumpity_strength_arr[brush_radius_ind]= bumpity_strength;
    error_threshold_arr[brush_radius_ind]= error_threshold;
    grid_size_factor_arr[brush_radius_ind]= grid_size_factor;
    texture_ind_arr[brush_radius_ind]= texture_ind;
 }

 /*
 Get the number of brush texture files
 */

 fscanf(fp,"%d",&texture_nbr);

 fprintf(stdout,"number of brush texture files = %d\n",texture_nbr);

 /*
 Get the brush texture files
 */

 texture_arr= (texture_struct *)calloc(texture_nbr,sizeof(texture_struct));

 for ( texture_ind= 0 ;
       texture_ind< texture_nbr ; 
       texture_ind++ ) {
    fprintf(stdout,"texture_ind = %d\n",texture_ind);

    fscanf(fp,"%s",filename);

    fprintf(stdout,"opacity image file = %s\n",filename);

    err_flag= load_image(
     filename,
     &opacity_image_arr,
     &opacity_image_width,
     &opacity_image_height
    );

    if ( err_flag == 1 ) {
       fprintf(stdout,"opacity image file %s not loaded!\n",filename);
       error_handler((char *)"main");
    }

    fscanf(fp,"%s",filename);

    fprintf(stdout,"bumpity image file = %s\n",filename);

    err_flag= load_image(
     filename,
     &bumpity_image_arr,
     &bumpity_image_width,
     &bumpity_image_height
    );

    if ( err_flag == 1 ) {
       fprintf(stdout,"bumpity image file %s not loaded!\n",filename);
       error_handler((char *)"main");
    }

    if ( !(bumpity_image_width == opacity_image_width) ) {
       fprintf(stdout,"opacity image and bumpity image must have same width!\n");
       error_handler((char *)"main");
    }
    if ( !(bumpity_image_height == opacity_image_height) ) {
       fprintf(stdout,"opacity image and bumpity image must have same height!\n");
       error_handler((char *)"main");
    }

    texture_data.opacity_image_arr= opacity_image_arr;
    texture_data.bumpity_image_arr= bumpity_image_arr;
    texture_data.width= opacity_image_width;
    texture_data.height= opacity_image_height;
    texture_arr[texture_ind]= texture_data;
 }

 /*
 Get filename for canvas rgb image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"canvas rgb image = %s\n",filename);

 strcpy(filename_canvas_rgb_image,filename);

 /*
 Get filename for canvas bumpity image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"canvas bumpity image = %s\n",filename);

 strcpy(filename_canvas_bumpity_image,filename);

 /*
 Done reading the input file
 */

 fclose(fp);

 /*
 Load source rgb image
 */

 err_flag= load_rgb_image(
  filename_source_rgb_image,
  &source_rgb_image_arr,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"source rgb image file %s not loaded!\n",filename_source_rgb_image);
    return 1;
 }

 /*
 Load initial canvas rgb image
 */

 err_flag= load_rgb_image(
  filename_initial_canvas_rgb_image,
  &initial_canvas_rgb_image_arr,
  &initial_canvas_rgb_image_width,
  &initial_canvas_rgb_image_height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"initial canvas rgb image file %s not loaded!\n",filename_initial_canvas_rgb_image);
    return 1;
 }

 /*
 Load initial canvas bumpity image
 */

 err_flag= load_image(
  filename_initial_canvas_bumpity_image,
  &initial_canvas_bumpity_image_arr,
  &initial_canvas_bumpity_image_width,
  &initial_canvas_bumpity_image_height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"initial canvas bumpity image file %s not loaded!\n",filename_initial_canvas_bumpity_image);
    return 1;
 }

 /*
 Paint the canvas
 */

 paint_canvas(
  source_rgb_image_arr,
  width,
  height,
  initial_canvas_rgb_image_arr,
  initial_canvas_rgb_image_width,
  initial_canvas_rgb_image_height,
  initial_canvas_bumpity_image_arr,
  initial_canvas_bumpity_image_width,
  initial_canvas_bumpity_image_height,
  brush_radius_arr,
  brush_radius_nbr,
  opacity_strength_arr,
  bumpity_strength_arr,
  error_threshold_arr,
  grid_size_factor_arr,
  texture_ind_arr,
  texture_arr,
  texture_nbr,
  &canvas_rgb_image_arr,
  &canvas_bumpity_image_arr
 );

 /*
 Write canvas rgb image
 */

 err_flag= write_rgb_image(
  filename_canvas_rgb_image,
  canvas_rgb_image_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"canvas rgb image file %s not written!\n",filename_canvas_rgb_image);
    return 1;
 }

 /*
 Write canvas bumpity image
 */

 err_flag= write_image(
  filename_canvas_bumpity_image,
  canvas_bumpity_image_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"canvas bumpity image file %s not written!\n",filename_canvas_bumpity_image);
    return 1;
 }

 /*
 Free source_rgb_image_arr
 */

 free(source_rgb_image_arr);

 /*
 Free initial_canvas_rgb_image_arr
 */

 free(initial_canvas_rgb_image_arr);

 /*
 Free initial_canvas_bumpity_image_arr
 */

 free(initial_canvas_bumpity_image_arr);

 /*
 Free brush_radius_arr
 Free opacity_strangth_arr
 Free bumpity_strength_arr
 Free error_threshold_arr
 Free grid_size_factor_arr
 Free texture_ind_arr
 */

 if ( brush_radius_nbr > 0 ) {
    free(brush_radius_arr);
    free(opacity_strength_arr);
    free(bumpity_strength_arr);
    free(error_threshold_arr);
    free(grid_size_factor_arr);
    free(texture_ind_arr);
 }

 /*
 Free texture_arr
 */

 free_texture_arr(
  texture_arr,
  texture_nbr
 );

 /*
 Free canvas_rgb_image_arr
 */

 free(canvas_rgb_image_arr);

 /*
 Free canvas_bumpity_image_arr
 */

 free(canvas_bumpity_image_arr);

 return 0;

}
