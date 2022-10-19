/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:17:08 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/19 12:46:15 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <mlx.h>
# include <stdint.h>
#include <stdio.h>
# include "libft.h"
# include "tuple.h"
# include "matrices.h"
# include "objects.h"
# include "colour.h"
#include "debug.h"

# define WIDTH 400
# define HEIGHT 400
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

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}			t_ray;

typedef struct s_intersect
{
	t_fl		time;
	t_object	*shape;
	int			hit;
}				t_intersect;

// need new name here
typedef struct s_intersections
{
	int			num;
	t_intersect	*intersections;

}				t_intersections;

typedef struct s_win
{
	t_img		img;
	void		*mlx;
	void		*win;
}	t_win;

/*tuple operations & matrix maths*/
t_tuple	point(t_fl x, t_fl y, t_fl z);
t_tuple	vector(t_fl x, t_fl y, t_fl z);
t_tuple	tuple_add(t_tuple *a, t_tuple *b);
t_tuple	tuple_sub(t_tuple *a, t_tuple *b);
t_tuple	tuple_multi(t_tuple *a, t_fl scalar);
t_tuple	tuple_div(t_tuple *a, t_fl scalar);
t_fl	magnitude(t_tuple *a);
t_tuple	normalize(t_tuple *a);
t_fl	dot_product(t_tuple *a, t_tuple *b);
t_tuple	cross_product(t_tuple *a, t_tuple *b);
int		matrix_comparison(t_fl **a, t_fl **b, uint32_t size);
t_tuple	matrix_tuple_multi(t_mtx *mtx, t_tuple *tuple);
void	matrix_multi_square(t_mtx *mtx, t_mtx *transformation, uint32_t size);
t_mtx	transpose_matrix(t_mtx *mtx);
t_mtx	identity_matrix(void);
t_fl	determinant(t_mtx *mtx, uint32_t size);
void	matrix_inversion(t_mtx *mtx, uint32_t size);


/* matrix transformations */
t_tuple	translate_tuple(t_tuple *tuple, t_tuple *transform);
t_tuple	scale_tuple(t_tuple *tuple, t_tuple *transform);
void	rotate(t_mtx *mtx, t_tuple *rotations);
t_tuple	rot_x_tuple(t_tuple *tuple, t_fl angle);
t_tuple	rot_y_tuple(t_tuple *tuple, t_fl angle);
t_tuple	rot_z_tuple(t_tuple *tuple, t_fl angle);

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

/* error handle*/
// void	handle_errors(char *str);
void	handle_errors(t_win *win, char *str);
void	free_win(t_win *win);

/* initialise */
void	initialise_window(t_win *win);

/* handle input*/
int		handle_input(int key, t_win *win);

/* colour */
t_tuple	hex_to_argb(uint32_t colour);

/* object intialisation */
t_object	sphere(t_tuple *origin, t_transform *transform, t_tuple *colour);

/* object intersection */
void	identify_hit(t_intersections *array);
// void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array);
void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array, t_win *win);

/* plot pixels */
void	plot_points(t_win *win, t_object *sphere);
void	img_pixel_put(t_win *win, int x, int y, unsigned int colour);
/* testing */
void	ft_print_num_array(t_fl **array, int y, int x);

#endif
