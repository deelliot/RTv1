/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:06:58 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 12:31:51 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_object	sphere_prototype(void)
{
	return ((t_object){
		.object.sphere = (t_sphere)
		{
			.origin = default_origin(),
			.transform = default_transform_1(),
			.material = default_material_1()
		},
		.type = OBJECT_SPHERE
	});
}

void	parse_sphere(t_parser *parser, t_object *shape)
{
	dispatch_find_subobject_keyword(parser, shape);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_sphere(parser, shape);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("sphere syntax error");
	transform_object(&shape->object.sphere.transform);
}
