/*
Define the structure for the brush strokes
 */

typedef struct brush_stroke_struct {
 int dummy_int;
 int origin_x;
 int origin_y;
 double xc;
 double yc;
 double theta;
 double rectw;
 double rectl;
 int color[3];
} brush_stroke_struct;

/*
Define the structure for the textures
*/

typedef struct texture_struct {
 int *opacity_image_arr;
 int *bumpity_image_arr;
 int width;
 int height;
} texture_struct;
