#include "RTv1.h"

void	transform_object(t_transform *object)
{
	identity_matrix_set(&object->matrix);
	translate(&object->matrix, &object->translation);
	rotate(&object->matrix, &object->rotation);
	scale(&object->matrix, &object->scale);
	object->inverse = object->matrix;
	matrix_inversion(&object->inverse, 4);
}

void	transform_plane(t_object *plane)
{
	(void)plane;
}

void	transform_sphere(t_object *sphere)
{
	transform_object(&sphere->object.sphere.transform);
}

void	transform_cone(t_object *cone)
{
	(void)cone;
}

void	transform_cylinder(t_object *cylinder)
{
	(void)cylinder;
}

void	transform_camera(t_camera *camera)
{
	t_mtx		view_matrix;

	identity_matrix_set(&camera->transform.matrix);
	translate(&camera->transform.matrix, &camera->transform.translation);
	rotate(&camera->transform.matrix, &camera->transform.rotation);
	scale(&camera->transform.matrix, &camera->transform.scale);
	view_matrix = view_transform(camera->origin, camera->center_of_interest , vector(0, 1, 0));
	matrix_multi_square(&camera->transform.matrix, &view_matrix, 4);
	camera->transform.inverse = camera->transform.matrix;
	matrix_inversion(&camera->transform.inverse, 4);
}

void	transform_camera_defunct(t_camera *camera)
{
	t_mtx		view_matrix;
	t_tuple		from_to;
	t_tuple		new_from_to;
	t_mtx		rotation_temp;
	t_tuple		negative_rotation;
	t_tuple		new_up;

	printf("\n\n\n");
	from_to = tuple_sub(camera->origin, camera->center_of_interest);
	print_tuple(&from_to, 0, "from_to, original");
	printf("magnitude original: %f\n", magnitude(from_to));
	negative_rotation = tuple_scale(camera->transform.rotation, -1);
	identity_matrix_set(&rotation_temp);
	rotate(&rotation_temp, &negative_rotation);
	new_from_to = matrix_tuple_multi(&rotation_temp, &from_to);
	print_tuple(&new_from_to, 0, "from_to, new");
	printf("magnitude: %f\n", magnitude(from_to));
	new_from_to = tuple_add(new_from_to, camera->center_of_interest);
	print_tuple(&new_from_to, 0, "from, new");

	new_up = cross_product(vector(1, 0, 0), new_from_to);
	print_tuple(&new_up, 0, "new_up");

	identity_matrix_set(&camera->transform.matrix);
	translate(&camera->transform.matrix, &camera->transform.translation);
	//rotate(&camera->transform.matrix, &camera->transform.rotation);
	scale(&camera->transform.matrix, &camera->transform.scale);
	view_matrix = view_transform(new_from_to, camera->center_of_interest , new_up);
	matrix_multi_square(&camera->transform.matrix, &view_matrix, 4);
	camera->transform.inverse = camera->transform.matrix;
	matrix_inversion(&camera->transform.inverse, 4);
}

void	transform_light(t_object *light)
{
	(void)light;
}

// void	transform_objects(t_objects *objects)
// {
// 	static const t_object_transform	object_transform[] = {
// 		transform_plane,
// 		transform_sphere,
// 		transform_cone,
// 		transform_cylinder,
// 		transform_camera,
// 		transform_light};
// 	uint64_t						i;

// 	i = -1;
// 	while (++i < objects->count)
// 	{
// 		object_transform[objects->list[i].type](&objects->list[i]);
// 	}
// }

/*void	transform_tuple(t_tuple tuple, t_transform *actions)
{

}*/
