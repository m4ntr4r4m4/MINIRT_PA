/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: vector_functions2.c                                            */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 07:57:40                                            */
/*   Updated:  2024/01/14 11:59:27                                            */
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
