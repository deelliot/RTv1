/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_subobjects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:44:56 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 16:21:27 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	plane_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.plane.origin,
			&shape->object.plane.transform,
			&shape->object.plane.material));
}

int	sphere_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.sphere.origin,
			&shape->object.sphere.transform,
			&shape->object.sphere.material));
}

int	cone_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cone.origin,
			&shape->object.cone.transform,
			&shape->object.cone.material));
}

int	cylinder_subobject_keywords(t_parser *parser, t_object *shape)
{
	return (find_subobject_keyword(parser, &shape->object.cylinder.origin,
			&shape->object.cylinder.transform,
			&shape->object.cylinder.material));
}

int	dispatch_find_subobject_keyword(t_parser *parser, t_object *shape)
{
	static const t_subobject_keyword_fn	kw_fns[] = \
	{
		plane_subobject_keywords,
		sphere_subobject_keywords,
		cone_subobject_keywords,
		cylinder_subobject_keywords
	};

	return (kw_fns[shape->type - OBJECT_INDEX_OFFSET](parser, shape));
}
