/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:27:16 by ahammoud          #+#    #+#             */
/*   Updated: 2024/02/07 16:36:38 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ray.h"

double	sp_dicriminant(t_ray ray, double *t1, double *t2, t_sp sphere)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;

	oc = vecminus(ray.origin, sphere.center);
	a = vecdot(ray.direction, ray.direction);
	b = 2.0 * vecdot(oc, ray.direction);
	c = (double)vecdot(oc, oc) - (sphere.radius * sphere.radius);
	*t1 = (-b - sqrt((b * b) - (4 * a * c))) / (2.0 * a);
	*t2 = (-b + sqrt((b * b) - (4 * a * c))) / (2.0 * a);
	return ((b * b) - (4 * a * c));
}

int	sphere_intersaction(t_ray ray, double *t, t_sp sphere)
{
	double	t1;
	double	t2;
	double	dicriminant;

	dicriminant = sp_dicriminant(ray, &t1, &t2, sphere);
	if (dicriminant < 0)
		return (0);
	if (t1 > 0 && (t1 < t2 || t2 <= 0))
		*t = t1;
	else
		*t = t2;
	return (1);
}

void	calculate_diffuse(t_vec p, t_vec n, t_vars *vars, t_sp sphere)
{
	double	cos_angle;

	cos_angle = vecdot(n, vecnormalize(vecminus(vars->light.origin, p)));
	if (cos_angle > 1e-4)
	{
		if (!shadowed(vars, p, vars->light, (char *)&sphere))
		{
			vars->color.r += (sphere.r * cos_angle) * vars->light.ratio;
			vars->color.g += (sphere.g * cos_angle) * vars->light.ratio;
			vars->color.b += (sphere.b * cos_angle) * vars->light.ratio;
			printf("not shadowed\n");
		}
	}
	else
	{
		vars->color.r *= sphere.r;
		vars->color.g *= sphere.g;
		vars->color.b *= sphere.b;
	}
	vars->color.r = ft_clamp(vars->color.r, 0, 255);
	vars->color.g = ft_clamp(vars->color.g, 0, 255);
	vars->color.b = ft_clamp(vars->color.b, 0, 255);
}

void	calculate_ambient(t_vars *vars)
{
	vars->color.r = vars->ambient.ratio * vars->ambient.r / 255;
	vars->color.g = vars->ambient.ratio * vars->ambient.g / 255;
	vars->color.b = vars->ambient.ratio * vars->ambient.b / 255;
}

int	calculate_sphere_color(t_ray ray, t_vars *vars, \
	t_sp sphere, double t_sphere)
{
	t_vec	intersection;
	t_vec	sphere_normal;

	calculate_ambient(vars);
	intersection = vecplus(ray.origin, vecscale(ray.direction, t_sphere));
	sphere_normal = vecnormalize(vecminus(intersection, sphere.center));
	calculate_diffuse(intersection, sphere_normal, vars, sphere);
	return (create_trgb(0, vars->color.r, vars->color.g, vars->color.b));
}
