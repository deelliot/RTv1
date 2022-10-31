/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:52:00 by thakala           #+#    #+#             */
/*   Updated: 2022/10/31 14:18:31 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	realign_camera(t_win *win)
{
	// static int64_t	z = -5;
	t_tuple		to_from;
	t_tuple		to;

	//win->world.camera.transform.rotation = (t_tuple){.tuple.units = {0, M_PI_4, 0, POINT_1}};
	// win->world.camera.origin = point(0, 0, -5);
	win->world.camera.transform.rotation = (t_tuple){.tuple.rotation = {
		.x_wid_lat_pitch = win->input.mouse.diff.row * 0.007 \
			+ win->world.camera.transform.rotation.tuple.rotation.x_wid_lat_pitch//,
		//.y_hei_vert_yaw = win->input.mouse.diff.col * 0.007 \
			//+ win->world.camera.transform.rotation.tuple.rotation.y_hei_vert_yaw,
	}};
	print_tuple(&win->world.camera.transform.rotation, 0, "camera.transform.rotation");
	print_tuple(&(t_tuple){.tuple.units = {.x = win->input.mouse.diff.row * 0.007, .y = win->input.mouse.diff.col * 0.007}}, 0, "mouse.diff {x, y}");
	win->world.camera.transform.matrix = identity_matrix();
	win->world.camera.origin = point(0, 1.5, -5);
	rotate(&win->world.camera.transform.matrix, &win->world.camera.transform.rotation);
	// translate(&win->world.camera.transform.matrix, &win->world.camera.transform.translation);
	// scale(&win->world.camera.transform.matrix, &win->world.camera.transform.scale);

	to_from = tuple_sub(win->world.camera.origin, (t_tuple){.tuple.units = {0, 1, 0, POINT_1}});
	to = matrix_tuple_multi(&win->world.camera.transform.matrix, &to_from);
	win->world.camera.transform.matrix = view_transform(win->world.camera.origin, to, vector(0, 1, 0));
	//win->world.camera.transform.matrix = view_transform(win->world.camera.origin, (t_tuple){.tuple.units = {0, 1, 0, POINT_1}}, vector(0, 1, 0));
	win->world.camera.transform.inverse = win->world.camera.transform.matrix;
	matrix_inversion(&win->world.camera.transform.inverse, 4);
	// print_world(&win->world, &win->world.camera);
	// win->world.camera.origin = point(0, 0, z--);
	//printf("%lli\n", z);
/*	win->world.camera.origin = matrix_tuple_multi(&win->world.camera.transform.inverse, \
	&win->world.camera.origin);*/
	// win->world.camera.transform.matrix = (win->world.camera.origin, point(0, 0, 0), vector(0, 1, 0));
//	win->world.camera.center_of_interest = point(0, 0, 0);
}


void	navigate_camera(t_win *win)
{
	(void)win;
	//win->objects.list[win->input.item_idx]
	realign_camera(win);
	render(win, &win->world.camera);

}

int	apply_mouse_move_scalar(t_win *win)
{
	static const t_mouse_move_scalars	mouse_move_scalars[] = {
		navigate_camera
	};

	mouse_move_scalars[win->input.mode](win);
	return (TRUE);
}

int	key_handler(int key, t_win *win)
{
	(void)key;
	(void)win;
	printf("key: %i\n", key);
	return (0);
}

void	mouse_register_click_down(int button, t_point mouse_pointer, t_win *win)
{
	(void)button;
	win->input.mouse.prev = win->input.mouse.curr;
	win->input.mouse.curr = mouse_pointer;
	if (button == RIGHT_CLICK)
		win->input.mouse.rmb_is_down = TRUE;
}

void	mouse_register_click_up(int button, t_point mouse_pointer, t_win *win)
{
	(void)button;
	(void)mouse_pointer;
	if (button == RIGHT_CLICK)
		win->input.mouse.rmb_is_down = FALSE;
}

int	mouse_handler_scroll_up(t_point *mouse_pointer, t_win *win)
{
	(void)mouse_pointer;
	(void)win;
	return (EXIT_SUCCESS);
}

int	mouse_handler_scroll_down(t_point *mouse_pointer, t_win *win)
{
	(void)mouse_pointer;
	(void)win;
	return (EXIT_SUCCESS);
}


int	mouse_handler_down(int button, int x, int y, t_win *win)
{
	(void)button;
	(void)x;
	(void)y;
	(void)win;
	if (button == RIGHT_CLICK)
		mouse_register_click_down(button, (t_point){.row = y, .col = x}, win);
	return (EXIT_SUCCESS);
}

int	mouse_handler_move(int x, int y, t_win *win)
{
	(void)x;
	(void)y;
	(void)win;
	if (win->input.mouse.rmb_is_down == TRUE)
	{
		win->input.mouse.diff = (t_point){.row = y - win->input.mouse.curr.row,
			.col = x - win->input.mouse.curr.col};
		apply_mouse_move_scalar(win);
		win->input.mouse.curr = (t_point){.row = y, .col = x};
	}
	return (EXIT_SUCCESS);
}

int	mouse_handler_up(int button, int x, int y, t_win *win)
{
	(void)button;
	(void)x;
	(void)y;
	(void)win;
	if (button == RIGHT_CLICK)
		mouse_register_click_up(button, (t_point){.row = y, .col = x}, win);
	return (EXIT_SUCCESS);
}
