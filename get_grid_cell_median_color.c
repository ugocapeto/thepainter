#include "header.h"

/*
Define the comparison function to sort the colors
*/

static int get_grid_cell_median_color_compare(
 const void *p1,
 const void *p2
)

{

 int var1;
 int var2;

 var1= *(int *)p1;
 var2= *(int *)p2;

 /*
 Sort w/r to increasing value
 */

 if ( var1 < var2 )
  return -1;
 if ( var1 > var2 )
  return +1;

 /*
 Sort w/r to decreasing value
 */

 /*
 if ( var1 > var2 )
  return -1;
 if ( var1 < var2 )
  return +1;
 */

 return 0;

}


void get_grid_cell_median_color(
 int *rgb_image_arr,
 int width,
 int height,
 int inp_i,
 int inp_j,
 int grid,
 int rgb[3]
)

/*
inp_i,inp_j is the top left corner of the grid cell
*/

{

 int *var_arr;
 int cind;
 int grid_i;
 int grid_j;
 int i;
 int j;
 int pixel;
 int var;
 int var_arr_ind;
 int var_arr_ind2;

 /*
 Process each color channel independently
 */

 for ( cind= 0 ; cind< 3 ; cind++ ) {

    var_arr= (int *)calloc(grid*grid,sizeof(int));

    for ( grid_i= 0 ; grid_i< grid ; grid_i++ ) {
       i= inp_i+grid_i;
       if ( !(i < height) )
        continue;
       for ( grid_j= 0 ; grid_j< grid ; grid_j++ ) {
          j= inp_j+grid_j;
          if ( !(j < width) )
           continue;
          pixel= i*width+j;
          var= rgb_image_arr[3*pixel+cind];
          var_arr_ind= grid_i*grid+grid_j;
          var_arr[var_arr_ind]= var;
       } 
    }

    /*
    Sort var_arr w/r to increasing value
    */

    /*
    The old fashioned way
    */

    /*
    for ( var_arr_ind= 0 ;
          var_arr_ind< grid*grid ;
          var_arr_ind++ ) {
       for ( var_arr_ind2= var_arr_ind+1 ;
             var_arr_ind2< grid*grid ;
             var_arr_ind2++ ) {
          if ( var_arr[var_arr_ind2] < var_arr[var_arr_ind] ) {
             var= var_arr[var_arr_ind];
             var_arr[var_arr_ind]= var_arr[var_arr_ind2];
             var_arr[var_arr_ind2]= var;
          }
       }
    }
    */

    /*
    Using qsort
    */

    qsort(
     var_arr,
     grid*grid,
     sizeof(int),
     get_grid_cell_median_color_compare
    );

    /*
    Check that var_arr was properly sorted
    */

    for ( var_arr_ind= 0 ;
          var_arr_ind< grid*grid-1 ;
          var_arr_ind++ ) {
       var_arr_ind2= var_arr_ind+1;
       if ( var_arr[var_arr_ind2] < var_arr[var_arr_ind] ) {
          error_handler((char *)"get_grid_cell_median_color");
       }
    }

    /*
    Get the median
    */

    rgb[cind]= var_arr[grid*grid/2];

    free(var_arr);
 }

}
