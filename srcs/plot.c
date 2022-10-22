/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:40:28 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/22 12:15:54 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	plot_points(t_win *win, t_object *sphere, t_pt_light light)
{
	t_index			obj_space;
	t_index			world;
	int				i;
	t_tuple			position;
	t_ray			ray;
	t_intersections list;
	t_tuple			lit_point;
	t_phong			vectors;
	uint32_t		final_colour;
	t_tuple			colour_argb;

	// a lot of these variables I image will be in a struct,
	// so it gets passed around instead of having to create them here.

	obj_space.row = -1;
	while (++obj_space.row < HEIGHT)
	{
		world.row = ((t_fl)7 / (t_fl)2) - ((t_fl)7 / (t_fl)HEIGHT) * (t_fl)obj_space.row;
		obj_space.col = -1;
		while (++obj_space.col < WIDTH)
		{
			world.col = ((t_fl)7 / (t_fl)2) - ((t_fl)7 / (t_fl)WIDTH) * (t_fl)obj_space.col;
			position = point(world.col, world.row, 10);
			ray.origin = (t_tuple){.tuple.units = (t_units){0.0, 0.0, -5.0, 1}};
			ray.direction = normalize(tuple_sub(position, ray.origin));
			sphere_intersection(&ray, sphere, &list, win);
			i = -1;
			while (++i < list.num)
			{
				if (list.intersections[i].hit == 1)
				{
					lit_point = hit_position(&ray, list.intersections[i].time);
					vectors.surface_normal = normal_at_sphere(&sphere->object.sphere, &lit_point);
					vectors.eye = ray.direction;
					colour_argb = lighting(sphere->object.sphere.material, light, vectors, lit_point);
					final_colour = argb_to_hex(&colour_argb.tuple.colour);
					img_pixel_put(win, obj_space.col, obj_space.row, final_colour);
				}
			}
		}
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}