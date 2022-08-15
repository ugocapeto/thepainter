void compute_difference_image_hertzmann(
 int *rgb_image_arr1,
 int *rgb_image_arr2,
 int width,
 int height,
 double **pdifference_image_arr
);

void compute_difference_image_shiraishi_2(
 int *rgb_image_arr,
 int width,
 int height,
 int rgb_color[3],
 double **pdifference_image_arr
);

void compute_difference_image_shiraishi(
 int *rgb_image_arr,
 int width,
 int height,
 int rgb_color[3],
 double **pdifference_image_arr
);

void compute_equivalent_rectangle(
 double *image_arr,
 int width,
 int height,
 double *pxc,
 double *pyc,
 double *ptheta,
 double *prectw,
 double *prectl,
 int *perr_flag
);

void compute_image_moment(
 double *image_arr,
 int width,
 int height,
 int l,
 int m,
 double *pmoment
);

void compute_rectangle_points(
 double xc,
 double yc,
 double theta,
 double rectw,
 double rectl,
 int point_arr[4*2]
);

void compute_reference_image(
 int *source_rgb_image_arr,
 int width,
 int height,
 double sigma,
 int **preference_rgb_image_arr
);

void free_texture_arr(
 texture_struct *texture_arr,
 int texture_nbr
);

void gaussian_blur_image_2(
 int *I,
 int xdim,
 int ydim,
 double sigma_x,
 double sigma_y,
 int precision,
 int *I_out
);

void gaussian_blur_image(
 int *I,
 int xdim,
 int ydim,
 double sigma,
 int precision,
 int *I_out
);

void gaussian_blur_rgb_image(
 int *inp_image_arr,
 int xdim,
 int ydim,
 double sigma,
 int precision,
 int *out_image_arr
);

void get_grid_cell_median_color(
 int *rgb_image_arr,
 int width,
 int height,
 int inp_i,
 int inp_j,
 int grid,
 int rgb[3]
);

void initialize_canvas_bumpity_image(
 int width,
 int height,
 int **pcanvas_bumpity_image_arr
);

void initialize_canvas_rgb_image(
 int width,
 int height,
 int **pcanvas_rgb_image_arr
);

void load_texture_arr(
 char *filename,
 texture_struct **ptexture_arr,
 int *ptexture_nbr
);

void make_brush_stroke(
 int *rgb_image_arr,
 int width,
 int height,
 int origin_x,
 int origin_y,
 int brush_radius,
 int brush_stroke_color[3],
 double *pxc,
 double *pyc,
 double *ptheta,
 double *prectw,
 double *prectl,
 int *perr_flag
);

void paint_brush_stroke(
 int *reference_rgb_image_arr,
 int width,
 int height,
 int brush_radius,
 brush_stroke_struct brush_stroke_data,
 texture_struct texture_data,
 double opacity_strength,
 double bumpity_strength,
 int *canvas_rgb_image_arr,
 int *canvas_bumpity_image_arr
);

void paint_canvas(
 int *reference_rgb_image_arr,
 int width,
 int height,
 int *initial_canvas_rgb_image_arr,
 int initial_canvas_rgb_image_width,
 int initial_canvas_rgb_image_height,
 int *initial_canvas_bumpity_image_arr,
 int initial_canvas_bumpity_image_width,
 int initial_canvas_bumpity_image_height,
 int *brush_radius_arr,
 int brush_radius_nbr,
 double *opacity_strength_arr,
 double *bumpity_strength_arr,
 double *error_threshold_arr,
 double *grid_size_factor_arr,
 int *texture_ind_arr,
 texture_struct *texture_arr,
 int texture_nbr,
 int **pcanvas_rgb_image_arr,
 int **pcanvas_bumpity_image_arr
);

void paint_canvas_layer(
 int *reference_rgb_image_arr,
 int width,
 int height,
 int brush_radius,
 double opacity_strength,
 double bumpity_strength,
 texture_struct *texture_arr,
 int texture_nbr,
 double error_threshold,
 double grid_size_factor,
 int texture_ind,
 int *canvas_rgb_image_arr,
 int *canvas_bumpity_image_arr
);

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
);

void rotate_image_cubic(
 int *image_arr1,
 int width1,
 int height1,
 double theta,
 int **pimage_arr2,
 int *porigin2_i,
 int *porigin2_j,
 int *pwidth2,
 int *pheight2
);

void rotate_image_linear(
 int *image_arr1,
 int width1,
 int height1,
 double theta,
 int **pimage_arr2,
 int *porigin2_i,
 int *porigin2_j,
 int *pwidth2,
 int *pheight2
);

void rotate_image_nearest_neighbor(
 int *image_arr1,
 int width1,
 int height1,
 double theta,
 int **pimage_arr2,
 int *porigin2_i,
 int *porigin2_j,
 int *pwidth2,
 int *pheight2
);

void scale_image(
 int *image_arr1,
 int width1,
 int height1,
 int *image_arr2,
 int width2,
 int height2,
 char *method,
 char *gaussian
);

void scale_image_cubic(
 int *image_arr1,
 int width1,
 int height1,
 int *image_arr2,
 int width2,
 int height2
);

void scale_image_linear(
 int *image_arr1,
 int width1,
 int height1,
 int *image_arr2,
 int width2,
 int height2
);

void scale_image_nearest_neighbor(
 int *image_arr1,
 int width1,
 int height1,
 int *image_arr2,
 int width2,
 int height2
);

void scale_rgb_image(
 int *rgb_image_arr1,
 int width1,
 int height1,
 int *rgb_image_arr2,
 int width2,
 int height2,
 char *method,
 char *gaussian
);
