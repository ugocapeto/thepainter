#include "header.h"

void scale_image_linear(
 int *image_arr1,
 int width1,
 int height1,
 int *image_arr2,
 int width2,
 int height2
)

{

 int i2;
 double y1;
 int j2;
 double x1;
 int pixel2;
 double intensity_dbl;
 int intensity_int;

 for ( i2= 0 ; i2< height2; i2++ ) {

    /*
    Get corresponding y1 in image1_arr
    */

    y1= ( (double)i2/(double)height2 ) * (double)height1;

    for ( j2= 0 ; j2< width2; j2++ ) {

       /*
       Get corresponding x1 in image1_arr
       */

       x1= ( (double)j2/(double)width2 ) * (double)width1;

       if ( !(x1 >= 0.0) )
        x1= 0.0;
       if ( !(x1 < (double)width1) )
        x1= (double)(width1-1);
       if ( !(y1 >= 0.0) )
        y1= 0.0;
       if ( !(y1 < (double)height1) )
        y1= (double)(height1-1);

       intensity_dbl= bilinear_interpolation_on_image_int(
        image_arr1,
        x1,
        y1,
        width1,
        height1
       );

       intensity_int= (int)round(intensity_dbl);

       if ( !(intensity_int >= 0) )
        intensity_int= 0;
       if ( !(intensity_int <= 255) )
        intensity_int= 255;

       pixel2= i2*width2+j2;
       image_arr2[pixel2]= intensity_int;
    }
 }

}
