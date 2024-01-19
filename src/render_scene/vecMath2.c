/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecMath2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:32:43 by ahammoud          #+#    #+#             */
/*   Updated: 2024/01/15 15:09:05 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_vec	vecnormalize(t_vec vec)
{
	t_vec	norm;
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	norm.x = vec.x / len;
	norm.y = vec.y / len;
	norm.z = vec.z / len;
	return (norm);
}

double	vecdot(t_vec vec1, t_vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
double veclength(t_vec vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec	at(t_ray ray, double t)
{
	t_vec	pos;

	ray.direction = vecscale(ray.direction, t);
	pos.x = ray.origin.x + ray.direction.x;
	pos.y = ray.origin.y + ray.direction.y;
	pos.z = ray.origin.z + ray.direction.z;
	return (pos);
}
