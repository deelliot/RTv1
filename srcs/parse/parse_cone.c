/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:05:28 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/30 14:08:43 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_object	cone_prototype(void)
{
	return ((t_object){
		.object.cone = (t_cone)
		{
			.origin = default_origin(),
			.transform = default_transform_1(),
			.material = default_material_1(),
			.min = -INFINITY,
			.max = INFINITY,
			.closed = false
		},
		.type = OBJECT_CONE
	});
}

void	parse_cone(t_parser *parser, t_object *shape)
{
	if (dispatch_find_subobject_keyword(parser, shape))
	{
		parser->c += ft_clear_whitespace(&parser->string[parser->c]);
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			parse_cone(parser, shape);
		}
		else if (!find_matching_bracket(parser))
			handle_errors("cone syntax error");
	}
	else if (cone_and_cylinder_objects(parser, shape))
	{
		parser->c += ft_clear_whitespace(&parser->string[parser->c]);
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			parse_cone(parser, shape);
		}
		else if (!find_matching_bracket(parser))
			handle_errors("cone syntax error");
	}
	else if (!find_matching_bracket(parser))
		handle_errors("cone syntax error");
}
