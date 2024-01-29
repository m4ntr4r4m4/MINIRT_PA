/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:18:11 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:25:48 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	substract(t_vector v1, t_vector v2)
{
	return ((t_vector){.x = v1.x - v2.x, .y = v1.y - v2.y, .z = v1.z - v2.z});
}

t_vector	multiply(t_vector v1, long double s)
{
	return ((t_vector){.x = v1.x * s, .y = v1.y * s, .z = v1.z * s});
}

t_vector	add(t_vector v1, t_vector v2)
{
	return ((t_vector){.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z});
}

t_vector	vector(long double x, long double y, long double z)
{
	return ((t_vector){.x = x, .y = y, .z = z});
}
