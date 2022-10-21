/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:12:35 by thakala           #+#    #+#             */
/*   Updated: 2022/10/21 01:56:43 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	fd_retryer(int *fd, char template[])
{
	uint8_t	t;

	t = 0;
	while (*fd < 0)
	{
		if (++t > 100)
		{
			dprintf(STDERR_FILENO, \
				"mkstemps failed 100 times in a row, quitting!\n");
			break ;
		}
		*fd = mkstemps(template, 4);
		printf("template: {'%s'}, fd: {'%d'}\n", template, *fd);
	}
}

static void	get_fd_automatic(int *fd_automatic)
{
	char	template[] = "crash_XXXXXXXXX.scn";

	fd_retryer(fd_automatic, template);
}

static void	get_fd_user(int *fd_user)
{
	char		template[] = "user_XXXXXXXXX.scn";

	fd_retryer(fd_user, template);
}

static void	get_fd(t_unravel *unravel)
{
	static int	fd_automatic = -1;

	if (unravel->automatic)
	{
		if (fd_automatic < 0)
		{
			get_fd_automatic(&fd_automatic);
			if (fd_automatic < 0)
				return ;
		}
		unravel->fd = fd_automatic;
	}
	else
		get_fd_user(&unravel->fd);
}

static char	*unravel_tuple(t_tuple *tuple)
{
	char	*res;

	asprintf(&res, TUPLE_FORMAT_0,
		tuple->array[0],
		tuple->array[1],
		tuple->array[2],
		tuple->array[3]);
	return (res);
}

static void	unravel_transform(
	t_transform *transform,
	char **translation_tuple,
	char **rotation_tuple,
	char **scale_tuple)
{
	*translation_tuple = unravel_tuple(&transform->translation);
	*rotation_tuple = unravel_tuple(&transform->rotation);
	*scale_tuple = unravel_tuple(&transform->scale);
}

static char	*unravel_matrix_four(t_mtx *m)
{
	char	*res;

	asprintf(&res, MATRIX_FORMAT_0,
		m->array[0], m->array[1], m->array[2], m->array[3],
		m->array[4], m->array[5], m->array[6], m->array[7],
		m->array[8], m->array[9], m->array[10], m->array[11],
		m->array[12], m->array[13], m->array[14], m->array[15]
		);
	return (res);
}

static void	unravel_plane(t_object *object, t_unravel *unravel)
{
	(void)object;
	dprintf(unravel->fd, "\n");
}

/*
Verbose mode in parallel to also print out the calculated matrices?
Perhaps debug them elsewhere to keep this as a configuration file generator?
*/

static void	unravel_sphere(t_object *object, t_unravel *unravel)
{
	char	*origin_tuple;
	char	*translation_tuple;
	char	*rotation_tuple;
	char	*scale_tuple;
	char	*colour_tuple;
	char	*resultant_matrix;
	char	*inverse_matrix;
	int		status;

	origin_tuple = unravel_tuple(&object->object.sphere.origin);
	unravel_transform(
		&object->object.sphere.transform,
		&translation_tuple,
		&rotation_tuple,
		&scale_tuple);
	colour_tuple = unravel_tuple(&object->object.sphere.material.colour);
	if (unravel->verbose)
	{
		resultant_matrix = \
			unravel_matrix_four(&object->object.sphere.transform.matrix);
		inverse_matrix = \
			unravel_matrix_four(&object->object.sphere.transform.inverse);
		status = dprintf(unravel->fd, "SPHERE\n{\n\
\t%s\t\t\t%s\n\
\t%s\t\t%s\n\
\t%s\t\t%s\n\
\t%s\t\t\t%s\n\
\t%s\t\t\t%s\n\
\t%s\t\t\t\n%s\n\
\t%s\t\t\t\n%s\n\
}\n",
	"origin", origin_tuple,
	"translation", translation_tuple,
	"rotation", rotation_tuple,
	"scale", scale_tuple,
	"colour", colour_tuple,
	"resultant", resultant_matrix,
	"inverse", inverse_matrix);
		free(origin_tuple);
		free(translation_tuple);
		free(rotation_tuple);
		free(scale_tuple);
		free(colour_tuple);
		free(resultant_matrix);
		free(inverse_matrix);
		if (status < 0)
		{
			dprintf(STDERR_FILENO, "dprintf to fd %d failed!", unravel->fd);
			close(unravel->fd);
			unravel->fd = -1;
			if (unravel->nests++ < 7)
			{
				get_fd(unravel);
				unravel_sphere(object, unravel);
			}
		}
	}
	else
	{

		status = dprintf(unravel->fd, "\
\t%s\t\t\t%s\n\
\t%s\t\t%s\n\
\t%s\t\t%s\n\
\t%s\t\t\t%s\n\
\t%s\t\t\t%s\n\
\n",
	"origin", origin_tuple,
	"translation", translation_tuple,
	"rotation", rotation_tuple,
	"scale", scale_tuple,
	"colour", colour_tuple);
		free(origin_tuple);
		free(translation_tuple);
		free(rotation_tuple);
		free(scale_tuple);
		free(colour_tuple);
		if (status < 0)
		{
			dprintf(STDERR_FILENO, "dprintf to fd %d failed!", unravel->fd);
			close(unravel->fd);
			unravel->fd = -1;
			if (unravel->nests++ < 7)
			{
				get_fd(unravel);
				unravel_sphere(object, unravel);
			}
		}
	}
}

static void	unravel_cone(t_object *object, t_unravel *unravel)
{

	(void)object;
	dprintf(unravel->fd, "\n");
}

static void	unravel_cylinder(t_object *object, t_unravel *unravel)
{

	(void)object;
	dprintf(unravel->fd, "\n");
}

static void	unravel_camera(t_object *object, t_unravel *unravel)
{

	(void)object;
	dprintf(unravel->fd, "\n");
}

static void	unravel_light(t_object *object, t_unravel *unravel)
{

	(void)object;
	dprintf(unravel->fd, "\n");
}

static void	unravel_object_error(t_object *object, t_unravel *unravel)
{

	(void)object;
	dprintf(unravel->fd, "\n");
}

static void	unravel_object_none(t_object *object, t_unravel *unravel)
{

	(void)object;
	dprintf(unravel->fd, "\n");
}

int	unravel_objects_array(t_objects *objects, t_unravel *unravel)
{
	static const t_unravels	\
				unravels[] = {
		unravel_plane, unravel_sphere,
		unravel_cone, unravel_cylinder,
		unravel_camera, unravel_light,
		unravel_object_error, unravel_object_none
	};
	uint64_t	c;

	get_fd(unravel);
	if (objects->count == 0)
	{
		dprintf(STDERR_FILENO, "No objects in objects array!\n");
		return (EXIT_SUCCESS);
	}
	c = 0;
	while (c < objects->count)
	{
		unravels[objects->list[c].type](&objects->list[c], unravel);
		c++;
	}
	return (EXIT_SUCCESS);
}
