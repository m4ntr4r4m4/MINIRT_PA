/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecMath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:27:16 by ahammoud          #+#    #+#             */
/*   Updated: 2024/01/15 15:15:18 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ray.h"

t_vec	vecplus(t_vec vec1, t_vec vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}

t_vec	vecminus(t_vec vec1, t_vec vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

t_vec	vecscale(t_vec vec, double scaler)
{
	vec.x *= scaler;
	vec.y *= scaler;
	vec.z *= scaler;
	return (vec);
}

t_vec	veccross(t_vec vec1, t_vec vec2)
{
	t_vec	c;

	c.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	c.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	c.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return (c);
}

t_vec	vec(double x, double y, double z)
{
	return ((t_vec){.x = x, .y = y, .z = z});
}
