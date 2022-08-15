#include "header.h"

void load_texture_arr(
 char *filename,
 texture_struct **ptexture_arr,
 int *ptexture_nbr
)

{

 texture_struct *texture_arr;
 int texture_nbr;
 FILE *fp;
 int line;
 int temp_int;
 char filename2[256];
 int texture_ind;
 int *opacity_image_arr;
 int opacity_image_width;
 int opacity_image_height;
 int *bumpity_image_arr;
 int bumpity_image_width;
 int bumpity_image_height;
 int width;
 int height;
 texture_struct texture_data;
 int err_flag;

 texture_arr= 0;
 texture_nbr= 0;

 fp= fopen(filename,"r");
 if ( fp == NULL ) {
    fprintf(stdout,"%s not found!\n",filename);
    error_handler((char *)"load_texture_arr");
 }

 for ( line= 1 ; ; line+=2 ) {

    temp_int= fscanf(fp,"%s",filename2);
    if ( temp_int == EOF )
     break;

    fprintf(stdout,"opacity image file = %s\n",filename2);

    err_flag= load_image(
     filename2,
     &opacity_image_arr,
     &opacity_image_width,
     &opacity_image_height
    );

    if ( err_flag == 1 ) {
       fprintf(stdout,"opacity image file %s not loaded!\n",filename2);
       error_handler((char *)"load_texture_arr");
    }

    width= opacity_image_width; 
    height= opacity_image_height; 

    temp_int= fscanf(fp,"%s",filename2);
    if ( temp_int == EOF ) {
       fprintf(stdout,"no entry for bumpity image file!\n");
       error_handler((char *)"load_texture_arr");
    }

    fprintf(stdout,"bumpity file = %s\n",filename2);

    err_flag= load_image(
     filename2,
     &bumpity_image_arr,
     &bumpity_image_width,
     &bumpity_image_height
    );

    if ( err_flag == 1 ) {
       fprintf(stdout,"bumpity image file %s not loaded!\n",filename2);
       error_handler((char *)"load_texture_arr");
    }

    if ( !(bumpity_image_width == width) ) {
       fprintf(stdout,"opacity image and bumpity image must have same width!\n");
       error_handler((char *)"load_texture_arr");
    }
    if ( !(bumpity_image_height == height) ) {
       fprintf(stdout,"opacity image and bumpity image must have same height!\n");
       error_handler((char *)"load_texture_arr");
    }

    if ( texture_nbr == 0 ) {
       texture_arr= (texture_struct *)calloc((texture_nbr+1),sizeof(texture_struct));
    }
    else {
       texture_arr= (texture_struct *)realloc(texture_arr,(texture_nbr+1)*sizeof(texture_struct));
    }
    texture_ind= texture_nbr;
    texture_nbr++;
    texture_data.opacity_image_arr= opacity_image_arr;
    texture_data.bumpity_image_arr= bumpity_image_arr;
    texture_data.width= width;
    texture_data.height= height;
    texture_arr[texture_ind]= texture_data;
 }

 fclose(fp);

 (*ptexture_arr)= texture_arr;
 (*ptexture_nbr)= texture_nbr;

}
