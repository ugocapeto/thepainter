#include "header.h"

void scale_rgb_image(
 int *rgb_image_arr1,
 int width1,
 int height1,
 int *rgb_image_arr2,
 int width2,
 int height2,
 char *method,
 char *gaussian
)

{

 int cind;
 int *image_arr1;
 int i;
 int j;
 int pixel;
 int *image_arr2;

 for ( cind= 0 ; cind< 3 ; cind++ ) {

    image_arr1= (int *)calloc(width1*height1,sizeof(int));

    for ( i= 0 ; i< height1 ; i++ ) {
       for ( j= 0 ; j< width1 ; j++ ) {
          pixel= i*width1+j;
          image_arr1[pixel]= rgb_image_arr1[3*pixel+cind];
       }
    }

    image_arr2= (int *)calloc(width2*height2,sizeof(int));

    scale_image(
     image_arr1,
     width1,
     height1,
     image_arr2,
     width2,
     height2,
     method,
     gaussian
    );

    for ( i= 0 ; i< height2 ; i++ ) {
       for ( j= 0 ; j< width2 ; j++ ) {
          pixel= i*width2+j;
          rgb_image_arr2[3*pixel+cind]= image_arr2[pixel];
       }
    }

    free(image_arr1);

    free(image_arr2);
 }

}
