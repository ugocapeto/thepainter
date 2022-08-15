#include "header.h"

void free_texture_arr(
 texture_struct *texture_arr,
 int texture_nbr
)

{

 int texture_ind;
 texture_struct texture_data;
 int *opacity_image_arr;
 int *bumpity_image_arr;

 for ( texture_ind= 0 ; texture_ind< texture_nbr ; texture_ind++ ) {
    texture_data= texture_arr[texture_ind];
    opacity_image_arr= texture_data.opacity_image_arr;
    bumpity_image_arr= texture_data.bumpity_image_arr;
    free(opacity_image_arr);
    free(bumpity_image_arr);
 }

 if ( texture_nbr > 0 )
  free(texture_arr);

}
