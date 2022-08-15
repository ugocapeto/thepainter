#include "header.h"

void scale_image_nearest_neighbor(
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
 int i1;
 int j2;
 double x1;
 int j1;
 int pixel1;
 int intensity1;
 int pixel2;
 int intensity2;

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

       i1= (int)round(y1);
       j1= (int)round(x1);

       /*
       Make sure pixel in image_arr1 is gonna be in bounds
       */

       if ( !(i1 >= 0) )
        i1= 0;
       if ( !(i1 < height1) )
        i1= height1-1;
       if ( !(j1 >= 0) )
        j1= 0;
       if ( !(j1 < width1) )
        j1= width1-1;
    
       pixel1= i1*width1+j1; 
       intensity1= image_arr1[pixel1];
       pixel2= i2*width2+j2;
       intensity2= intensity1;
       image_arr2[pixel2]= intensity2;
    }
 }

}
