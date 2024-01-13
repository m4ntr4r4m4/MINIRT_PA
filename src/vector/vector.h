/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: vector.h                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/03 23:44:35                                            */
/*   Updated:  2023/11/10 18:43:15                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdbool.h>

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef struct s_vector
{
	long double	x;
	long double	y;
	long double	z;
}t_vector;

bool		is_normal(t_vector vector);
t_vector	normalize(t_vector v1);
t_vector	cross_product(t_vector v1, t_vector v2);
t_vector	multiply(t_vector v1, long double s);
t_vector	substract(t_vector v1, t_vector v2);
t_vector	add(t_vector v1, t_vector v2);
long double	get_magnitude(t_vector v1);
long double	dot_product(t_vector v1, t_vector v2);

# pragma clang diagnostic pop

#endif
