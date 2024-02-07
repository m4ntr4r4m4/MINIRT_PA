/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:27:16 by ahammoud          #+#    #+#             */
/*   Updated: 2024/01/22 12:32:28 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int	check_shadow_sp(char *add, t_vars *vars, t_vec p, t_ablight light)
{
	size_t	i;
	double	t;
	t_ray	shadow;

	shadow.origin = p;
	shadow.direction = vecnormalize(vecminus(light.origin, p));
	i = -1;
	t = 0;
	while (++i < vars->sp_size)
	{
		if (strlen(add) && !strcmp((char *)&vars->spheres[i], add))
			continue ;
		sphere_intersaction(shadow, &t, vars->spheres[i]);
		if (t > 1e-8 && t < veclength(vecminus(light.origin, p)))
			return (1);
	}
	return (0);
}

int	check_shadow_pl(char *add, t_vars *vars, t_vec p, t_ablight light)
{
	size_t	i;
	double	t;
	t_ray	shadow;

	shadow.origin = p;
	shadow.direction = vecnormalize(vecminus(light.origin, p));
	i = 0;
	t = 0;
	while (i < vars->pl_size)
	{
		if (strlen(add) && !strcmp((char *)&vars->planes[i], add))
			continue ;
		plane_intersaction(shadow, &t, vars->planes[i]);
		if (t > 1e-8 && t < veclength(vecminus(light.origin, p)))
			return (1);
		i++;
	}
	return (0);
}

int	check_shadow_cy(char *add, t_vars *vars, t_vec p, t_ablight light)
{
	size_t	i;
	double	t;
	t_ray	shadow;

	shadow.origin = p;
	shadow.direction = vecnormalize(vecminus(light.origin, p));
	i = 0;
	t = 0;
	while (i < vars->cy_size)
	{
		if (strlen(add) && !strcmp((char *)&vars->cylanders[i], add))
			continue ;
		cylinder_intersaction(shadow, &t, vars->cylanders[i]);
		if (t > 1e-8 && t < veclength(vecminus(light.origin, p)))
			return (1);
		i++;
	}
	return (0);
}

int	shadowed(t_vars *vars, t_vec p, t_ablight light, char *add)
{
	if (check_shadow_sp(add, vars, p, light))
		return (1);
	if (check_shadow_pl(add, vars, p, light))
		return (1);
	if (check_shadow_cy(add, vars, p, light))
		return (1);
	return (0);
}
