/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:17:08 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/29 13:15:56 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"
# include "tuple.h"
# include "matrices.h"
# include "colour_and_light.h"
# include "objects.h"
# include "world.h"
#include "debug.h"

# define USAGE "<instructions>"
# define WIDTH 201
# define HEIGHT 101
# define WALL_WIDTH 7
# define WALL_HEIGHT 7
# define KEY_DOWN 2
# define ESC 53
# define EPSILON 0.00001

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_img;

typedef struct s_coords
{
	uint32_t	row;
	uint32_t	col;
}				t_coords;

typedef struct s_pixel_index
{
	t_fl		row;
	t_fl		col;
}				t_index;

typedef struct s_win
{
	t_img		img;
	void		*mlx;
	void		*win;
	t_world		world;
	t_input		input;
}	t_win;

typedef void	(*t_intersect_function)(t_ray, void *, t_world *);

typedef void	(*t_shading_function)(t_world *, void *, t_tuple *, t_light *);

typedef void	(*t_computation_fn)(t_world *);

/*tuple operations & matrix maths*/
t_tuple	point(t_fl x, t_fl y, t_fl z);
t_tuple	vector(t_fl x, t_fl y, t_fl z);
t_tuple	colour(t_fl a, t_fl r, t_fl g, t_fl b);
t_tuple	tuple_add(t_tuple a, t_tuple b);
t_tuple	tuple_sub(t_tuple a, t_tuple b);
t_tuple	tuple_multi(t_tuple a, t_tuple b);
t_tuple	tuple_scale(t_tuple a, t_fl scalar);
t_tuple	colour_scale(t_tuple a, t_fl scalar);
t_tuple	tuple_div(t_tuple a, t_fl scalar);
t_fl	magnitude(t_tuple a);
t_tuple	normalize(t_tuple a);
t_fl	dot_product(t_tuple a, t_tuple b);
t_tuple	cross_product(t_tuple a, t_tuple b);
int		matrix_comparison(t_fl **a, t_fl **b, uint32_t size);
t_tuple	matrix_tuple_multi(t_mtx *mtx, t_tuple *tuple);
void	matrix_multi_square(t_mtx *mtx, t_mtx *transformation, uint32_t size);
t_mtx	transpose_matrix(t_mtx *mtx);
t_mtx	identity_matrix(void);
t_fl	determinant(t_mtx *mtx, uint32_t size);
void	matrix_inversion(t_mtx *mtx, uint32_t size);


/* matrix transformations */
// t_tuple	translate_tuple(t_tuple *tuple, t_tuple *transform);
// t_tuple	scale_tuple(t_tuple *tuple, t_tuple *transform);
void	rotate(t_mtx *mtx, t_tuple *rotations);
// t_tuple	rot_x_tuple(t_tuple *tuple, t_fl angle);
// t_tuple	rot_y_tuple(t_tuple *tuple, t_fl angle);
// t_tuple	rot_z_tuple(t_tuple *tuple, t_fl angle);

void	translate(t_mtx *mtx, t_tuple *transform);
void	scale(t_mtx *mtx, t_tuple *transform);
void	rot_x(t_mtx *mtx, t_fl angle);
void	rot_y(t_mtx *mtx, t_fl angle);
void	rot_z(t_mtx *mtx, t_fl angle);

/* matrix support */
void	identity_matrix_set(t_mtx *dst);

/* ray transformations */
t_ray	ray_translation(t_ray ray, t_tuple transform);
t_ray	ray_scale(t_ray ray, t_tuple transform);
t_ray	ray_transform(t_ray *ray, t_mtx *transform);
t_tuple	hit_position(t_ray *ray, t_fl distance);

/* error handle*/
void	handle_errors(char *str);
// void	handle_errors(t_win *win, char *str);
// void	free_win(t_win *win);

/* initialise */
void	initialise_world(t_world *world);
void	initialise_window(t_win *win);

/* handle input*/
int		key_handler(int key, t_win *win);
int		mouse_handler_scroll_up(t_point *mouse, t_win *win);
int		mouse_handler_scroll_down(t_point *mouse, t_win *win);
int		mouse_handler_down(int button, int x, int y, t_win *win);
int		mouse_handler_move(int x, int y, t_win *win);
int		mouse_handler_up(int button, int x, int y, t_win *win);
// int		handle_input(int key, t_win *win);
int		handle_input(int key);

/* colour and lighting*/
t_tuple	hex_to_argb(uint32_t colour);
uint32_t	argb_to_hex(t_colour *colour);
t_tuple shade_hit(t_world *world);
t_tuple	lighting(t_material material, t_light *light, t_phong vectors,
	t_tuple point);

/* object intialisation */
t_object	sphere(t_tuple origin, t_transform transform, t_material material);

/* object intersection */
void	intersect_world(t_world *world);
void	identify_hit(t_world *world);
// void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array);
//void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array, t_win *win);
// void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array);
void	sphere_intersection(t_ray ray, void *sphere, t_world *world);

/* reflections*/
t_tuple	reflect(t_tuple input, t_tuple normal);

/* object transformation */
void	transform_object(t_transform *object);
// void	transform_objects(t_objects *objects);

/* view transfrom */
t_mtx	view_transform(t_tuple from, t_tuple to, t_tuple up);

/* normals */
t_tuple	normal_at(void *object, t_tuple *point);
t_tuple	normal_at_sphere(void *sphere, t_tuple *point_at);

/* plot pixels */
// void	plot_points(t_win *win, t_object *sphere);
void	plot_points(t_win *win);
void	plot_points_params(t_win *win);
// void	img_pixel_put(t_win *win, int x, int y, t_tuple *colour);
void	img_pixel_put(t_win *win, int x, int y, unsigned int colour);

/* testing */
void	ft_print_mtx(t_mtx *mtx);
void	default_world(t_world *world);
t_transform	default_transform(void);

/* camera */
t_camera	camera(t_canvas size, t_fl field_of_view);
t_ray	ray_for_pixel(t_camera *camera, t_canvas position);
void	prepare_computations(t_world *world);
t_tuple	colour_at(t_world *world);
void	render(t_win *win, t_camera *camera);

void	print_tuple(t_tuple *tuple, uint8_t indent_level, const char *description);

#endif
