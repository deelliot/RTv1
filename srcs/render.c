#include "RTv1.h"

void	render(t_win *win, t_camera *camera)
{
	t_canvas	canvas;
	t_tuple		colour;

	canvas.vertical = 0;
	while (canvas.vertical < camera->size.vertical)
	{
		canvas.horizontal = 0;
		while (canvas.horizontal < camera->size.horizontal)
		{
			win->world.ray = ray_for_pixel(camera, (t_canvas){.vertical = \
				canvas.vertical, .horizontal = canvas.horizontal});
			if (0 && ((canvas.vertical == 0 && canvas.horizontal == 0) \
				|| (canvas.vertical == 50 && canvas.horizontal == 100)
				|| (canvas.vertical == 100 && canvas.horizontal == 200)))
			{
				printf("\n\nDEBUG:______\n");
				print_camera(camera, 0);
				printf("{%hu, %hu}\n", canvas.vertical, canvas.horizontal);
				print_ray(&win->world.ray, 0);
			}
			colour = colour_at(&win->world);
			img_pixel_put(win, canvas.horizontal, canvas.vertical,
				argb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
		}
		canvas.vertical++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}
