#include "header.h"

void initialize_canvas_rgb_image(
 int width,
 int height,
 int **pcanvas_rgb_image_arr
)

{

 int *canvas_rgb_image_arr;
 int i;
 int j;
 int pixel;
 int cind;
 int rgb[3];

 /*
 Allocate memory for canvas_rgb_image_arr
 */

 canvas_rgb_image_arr= (int *)calloc(width*height,3*sizeof(int));

 /*
 Fill each color channel of the canvas with a median value
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       /* pure white */
       rgb[0]= 255;
       rgb[1]= 255;
       rgb[2]= 255;
       for ( cind= 0 ; cind< 3 ; cind++ )
        canvas_rgb_image_arr[3*pixel+cind]= rgb[cind];
    }
 }

 (*pcanvas_rgb_image_arr)= canvas_rgb_image_arr;

}
