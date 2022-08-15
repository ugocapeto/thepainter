#include "header.h"

void rotate_image(
 int *image_arr1,
 int width1,
 int height1,
 double theta,
 char *method,
 int **pimage_arr2,
 int *porigin2_i,
 int *porigin2_j,
 int *pwidth2,
 int *pheight2
)

/*
Rotation of image_arr1 w/r to its center
theta = angle of rotation w/r to x-axis
*/

/*
The top left corner of image_arr2 is at
(origin2_i,origin2_j), which are coordinates w/r to center of image_arr1
The width of image_arr2 is width2
The height of image_arr2 is height2
*/

{

 int *image_arr2;
 int origin2_i;
 int origin2_j;
 int width2;
 int height2;

 if ( strcmp(method,"nearest_neighbor") == 0 ) {

    rotate_image_nearest_neighbor(
     image_arr1,
     width1,
     height1,
     theta,
     &image_arr2,
     &origin2_i,
     &origin2_j,
     &width2,
     &height2
    );
 }
 else if ( strcmp(method,"linear") == 0 ) {

    rotate_image_linear(
     image_arr1,
     width1,
     height1,
     theta,
     &image_arr2,
     &origin2_i,
     &origin2_j,
     &width2,
     &height2
    );
 }
 else if ( strcmp(method,"cubic") == 0 ) {

    rotate_image_cubic(
     image_arr1,
     width1,
     height1,
     theta,
     &image_arr2,
     &origin2_i,
     &origin2_j,
     &width2,
     &height2
    );
 }
 else {
    error_handler((char *)"rotate_image");
 }

 (*pimage_arr2)= image_arr2;
 (*porigin2_i)= origin2_i;
 (*porigin2_j)= origin2_j;
 (*pwidth2)= width2;
 (*pheight2)= height2;

}
