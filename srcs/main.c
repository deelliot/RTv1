/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:10:12 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 14:39:59 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	open_scene_into(t_win *win, const char *str)
{
	win->fd = open(str, O_RDONLY);
	if (win->fd < 0)
		handle_errors("unable to open file");
}

int	close_success(void)
{
	handle_errors("All done :)");
	return (0);
}

int	main(int argc, char **argv)
{
	t_win	win;

	if (argc != 2)
		handle_errors(USAGE);
	open_scene_into(&win, argv[1]);
	initialise_world(&win.world);
	parse_into(&win.world, win.fd);
	initialise_window(&win);
	render(&win, &win.world.camera);
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_hook(win.win, MOUSE_ESC, 0, close_success, &win);
	mlx_loop(win.mlx);
	return (0);
}
