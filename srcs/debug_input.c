/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:52:00 by thakala           #+#    #+#             */
/*   Updated: 2022/10/22 14:33:32 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	navigate_camera(t_win *win)
{
	win->objects.list[win->input.item_idx]
}

int	apply_mouse_move_scalar(t_win *win)
{
	static const t_mouse_move_scalars	mouse_move_scalars[] = {
		navigate_camera
	};

	mouse_move_scalars[win->input.mode](win);
}

int	key_handler(int key, t_win *win)
{
	(void)key;
	(void)win;
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
