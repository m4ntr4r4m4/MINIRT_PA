#include "ray.h"

void	copy_sphere(t_vars *vars, t_sphere_list list)
{
	size_t	i;

	i = 0;
	vars->sp_size = list.size;
	if (vars->sp_size > 0)
		vars->spheres = malloc(sizeof(t_sp) * vars->sp_size);
	while (i < vars->sp_size)
	{
		vars->spheres[i].center = vector_to_vec(list.spheres[i].center);
		vars->spheres[i].radius = list.spheres[i].diameter / 2;
		vars->spheres[i].r = list.spheres[i].color.r;
		vars->spheres[i].g = list.spheres[i].color.g;
		vars->spheres[i].b = list.spheres[i].color.b;
		i++;
	}
}

void	copy_plane(t_vars *vars, t_plane_list list)
{
	size_t	i;

	i = 0;
	vars->pl_size = list.size;
	if (vars->pl_size > 0)
		vars->planes = malloc(sizeof(t_pl) * vars->pl_size);
	while (i < vars->pl_size)
	{
		vars->planes[i].point = vector_to_vec(list.planes[i].position);
		vars->planes[i].normal = vector_to_vec(list.planes[i].normal);
		vars->planes[i].r = list.planes[i].color.r;
		vars->planes[i].g = list.planes[i].color.g;
		vars->planes[i].b = list.planes[i].color.b;
		i++;
	}
}

void	copy_cy(t_vars *vars, t_cylider_list list)
{
	size_t	i;

	i = 0;
	vars->cy_size = list.size;
	printf("this size %zu\n", vars->cy_size);
	if (vars->cy_size > 0)
		vars->cylanders = malloc(sizeof(t_cy) * vars->cy_size);
	while (i < vars->cy_size)
	{
		vars->cylanders[i].center = \
			vector_to_vec(list.cylinders[i].geometric_center);
		vars->cylanders[i].diameter = list.cylinders[i].diameter;
		vars->cylanders[i].axis = vector_to_vec(list.cylinders[i].direction);
		vars->cylanders[i].height = list.cylinders[i].height;
		vars->cylanders[i].r = list.cylinders[i].color.r;
		vars->cylanders[i].g = list.cylinders[i].color.g;
		vars->cylanders[i].b = list.cylinders[i].color.b;
		i++;
	}
}

void	copy_light(t_vars *vars, t_light light)
{
	vars->light.origin = vector_to_vec(light.position);
	vars->light.ratio = light.brightness;
	vars->light.r = light.color.r;
	vars->light.g = light.color.g;
	vars->light.b = light.color.b;
}

void	copy_ambient(t_vars *vars, t_parameters params)
{
	vars->ambient.ratio = params.ambient_lighting.intensity;
	vars->ambient.r = params.ambient_lighting.color.r;
	vars->ambient.g = params.ambient_lighting.color.g;
	vars->ambient.b = params.ambient_lighting.color.b;
}
