/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:19:24 by thakala           #+#    #+#             */
/*   Updated: 2022/10/21 02:08:45 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# define TUPLE_FORMAT TUPLE_FORMAT_0
# define TUPLE_FORMAT_0 "(%3.3lf, %3.3lf, %3.3lf, %3.3lf)"
# define TUPLE_FORMAT_1 "(%6.lf, %6.lf, %6.lf, %6.lf)"
# define TUPLE_FORMAT_2 "(%12.12lf, %12.12lf, %12.12lf, %12.12lf)"
# define MATRIX_FORMAT MATRIX_FORMAT_0
# define MATRIX_FORMAT_0 "\
\t\t\t\t\t|%3.3lf, %3.3lf, %3.3lf, %3.3lf|\n\
\t\t\t\t\t|%3.3lf, %3.3lf, %3.3lf, %3.3lf|\n\
\t\t\t\t\t|%3.3lf, %3.3lf, %3.3lf, %3.3lf|\n\
\t\t\t\t\t|%3.3lf, %3.3lf, %3.3lf, %3.3lf|"
# define MATRIX_FORMAT_1 "\
\t\t\t\t\t|%6.lf, %6.lf, %6.lf, %6.lf|\n\
\t\t\t\t\t|%6.lf, %6.lf, %6.lf, %6.lf|\n\
\t\t\t\t\t|%6.lf, %6.lf, %6.lf, %6.lf|\n\
\t\t\t\t\t|%6.lf, %6.lf, %6.lf, %6.lf|"
# define MATRIX_FORMAT_2 "\
\t\t\t\t\t|%12.12lf, %12.12lf, %12.12lf, %12.12lf|\n\
\t\t\t\t\t|%12.12lf, %12.12lf, %12.12lf, %12.12lf|\n\
\t\t\t\t\t|%12.12lf, %12.12lf, %12.12lf, %12.12lf|\n\
\t\t\t\t\t|%12.12lf, %12.12lf, %12.12lf, %12.12lf|"

typedef struct s_unravel
{
	int		fd;
	uint8_t	automatic : 1;
	uint8_t	verbose : 1;
	uint8_t	nests : 3;
}	t_unravel;

typedef void	(*t_unravels)(t_object *, t_unravel *);

int	unravel_objects_array(t_objects *objects, t_unravel *unravel);

#endif