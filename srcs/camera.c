#include "RTv1.h"

static t_fl	get_pixel_size(t_camera *camera, t_canvas size, t_fl field_of_view)
{
	t_fl		half_view;
	t_fl		aspect;

	half_view = (t_fl)tan(field_of_view / 2);
	aspect = (t_fl)size.horizontal / (t_fl)size.vertical;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	return (camera->half_width * 2 / size.horizontal);
}

t_camera	camera(t_tuple origin, t_transform transform, t_fl field_of_view, t_canvas size)
{
	t_camera camera;

	camera.origin = origin;
	camera.transform = transform;
	camera.center_of_interest =  point(0, 0, 0);
	camera.field_of_view = field_of_view,
	camera.size = (t_canvas){.vertical = size.vertical, .horizontal = size.horizontal};
	camera.pixel_size = get_pixel_size(& camera, size, field_of_view);
	return (camera);
}
