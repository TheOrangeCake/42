/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:05:52 by masase            #+#    #+#             */
/*   Updated: 2025/07/24 11:28:33 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/libft.h" 
# include "../gnl/get_next_line.h" 
# include "../minilibx-linux/mlx.h"

# define ESC_KEY 65307
# define W 119
# define S 115
# define A 97
# define D 100
# define Q 113
# define E 101
# define T 116
# define G 103
# define F 102
# define H 104
# define R 114

# define NONE 0
# define CHECKER 1
# define STRIPE 2
# define EARTH 3
# define MARS 4
# define MERCU 5
# define PLUTO 6
# define VENUS 7
# define EARTH_BUMP 8
# define MARS_BUMP 9
# define MERCU_BUMP 10
# define PLUTO_BUMP 11
# define VENUS_BUMP 12
# define U_SCALE 0.45f
# define V_SCALE 0.8f
# define XPM_HEIGHT 500
# define XPM_WIDTH 1000

# define HEIGHT 1080
# define WIDTH 1920

typedef enum t_tab_type
{
	LIGHT,
	PLANE,
	CYLINDER,
	SPHERE,
	CONE,
}	t_tab_type;

// BASE PIECE STRUCT -----------------------
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vector
{
	float	a;
	float	b;
	float	c;
}	t_vector;

typedef struct s_pos
{
	float	x;
	float	y;
	float	z;
}	t_pos;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_pattern
{
	int		size;
	t_color	color1;
	t_color	color2;
}	t_pattern;

// SAVE LINE -------------------------------
typedef struct s_pixel
{
	int			i;
	int			j;
	t_vector	horiz;
	t_vector	vert;
}	t_pixel;

typedef struct s_world
{
	float		aspect_ratio;
	float		fov_rad;
	t_vector	right;
	t_vector	up;
	t_vector	forward;
	t_vector	world_up;
}	t_world;

typedef struct s_value_int
{
	int	x;
	int	y;
}	t_value_int;

typedef struct s_value_float
{
	float	t1;
	float	t2;
}	t_value_float;

typedef struct s_inter
{
	float		height_projection;
	t_vector	oc;
	t_vector	d_perp;
	t_vector	oc_perp;	
	t_vector	axis;
	float		b;
	float		a;
	float		c;
	float		disc;
}	t_inter;

typedef struct s_inter_cone
{
	float		height_projection;
	t_vector	oc;
	t_vector	d_perp;
	t_vector	oc_perp;	
	t_vector	axis;
	float		k;
	float		k2;
	float		dv;
	float		oc_v;
	float		b;
	float		a;
	float		c;
	float		disc;
}	t_inter_cone;

// SCENE ITEM STRUCT -----------------------
typedef struct s_camera
{
	t_vector	vector;
	t_pos		pos;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_pos	pos;
	t_color	color;
	float	ratio;
}	t_light;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_plane
{
	t_vector	vector;
	t_pos		pos;
	t_color		color;
	int			texture_type;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	vector;
	t_pos		pos;
	t_color		color;
	float		d;
	float		h;
	float		shine;
	int			texture_type;
}	t_cylinder;

typedef struct s_cone
{
	t_vector	vector;
	t_pos		pos;
	t_color		color;
	float		d;
	float		h;
	float		shine;
	int			texture_type;
}	t_cone;

typedef struct s_sphere
{
	t_pos		pos;
	t_color		color;
	float		d;
	float		shine;
	int			texture_type;
	bool		bump;
}	t_sphere;

// MAIN STRUCT -----------------------------
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_color		color;
	float		t;
	t_vector	hit_point;
	t_vector	normal;
	t_vector	reflect;
	t_plane		*hit_plane;
	t_cylinder	*hit_cylinder;
	t_sphere	*hit_sphere;
	t_cone		*hit_cone;
	bool		hit_inside;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
}	t_ray;

typedef struct s_quantity
{
	int		camera;
	int		ambiant;
	int		light;
	int		plane;
	int		cylinder;
	int		sphere;
	int		cone;
}	t_quantity;

typedef struct s_bump
{
	void	*earth;
	void	*earthbump;
	void	*mars;
	void	*marsbump;
	void	*mercu;
	void	*mercubump;
	void	*pluto;
	void	*plutobump;
	void	*venus;
	void	*venusbump;
}	t_bump;

typedef struct s_params
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		**light;
	t_plane		**plane;
	t_cylinder	**cylinder;
	t_sphere	**sphere;
	t_cone		**cone;
	t_pattern	checker;
	t_pattern	stripe;
	t_bump		bump;
	t_quantity	quantity;
	void		*mlx;
	void		*window;
	t_data		data;
}	t_params;

// PARSING ---------------------------------

bool		ft_error(char *str);
bool		check_arg(char *str);
bool		fill_struct(char *line, t_params *params);
bool		read_scene(char *file, t_params *params);
bool		parsing(char *file, t_params *params);
int			ft_isdigit_point(int c);

// save utils
bool		put_rgb(int *i, int *value, char *line);
bool		put_vector(int *i, float *value, char *line);
bool		put_position(int *i, float *value, char *line);
bool		save_shine(int *i, float *value, char *line);
bool		save_texture(int *i, int *value, char *line);
void		skip_space(char *line, int *i);
void		skip_alpha(char *line, int *i);
bool		skip_sign_and_number(char *line, int *i);

// save camera
bool		save_camera(char *line, t_params *params);
bool		save_fov(char *line, int *i, t_camera *camera);
bool		cam_view_point(char *line, int *i, t_camera *camera);
bool		cam_vector(char *line, int *i, t_camera *camera);

// save ambient
bool		save_ambiant(char *line, t_params *params);
bool		amb_rgb(char *line, int *i, t_ambient *ambient);
bool		amb_ratio(char *line, int *i, t_ambient *ambient);

// save light
bool		save_light(char *line, t_params *params);
bool		light_view_point(char *line, int *i, t_light *light);
bool		light_rgb(char *line, int *i, t_light *light);
bool		light_ratio(char *line, int *i, t_light *light);

// save sphere
bool		save_sphere(char *line, t_params *params);
bool		sphere_view_point(char *line, int *i, t_sphere *sphere);
bool		sphere_rgb(char *line, int *i, t_sphere *sphere);
bool		sphere_diameter(char *line, int *i, t_sphere *sphere);

// save plane
bool		save_plane(char *line, t_params *params);
bool		plane_vector(char *line, int *i, t_plane *plane);
bool		plane_view_point(char *line, int *i, t_plane *plane);
bool		plane_rgb(char *line, int *i, t_plane *plane);

// save cylinder
bool		save_cylinder(char *line, t_params *params);
bool		cylinder_diameter(char *line, int *i, t_cylinder *cylinder);
bool		cylinder_height(char *line, int *i, t_cylinder *cylinder);
bool		cylinder_view_point(char *line, int *i, t_cylinder *cylinder);
bool		cylinder_vector(char *line, int *i, t_cylinder *cylinder);
bool		cylinder_rgb(char *line, int *i, t_cylinder *cylinder);

// save cone
bool		save_cone(char *line, t_params *params);
bool		cone_diameter(char *line, int *i, t_cone *cone);
bool		cone_height(char *line, int *i, t_cone *cone);
bool		cone_view_point(char *line, int *i, t_cone *cone);
bool		cone_vector(char *line, int *i, t_cone *cone);
bool		cone_rgb(char *line, int *i, t_cone *cone);

// utils
int			ft_isspace(int c);
float		ft_atof(const char *str);
void		decimal_atof(int i, const char *str, float *resultat);

// utils 2
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void		*alloc_tab(t_params *params, t_tab_type type);
size_t		setup_tab_type(void ***tab, int **current_size,
				t_params *params, t_tab_type type);

// printf
void		print_camera_as_array(t_camera *cam);
void		print_plane_as_array(t_plane *plane);
void		print_sphere_as_array(t_sphere *sp);
void		print_cylinder_as_array(t_cylinder *cyl);
void		print_ambiance_as_array(t_ambient *amb);
void		print_point_as_array(t_light *light);

// IMAGE -----------------------------------
void		render(t_params *params);
void		render_object(t_params *params);
void		my_mlx_pixel_put(t_params *params, int x, int y, t_color color);

// RAYON -----------------------------------
void		intersection_sphere(t_params *params, t_ray *ray);
void		intersection_plane(t_params *params, t_ray *ray);
void		intersection_cylinder(t_params *params, t_ray *ray);
float		calculate_cap_t(t_cylinder *cylinder, t_ray *ray, t_vector *normal);
void		set_t_cap(t_ray *ray, float t, t_cylinder *cylinder,
				t_vector normal);
void		intersection_cone(t_params *params, t_ray *ray);
float		calculate_lateral_t_cone(t_cone *cone, t_ray *ray);
float		calculate_cap_t_cone(t_cone *cone, t_ray *ray, t_vector *normal);
void		set_t_cap_cone(t_ray *ray, float t, t_cone *cone, t_vector normal);

// LIGHT -----------------------------------
void		calculate_ambient_light(t_params *params, t_ray *ray);
void		calculate_diffuse_light(t_params *params, t_ray *ray);
void		calculate_specular_light(t_params *params, t_ray *ray);

// SHADOW ----------------------------------
bool		shadow_check(t_params *params, t_ray *ray, int index);
bool		shadow_sphere_check(t_params *params, t_ray *shadow,
				float light_dist, t_vector light_pos);
bool		shadow_plane_check(t_params *params, t_ray *shadow,
				t_ray *ray, t_vector light_pos);
bool		shadow_cylinder_check(t_params *params, t_ray *shadow,
				float light_dist);
bool		shadow_cylinder_cap_check(t_params *params, t_ray *shadow,
				float light_dist);
bool		shadow_cone_check(t_params *params, t_ray *shadow,
				float light_dist);		

// PATTERN ---------------------------------
void		initialise_pattern(t_params *params);
void		initialise_bump(t_params *params);
void		initialise_data(t_params *params, t_data *data, int type);
t_color		checkerboard_plane(t_params *params, t_ray *ray);
t_color		checkerboard_sphere(t_params *params,
				t_vector hit_point, t_sphere *sphere);
t_color		checkerboard_cylinder(t_params *params,
				t_vector hit_point, t_cylinder *cyl);
t_color		stripe_plane(t_params *params, t_vector hit_point);
t_color		stripe_sphere(t_params *params,
				t_vector hit_point, t_sphere *sphere);
t_color		stripe_cylinder(t_params *params,
				t_vector hit_point, t_cylinder *cyl);
t_color		planet_sphere(t_params *params,
				t_vector hit_point, t_sphere *sphere, int type);
void		get_sphere_color(t_params *params, t_ray *ray, t_color *color);
void		get_cylinder_color(t_params *params, t_ray *ray, t_color *color);
void		get_plane_color(t_params *params, t_ray *ray, t_color *color);
void		get_cone_color(t_params *params, t_ray *ray, t_color *color);
void		apply_bump(t_params *params, t_ray *ray, t_sphere *sphere);

// UTIL ------------------------------------
void		free_all(t_params *params);
void		free_maps(t_params *params);
void		free_cone(t_params *params);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
t_vector	vector_multi(float x, t_vector v1);
t_vector	vector_divi(t_vector v1, float x);
t_vector	vector_cross(t_vector v1, t_vector v2);
float		vector_dot(t_vector v1, t_vector v2);
float		vector_norm2(t_vector v1);
void		vector_normalize(t_vector *v1);
t_vector	pos_to_vector(t_pos pos);
t_color		color_add(t_color c1, t_color c2);
float		vector_lenght(t_vector v1);

// HOOk ------------------------------------
void		hook(t_params *params);
int			x_close_window(t_params *params);
void		camera_pos_forward(t_params *params);
void		camera_pos_backward(t_params *params);
void		camera_pos_left(t_params *params);
void		camera_pos_right(t_params *params);
void		camera_pos_up(t_params *params);
void		camera_pos_down(t_params *params);
void		camera_look_up(t_params *params);
void		camera_look_down(t_params *params);
void		camera_look_left(t_params *params);
void		camera_look_right(t_params *params);

#endif
