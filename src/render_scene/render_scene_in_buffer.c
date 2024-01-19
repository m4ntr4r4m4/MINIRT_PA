/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   render_scene_in_buffer.c                           :+:      :+:    :+:   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/23 08:56:27                                            */
/*   Updated: 2024/01/19 20:07:19 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
# include "ray.h"
#include "stdlib.h"
#include <math.h>
#include <stdio.h>

t_ray	init_ray(t_vars *vars,  double u, double v)
{
	t_ray ray;

	ray.origin = vars->camera.origin;
	ray.direction =  vecnormalize(vecplus(vars->camera.direction ,  vecplus( vecscale(vars->camera.right, u), vecscale(vars->camera.up, v))));
	return (ray);
}
unsigned int trace_ray(t_vars* vars, t_ray ray)
{
	double t;
	double closest_t;
	int sphere_idx;
	int plane_idx;
	int cy_idx;

	closest_t = INFINITY;
	sphere_idx = -1;
	plane_idx = -1;
	cy_idx = -1;
	for (size_t i = 0; i < vars->sp_size; i++)
	{
		if(sphere_intersaction(vars, ray, &t, vars->spheres[i]) && t < closest_t)		
		{
			closest_t = t;
			sphere_idx = i;
			plane_idx = -1;
			cy_idx = -1;
		}
	}
	for (size_t i = 0; i < vars->pl_size; i++)
	{
		if (plane_intersaction(vars, ray, &t, vars->planes[i]) && t < closest_t)			
		{
			closest_t = t;
			sphere_idx = -1;
			plane_idx = i;
			cy_idx = -1;
		}
	}
	for (size_t i = 0; i < vars->cy_size; i++)
	{
		if (cylinder_intersaction(vars, ray, &t, vars->cylanders[i]) && t < closest_t)		
		{
			closest_t = t;
			sphere_idx = -1;
			plane_idx = -1;
			cy_idx = i;
		}
	}
	if (sphere_idx != -1)
	{
		sphere_intersaction(vars, ray, &t, vars->spheres[sphere_idx]);

			return (calculate_sphere_color(ray, vars, vars->spheres[sphere_idx], t));
	}
	if (plane_idx != -1)
	{
		plane_intersaction(vars, ray, &t, vars->planes[plane_idx]);			
		return (calculate_plane_color(ray, vars, vars->planes[plane_idx], t));
	}
	if (cy_idx != -1)
	{
	cylinder_intersaction(vars, ray, &t, vars->cylanders[cy_idx]);
		return (calculate_cylinder_color(ray, vars, vars->cylanders[cy_idx], t));
	}
	
	return (0);
}

t_vec vector_to_vec(t_vector vector)
{
	return ((t_vec){.x = vector.x, .y = vector.y, .z = vector.z});
}

void copy_sphere(t_vars *vars, t_sphere_list list)
{
	vars->sp_size = list.size;
	if (vars->sp_size > 0)
		vars->spheres = malloc(sizeof(t_sp) * vars->sp_size);
	for (size_t i = 0; i < vars->sp_size; i++)
	{
		vars->spheres[i].center = vector_to_vec(list.spheres[i].center);
		vars->spheres[i].radius = list.spheres[i].diameter / 2;
		vars->spheres[i].r = list.spheres[i].color.r;
		vars->spheres[i].g = list.spheres[i].color.g;
		vars->spheres[i].b = list.spheres[i].color.b;
	}
}

void copy_plane(t_vars *vars, t_plane_list list)
{
	vars->pl_size = list.size;
	if (vars->pl_size > 0)
		vars->planes = malloc(sizeof(t_pl) * vars->pl_size);
	for (size_t i = 0; i < vars->pl_size; i++)
	{
		vars->planes[i].point = vector_to_vec(list.planes[i].position);
		vars->planes[i].normal = vector_to_vec(list.planes[i].normal);
		vars->planes[i].r = list.planes[i].color.r;
		vars->planes[i].g = list.planes[i].color.g;
		vars->planes[i].b = list.planes[i].color.b;
	}
}

void copy_cy(t_vars *vars, t_cylider_list list)
{
	vars->cy_size = list.size;
	printf("this size %zu\n", vars->cy_size);
	if (vars->cy_size > 0)
		vars->cylanders = malloc(sizeof(t_cy) * vars->cy_size);
	for (size_t i = 0; i < vars->cy_size; i++)
	{
		vars->cylanders[i].center = vector_to_vec(list.cylinders[i].geometric_center);
		vars->cylanders[i].diameter = list.cylinders[i].diameter;
		vars->cylanders[i].axis = vector_to_vec(list.cylinders[i].direction);
		vars->cylanders[i].height = list.cylinders[i].height;
		vars->cylanders[i].r = list.cylinders[i].color.r;
		vars->cylanders[i].g = list.cylinders[i].color.g;
		vars->cylanders[i].b = list.cylinders[i].color.b;
	printf("cy pos : %f, %f, %f\n",vars->cylanders[i].center.x, vars->cylanders[i].center.y, vars->cylanders[i].center.z);
	}
}

void copy_light(t_vars *vars, t_light light)
{
	vars->light.origin = vector_to_vec(light.position);
	vars->light.ratio = light.brightness;
	vars->light.r = light.color.r;
	vars->light.g = light.color.g;
	vars->light.b = light.color.b;
}

void copy_ambient(t_vars *vars, t_parameters params)
{
	vars->ambient.ratio = params.ambient_lighting.intensity;
	vars->ambient.r = params.ambient_lighting.color.r;
	vars->ambient.g = params.ambient_lighting.color.g;
	vars->ambient.b = params.ambient_lighting.color.b;
}

t_vec choose_up_vector(t_vec forward) {
    t_vec up;
    
    up = vec(0,1,0);

    if (fabs(fabs(forward.y) - 1.0) < 1e-6)
        up = vec(1, 0, 0);
    return up;
}

void copy_camera(t_vars *vars, t_parameters params)
{
	vars->camera.fov = params.camera.field_of_view;
	vars->camera.direction = vector_to_vec(params.camera.orientation);
	vars->camera.origin = vector_to_vec(params.camera.position);
	//vars->camera.right = vecnormalize(veccross(vec(.0,.0,1) ,vecnormalize(vars->camera.direction)));
	vars->camera.right = veccross(choose_up_vector(vars->camera.direction) ,vars->camera.direction);
	vars->camera.up = veccross(vars->camera.direction, vars->camera.right);
}

t_vars init_vars(t_parameters params)
{
	t_vars vars;

	copy_light(&vars, params.light);
	printf("1\n");
	copy_ambient(&vars, params);
	printf("2\n");
	copy_camera(&vars, params);
	printf("3\n");
	copy_sphere(&vars, params.sphere_list);
	printf("4\n");
	copy_cy(&vars, params.cylinder_list);
	printf("5\n");
	copy_plane(&vars, params.plane_list);
	printf("6\n");
	return (vars);
}

void	render_scene_in_buffer(t_parameters parameters, unsigned int *buffer,
			int height, int width)
{
	t_vars 		vars;

	vars = init_vars(parameters);
	//your code goes here
	t_ray ray;
	double u;
	double v;
	int i;

	i = 0;
	for (i = 0; i < height * width; i++)
	{
		u = (((double)(i % width) / width) - 0.5) * tan((vars.camera.fov)) * 2;
		v= ((double)(((double)i / width) / width) - 0.5) * tan((vars.camera.fov)) * 2;
		ray = init_ray(&vars, u , v);
		buffer[i] = trace_ray(&vars, ray);
	}
	if (vars.sp_size)
		free(vars.spheres);
	if (vars.cy_size)
		free(vars.cylanders);
	if (vars.pl_size)
		free(vars.planes);
	printf("DONE!\n");
}

