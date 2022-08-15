#include "header.h"

void initialize_canvas_bumpity_image(
 int width,
 int height,
 int **pcanvas_bumpity_image_arr
)

{

 int *canvas_bumpity_image_arr;
 int i;
 int j;
 int pixel;

 /*
 Allocate memory for canvas_bumpity_image_arr
 */

 canvas_bumpity_image_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Fill the canvas with a median value
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       canvas_bumpity_image_arr[pixel]= 128;
    }
 }

 (*pcanvas_bumpity_image_arr)= canvas_bumpity_image_arr;

}
