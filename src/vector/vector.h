/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:17:48 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:25:28 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vector
{
	long double	x;
	long double	y;
	long double	z;
}	t_vector;

bool		is_normal(t_vector vector);
t_vector	normalize(t_vector v1);
t_vector	cross_product(t_vector v1, t_vector v2);
t_vector	multiply(t_vector v1, long double s);
t_vector	substract(t_vector v1, t_vector v2);
t_vector	add(t_vector v1, t_vector v2);
long double	get_magnitude(t_vector v1);
long double	dot_product(t_vector v1, t_vector v2);
t_vector	vector(long double x, long double y, long double z);

#endif
