/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:27:16 by ahammoud          #+#    #+#             */
/*   Updated: 2024/01/22 12:32:45 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

double	ft_max(double x, double y)
{
	if (x > y)
		return (x);
	return (y);
}

double	ft_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double	ft_clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_acolor	ft_clamping(int r, int g, int b, t_vars *vars)
{
	t_acolor	p;

	p.r = ft_clamp(vars->color.r, vars->ambient.ratio * r, 255);
	p.g = ft_clamp(vars->color.g, vars->ambient.ratio * g, 255);
	p.b = ft_clamp(vars->color.b, vars->ambient.ratio * b, 255);
	return (p);
}
