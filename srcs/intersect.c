/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:14:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/21 03:16:16 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/* circumference of sphere: 2πr.
Assume for now all spheres are unit spheres, therefore radius of 1

diameter of sphere: 2 * r
*/

void	identify_hit(t_intersections *array)
{
	int	i;
	int	hit;

	i = -1;
	hit = -1;
	while (++i < array->num)
	{
		if (array->intersections[i].time >= 0 && hit == -1)
		{
			hit = i;
			array->intersections[i].hit = 1;
		}
		else
			array->intersections[i].hit = 0;
	}
}

void	sphere_intersection(t_ray *ray, t_object *shape, t_intersections *array, t_win *win)
{
	t_fl	discriminant;
	t_fl	a;
	t_fl	b;
	t_fl	c;
	t_tuple	sphere_to_ray;

	sphere_to_ray = tuple_sub(&ray->origin, &shape->object.sphere.origin);
	a = dot_product(&ray->direction, &ray->direction);
	b = 2 * dot_product(&ray->direction, &sphere_to_ray);
	c = dot_product(&sphere_to_ray, &sphere_to_ray) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0.0)
	{
		array->num = 0;
		array->intersections = NULL;
		return ;
	}
	else
	{
		array->num = 2;
		array->intersections = (t_intersect *)malloc(sizeof(t_intersect) * 2);
		if (!array->intersections)
			handle_errors(win, "intersect malloc fail");
		if (discriminant <= 1)
		{
			array->intersections[0].time = (-b - sqrt(discriminant)) / (2 * a);
			array->intersections[0].shape = shape;
			array->intersections[1].time = (-b + sqrt(discriminant)) / (2 * a);
			array->intersections[1].shape = shape;
		}
		else
		{
			array->intersections[0].time = (-b - sqrt(discriminant)) / (2 * a);
			array->intersections[0].shape = shape;
			array->intersections[1].time = array->intersections[0].time + 2; // radius * 2
			array->intersections[1].shape = shape;
		}
	}
	identify_hit(array);
}

/*t_object sphere(t_tuple *origin, t_transform *transform, t_tuple *colour)
{
	return ((t_object)
	{
		.object.sphere = (t_sphere)
		{
			.origin = (t_tuple){.tuple.units = (t_units)
				{origin->tuple.units.x,
				origin->tuple.units.y,
				origin->tuple.units.z,
				origin->tuple.units.w}},
			.transform = (t_transform){transform->translation,
				transform->rotation,
				transform->scale},
			.colour = (t_tuple){.tuple.colour = (t_colour)
				{colour->tuple.colour.a,
				colour->tuple.colour.r,
				colour->tuple.colour.g,
				colour->tuple.colour.b}}
		},
		.type = OBJECT_SPHERE
	});
}*/

t_tuple	hex_to_argb(uint32_t colour)
{
	return ((t_tuple){.tuple.colour.a = ((colour >> 24) & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.r = ((colour >> 16) & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.g = ((colour >> 8) & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.b = (colour & 0xFFu) / (t_fl)0xFFu});
}

static t_fl	truncate_fl(t_fl min, t_fl clamped, t_fl max)
{
	if (clamped > max)
		return (max);
	else if (clamped < min)
		return (min);
	return (clamped);
}

uint32_t	argb_to_hex(t_tuple *colour)
{
	return ((uint32_t)(255 * truncate_fl(0.0, colour->tuple.colour.a, 1.0)) << 24
		| (uint32_t)(255 * truncate_fl(0.0, colour->tuple.colour.r, 1.0)) << 16
		| (uint32_t)(255 * truncate_fl(0.0, colour->tuple.colour.g, 1.0)) << 8
		| (uint32_t)(255 * truncate_fl(0.0, colour->tuple.colour.b, 1.0)));
}

// int main(void)
// {
// 	t_ray		ray;
// 	t_objects	objects;
// 	t_tuple		purple;
// 	t_transform transform;
// 	t_object	object_sphere;
// 	t_intersections array;
// 	int i;

// 	purple = hex_to_argb(0x4c00b0);
// 	ray.origin.tuple.units = (t_units){ 0.0, 2.0, -5.0, 1.0 };
// 	ray.direction.tuple.units = (t_units){ 0.0, 0.0, 1.0, 0.0 };
// 	transform =(t_transform)
// 	{
// 		.translation = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
// 		},
// 		.rotation = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1 }
// 		},
// 		.scale = (t_tuple)
// 		{
// 			.tuple.units = (t_units){ 1.0, 1.0, 1.0, POINT_1 }
// 		}
// 	};
// 	objects.list = (t_object *)malloc(sizeof(t_object) * 3);
// 	if (objects.list == NULL)
// 		exit(EXIT_FAILURE);
// 	object_sphere = sphere(
// 			&(t_tuple){.tuple.units = (t_units){ 0.0, 0.0, 0.0, POINT_1}},
// 			&transform,
// 			&purple
// 		);
// 	sphere_intersection(&ray, &object_sphere, &array);
// 	if (array.num > 0)
// 		printf("time at 1st: %f\ntime at 2nd: %f\n", array.intersections[0].time ,array.intersections[1].time);
// 	else
// 		printf("no hits\n");
// 	i = -1;
// 	while (++i < array.num)
// 	{
// 		if (array.intersections[i].hit == 1)
// 			printf("time of hit = %f\n", array.intersections[i].time);
// 	}
// 	return (0);
// }