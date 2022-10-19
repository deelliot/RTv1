/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:12:35 by thakala           #+#    #+#             */
/*   Updated: 2022/10/19 10:04:52 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static char	*unravel_tuple(t_tuple *tuple)
{
	char	*res;

	asprintf(&res, "\n");
}

static char	*unravel_transform(
	t_transform *transform,
	char *translation_tuple,
	char *rotation_tuple,
	char *scale_tuple)
{
	*translation_tuple = unravel_tuple(&transform->translation);
	*rotation_tuple = unravel_tuple(&transform->rotation);
	*scale_tuple = unravel_tuple(&transform->scale);
}

static char	*unravel_matrix_four(t_mtx_4 *matrix)
{
	char	*res;

	asprintf(&res, "\n");
}

static void	unravel_plane(t_object *object, int fd)
{
	dprintf(fd, "\n");
}

/*
Verbose mode in parallel to also print out the calculated matrices?
Perhaps debug them elsewhere to keep this as a configuration file generator?
*/

static void	unravel_sphere(t_object *object, int fd)
{
	char	*origin_tuple;
	char	*translation_tuple;
	char	*rotation_tuple;
	char	*scale_tuple;
	char	*colour_tuple;
	char	*resultant_matrix;
	char	*inverse_matrix;

	origin_tuple = unravel_tuple(&object->object.sphere.origin);
	unravel_transform(
		&object->object.sphere.transform,
		translation_tuple,
		rotation_tuple,
		scale_tuple);
	colour_tuple = unravel_tuple(&object->object.sphere.colour);
	resultant_matrix = \
		unravel_matrix_four(&object->object.sphere.transform.matrix.resultant);
	inverse_matrix = \
		unravel_matrix_four(&object->object.sphere.transform.matrix.inverse);
	dprintf(fd, "\
%s\
%s\
%s\
%s\
%s\
%s\
\n");
}

static void	unravel_cone(t_object *object, int fd)
{
	dprintf(fd, "\n");
}

static void	unravel_cylinder(t_object *object, int fd)
{
	dprintf(fd, "\n");
}

static void	unravel_camera(t_object *object, int fd)
{
	dprintf(fd, "\n");
}

static void	unravel_light(t_object *object, int fd)
{
	dprintf(fd, "\n");
}

static void	unravel_object_error(t_object *object, int fd)
{
	dprintf(fd, "\n");
}

static void	unravel_object_none(t_object *object, int fd)
{
	dprintf(fd, "\n");
}

static int	get_fd_automatic(void)
{
	static char	template[] = "crash_situation_XXXXXXXXX.scn";
	int			fd_automatic;
	uint8_t		t;

	t = 0;
	fd_automatic = -1;
	while (fd_automatic < 0)
	{
		if (++t > 100)
		{
			printf("mkstemps failed 100 times in a row, quitting!\n");
			break ;
		}
		printf("opening crash_situation fd: ");
		fd_automatic = mkstemps(template, 4);
		printf("%d\n", fd_automatic);
	}
	return (fd_automatic);
}

int	unravel_objects_array(t_objects *objects, uint8_t automatic)
{
	static const t_unravel	\
				unravel[] = {
		unravel_plane, unravel_sphere,
		unravel_cone, unravel_cylinder,
		unravel_camera, unravel_light,
		unravel_object_error, unravel_object_none
	};
	static int	fd_automatic = -1;
	uint64_t	c;

	if (automatic && fd_automatic < 0)
	{
		fd_automatic = get_fd_automatic();
		if (fd_automatic < 0)
			return (EXIT_FAILURE);
	}
	if (objects->len == 0)
	{
		dprintf(STDERR_FILENO, "No objects in objects array!\n");
		return (EXIT_SUCCESS);
	}
	c = 0;
	while (c < objects->len)
	{
		unravel[objects->list[c].type](&objects->list[c].object);
		c++;
	}
}
