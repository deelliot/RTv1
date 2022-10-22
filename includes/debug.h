/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:19:24 by thakala           #+#    #+#             */
/*   Updated: 2022/10/22 14:32:12 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# include "RTv1.h"
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

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

enum e_event
{
	ON_KEY_DOWN = 2,
	ON_KEY_UP = 3,
	ON_MOUSE_DOWN = 4,
	ON_MOUSE_UP = 5,
	ON_MOUSE_MOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_mouse
{
	MOVE = 0,
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	MIDDLE_CLICK = 3,
	SCROLL_DN = 4,
	SCROLL_UP = 5
};

enum e_key
{
	KEY_COLOUR = 8,
	KEY_ESC = 53,
	KEY_L_CMD = 259,
	KEY_R_CMD = 260
};

typedef enum e_input_mode
{
	MODE_CAMERA,
	MODE_LIGHT,
	MODE_OBJECT
}	t_mode;

typedef struct s_point
{
	int		row;
	int		col;
}	t_point;

typedef struct s_mouse
{
	t_point	prev;
	t_point	curr;
	t_point	diff;
	uint8_t	rmb_is_down : 1;
}	t_mouse;


typedef struct s_keyboard
{
	uint8_t	cmd_toggled : 1;
}	t_keyboard;

typedef struct s_user_inputs
{
	t_mouse		mouse;
	t_keyboard	keyboard;
	t_mode		mode;
	uint64_t	item_idx;
}	t_input;

typedef struct s_unravel
{
	int		fd;
	uint8_t	automatic : 1;
	uint8_t	verbose : 1;
	uint8_t	nests : 3;
}	t_unravel;


typedef void	(*t_mouse_move_scalars)(t_win *);

typedef void	(*t_unravels)(t_object *, t_unravel *);

int	unravel_objects_array(t_objects *objects, t_unravel *unravel);

#endif