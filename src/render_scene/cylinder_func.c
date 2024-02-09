/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:27:16 by ahammoud          #+#    #+#             */
/*   Updated: 2024/02/07 16:37:08 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

double	cy_dicriminant(t_ray ray, double *t1, double *t2, t_cy cylinder)
{
	t_vec	oc;
	t_ray	scaled;
	double	a;
	double	b;
	double	c;

	oc = vecminus(ray.origin, cylinder.center);
	scaled.direction = vecscale(vecnormalize(cylinder.axis), \
		vecdot(ray.direction, vecnormalize(cylinder.axis)));
	scaled.origin = vecscale(vecnormalize(cylinder.axis), \
		vecdot(oc, vecnormalize(cylinder.axis)));
	a = vecdot(vecminus(ray.direction, scaled.direction), \
		vecminus(ray.direction, scaled.direction));
	b = 2.0 * vecdot(vecminus(ray.direction, scaled.direction), \
		vecminus(oc, scaled.direction));
	c = vecdot(vecminus(oc, scaled.origin), vecminus(oc, scaled.origin)) \
		- 0.25 * cylinder.diameter * cylinder.diameter;
	*t1 = (-b - sqrt((b * b) - (4 * a * c))) / (2.0 * a);
	*t2 = (-b + sqrt((b * b) - (4 * a * c))) / (2.0 * a);
	return ((b * b) - (4 * a * c));
}

int	cylinder_intersaction(t_ray ray, double *t, t_cy cylinder)
{
	double	dicriminant;
	double	h2;
	double	h1;
	double	t1;
	double	t2;

	dicriminant = cy_dicriminant(ray, &t1, &t2, cylinder);
	if (dicriminant < 0)
		return (0);
	h1 = vecdot(vecminus(vecplus(ray.origin, vecscale(ray.direction, t1)), \
		cylinder.center), cylinder.axis);
	h2 = vecdot(vecminus(vecplus(ray.origin, vecscale(ray.direction, t2)), \
		cylinder.center), cylinder.axis);
	if (t1 > 1e-6 && h1 > 0.0 && h1 <= cylinder.height)
	{
		*t = t1;
		return (1);
	}
	if (t2 > 1e-6 && h2 > 0.0 && h2 <= cylinder.height)
	{
		*t = t2;
		return (1);
	}
	return (0);
}

void	calculate_diffuse_cy(t_vec p, t_vec n, t_vars *vars, t_cy cylinder)
{
	t_vec	light_direction;
	double	cos_angle;

	light_direction = vecnormalize(vecminus(vars->light.origin, p));
	cos_angle = fabs(vecdot(n, light_direction));
	vars->color.r *= cylinder.r;
	vars->color.g *= cylinder.g;
	vars->color.b *= cylinder.b;
	if (cos_angle > 0.0)
	{
		if (!shadowed(vars, p, vars->light, (char *)&cylinder))
		{
			vars->color.r += (cylinder.r * cos_angle) * vars->light.ratio;
			vars->color.g += (cylinder.g * cos_angle) * vars->light.ratio;
			vars->color.b += (cylinder.b * cos_angle) * vars->light.ratio;
		}
	}
	vars->color = ft_clamping(cylinder.r, cylinder.g, cylinder.b, vars);
}

t_vec	cy_normal(t_vec p, t_cy cylinder)
{
	t_vec	cp;
	double	projection;
	t_vec	along_axis;

	cp = vecminus(p, cylinder.center);
	projection = vecdot(cp, cylinder.axis);
	along_axis = vecscale(cylinder.axis, projection);
	return (vecnormalize(vecminus(cp, along_axis)));
}

int	calculate_cylinder_color(t_ray ray, t_vars *vars, \
		t_cy cylinder, double t_cylinder)
{
	t_vec	intersection;
	t_vec	cylinder_normal;

	calculate_ambient(vars);
	intersection = vecplus(ray.origin, vecscale(ray.direction, t_cylinder));
	cylinder_normal = cy_normal(intersection, cylinder);
	calculate_diffuse_cy(intersection, cylinder_normal, vars, cylinder);
	return (create_trgb(0, vars->color.r, vars->color.g, vars->color.b));
}
