/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_in_buffer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:27:16 by ahammoud          #+#    #+#             */
/*   Updated: 2024/01/29 16:21:14 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "ray.h"
#include "stdlib.h"
#include <math.h>
#include <stdio.h>

unsigned int	trace_ray(t_vars *vars, t_ray ray)
{
	vars->closest_t = INFINITY;
	vars->sphere_idx = -1;
	vars->plane_idx = -1;
	vars->cy_idx = -1;
	ft_check_pl(vars, ray);
	ft_check_sp(vars, ray);
	ft_check_cy(vars, ray);
	return (ft_color_obj(vars, ray));
}

t_vec	choose_up_vector(t_vec forward)
{
	t_vec	up;

	up = vec(0, 1, 0);
	if (fabs(fabs(forward.y) - 1.0) < 1e-6)
		up = vec(1, 0, 0);
	return (up);
}

void	copy_camera(t_vars *vars, t_parameters params)
{
	vars->camera.fov = params.camera.field_of_view;
	vars->camera.direction = vector_to_vec(params.camera.orientation);
	vars->camera.origin = vector_to_vec(params.camera.position);
	vars->camera.right = veccross(choose_up_vector(vars->camera.direction), \
		vars->camera.direction);
	vars->camera.up = veccross(vars->camera.direction, vars->camera.right);
}

t_vars	init_vars(t_parameters params)
{
	t_vars	vars;

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

void	render_scene_in_buffer(t_parameters parameters, \
	unsigned int *buffer, int height, int width)
{
	t_vars	vars;
	t_ray	ray;
	double	u;
	double	v;
	int		i;

	vars = init_vars(parameters);
	i = 0;
	printf("FOV %f\n",vars.camera.fov);
	while (i < height * width)
	{
		u = (((double)(i % width) / width) - 0.5) * tan((vars.camera.fov / 2 * M_PI / 180)) * 2;
		v = ((double)(((double)i / width) / height) \
			- 0.5) * tan((vars.camera.fov / 2 * M_PI / 180)) * 2;
		v *= -1 * (double)(width / height);
		ray = init_ray(&vars, u, v);
		buffer[i++] = trace_ray(&vars, ray);
	}
	if (vars.sp_size)
		free(vars.spheres);
	if (vars.cy_size)
		free(vars.cylanders);
	if (vars.pl_size)
		free(vars.planes);
	printf("DONE!\n");
}
