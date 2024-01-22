/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:27:16 by ahammoud          #+#    #+#             */
/*   Updated: 2024/01/22 12:31:05 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int	plane_intersaction(t_ray ray, double *t, t_pl plane)
{
	double	dot;

	dot = vecdot(vecnormalize(plane.normal), ray.direction);
	if (fabs(dot) < 1e-4)
		return (0);
	*t = vecdot(plane.normal, \
		vecscale(vecminus(plane.point, ray.origin), 1 / dot));
	if (*t < 0)
		return (0);
	return (1);
}

void	calculate_diffuse_plane(t_vec p, t_vec n, t_vars *vars, t_pl plane)
{
	t_vec	light_dir;
	double	cos_angle;

	light_dir = vecnormalize(vecminus(vars->light.origin, p));
	cos_angle = vecdot(n, light_dir);
	if (cos_angle > 0)
	{
		if (!shadowed(vars, p, vars->light, (char *)&plane))
		{
			vars->color.r += (plane.r * cos_angle) * vars->light.ratio;
			vars->color.g += (plane.g * cos_angle) * vars->light.ratio;
			vars->color.b += (plane.b * cos_angle) * vars->light.ratio;
		}
		vars->color.r = ft_clamp(vars->color.r, 0, 255);
		vars->color.g = ft_clamp(vars->color.g, 0, 255);
		vars->color.b = ft_clamp(vars->color.b, 0, 255);
	}
}

int	calculate_plane_color(t_ray ray, t_vars *vars, t_pl plane, double t_plane)
{
	t_vec	intersection;

	calculate_ambient(vars);
	intersection = vecplus(ray.origin, vecscale(ray.direction, t_plane));
	calculate_diffuse_plane(intersection, plane.normal, vars, plane);
	return (create_trgb(0, vars->color.r, vars->color.g, vars->color.b));
}
