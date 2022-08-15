#include "header.h"

void compute_reference_image(
 int *source_rgb_image_arr,
 int width,
 int height,
 double sigma,
 int **preference_rgb_image_arr
)

{

 int precision= 5;
 int *reference_rgb_image_arr;

 /*
 Allocate memory for reference_rgb_image_arr
 */

 reference_rgb_image_arr= (int *)calloc(width*height,3*sizeof(int));

 /* 
 The reference image is obtained by blurring (Gaussian) the source image
 */

 gaussian_blur_rgb_image(
  source_rgb_image_arr,
  width, 
  height,
  sigma,
  precision,
  reference_rgb_image_arr 
 );

 (*preference_rgb_image_arr)= reference_rgb_image_arr;

}
