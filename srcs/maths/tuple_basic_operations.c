/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_basic_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:37:39 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 10:39:22 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	tuple_add(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x + b.tuple.units.x,
		.tuple.units.y = a.tuple.units.y + b.tuple.units.y,
		.tuple.units.z = a.tuple.units.z + b.tuple.units.z,
		.tuple.units.w = a.tuple.units.w + b.tuple.units.w
	});
}

t_tuple	tuple_sub(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x - b.tuple.units.x,
		.tuple.units.y = a.tuple.units.y - b.tuple.units.y,
		.tuple.units.z = a.tuple.units.z - b.tuple.units.z,
		.tuple.units.w = a.tuple.units.w - b.tuple.units.w
	});
}

t_tuple	tuple_multi(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x * b.tuple.units.x,
		.tuple.units.y = a.tuple.units.y * b.tuple.units.y,
		.tuple.units.z = a.tuple.units.z * b.tuple.units.z,
		.tuple.units.w = a.tuple.units.w * b.tuple.units.w
	});
}

t_tuple	tuple_div(t_tuple a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.units.x = a.tuple.units.x / scalar,
		.tuple.units.y = a.tuple.units.y / scalar,
		.tuple.units.z = a.tuple.units.z / scalar,
		.tuple.units.w = a.tuple.units.w / scalar
	});
}
