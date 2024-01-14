/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: color.h                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/03 23:50:07                                            */
/*   Updated:  2024/01/14 11:52:14                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}t_color __attribute__((aligned(4)));

t_color	color_add(t_color c1, t_color c2);
t_color	color_absorb(t_color c1, t_color c2);
t_color	color_multiply(t_color c1, long double s);

#endif
