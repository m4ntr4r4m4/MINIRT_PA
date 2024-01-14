/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   render_scene_in_buffer.c                           :+:      :+:    :+:   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/23 08:56:27                                            */
/*   Updated: 2024/01/14 17:32:21 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
# include "ray.h"
#include <math.h>
#include <stdio.h>

t_ray	init_camera_up_right(t_parameters parameters)
{
	t_ray r;

	r.direction = normalize(cross_product(vector(0,0,1), normalize(parameters.camera.orientation)));
	r.origin = cross_product(normalize(parameters.camera.orientation), r.direction);
	return (r);
}

t_ray	init_ray(t_parameters vars, t_ray right_up, long double u, long double v)
{
	t_ray ray;

	ray.origin = vars.camera.position;	
	ray.direction = normalize(add(vars.camera.orientation, add(multiply(right_up.direction, u), multiply(right_up.origin, v))));
	return (ray);
}

unsigned int trace_ray(t_parameters vars, t_ray ray)
{
	long double t;
	long double closest_t;
	int sphere_idx;
	int plane_idx;
	int cy_idx;

	closest_t = INFINITY;
	sphere_idx = -1;
	plane_idx = -1;
	cy_idx = -1;
	for (int i = 0; i < vars.sphere_list.size; i++)
	{
		if (sphere_intersaction(&vars, ray, &t, vars.sphere_list.spheres[i]) && t < closest_t)
		{
			closest_t = t;
			sphere_idx = i;
			plane_idx = -1;
			cy_idx = -1;
		}
	}
	for (int i = 0; i < vars.plane_list.size; i++)
	{
		if (plane_intersaction(&vars, ray, &t, vars.plane_list.planes[i]) && t < closest_t)
		{
			closest_t = t;
			sphere_idx = -1;
			plane_idx = i;
			cy_idx = -1;
		}
	}
	for (int i = 0; i < vars.cylinder_list.size; i++)
	{
		if (cylinder_intersaction(&vars, ray, &t, vars.cylinder_list.cylinders[i]) && t < closest_t)
		{
			closest_t = t;
			sphere_idx = -1;
			plane_idx = -1;
			cy_idx = i;
		}
	}
	if (sphere_idx != -1)
		return (calculate_sphere_color(ray, &vars, vars.sphere_list.spheres[sphere_idx], t));
	if (plane_idx != -1)
		return (calculate_plane_color(ray, &vars, vars.plane_list.planes[plane_idx], t));
	if (cy_idx != -1)
		return (calculate_cylinder_color(ray, &vars, vars.cylinder_list.cylinders[cy_idx], t));
	
	return (0);
}

void	render_scene_in_buffer(t_parameters parameters, unsigned int *buffer,
			int height, int width)
{
	//your code goes here
	t_ray ray;
	t_ray camera_up_right;
	long double u;
	long double v;
	int i;

	i = 0;
	camera_up_right = init_camera_up_right(parameters);
	for (i = 0; i < height * width; i++)
	{
		u = -1 * (((double)(i % width) / width) - 0.5) * tan((parameters.camera.field_of_view)) * 2;
		v= -1 * ((double)(((double)i / width) / width) - 0.5) * tan((parameters.camera.field_of_view)) * 2;
		ray = init_ray(parameters, camera_up_right, u , v);
		buffer[i] = trace_ray(parameters, ray);
	}
	printf("DONE!\n");
}

