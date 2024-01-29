/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:17:59 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:18:01 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdbool.h>
#include <math.h>

bool	is_normal(t_vector v)
{
	const long double	magnitude = get_magnitude(v);

	if ((magnitude < 1.l - 1e-16l)
		|| (magnitude > 1.l + 1e-16l))
		return (false);
	return (true);
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x});
}

long double	get_magnitude(t_vector v1)
{
	return (sqrtl(powl(v1.x, 2) + powl(v1.y, 2) + powl(v1.z, 2)));
}

t_vector	normalize(t_vector v1)
{
	const long double	lenght = get_magnitude(v1);

	if (lenght < 1.E-14L && lenght > -1.E-14L)
		return ((t_vector){0});
	v1.x /= lenght;
	v1.y /= lenght;
	v1.z /= lenght;
	return (v1);
}

long double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
