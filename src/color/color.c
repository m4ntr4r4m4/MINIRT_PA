/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: color.c                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/11/12 18:36:52                                            */
/*   Updated:  2023/11/14 18:20:50                                            */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

t_color	color_add(t_color c1, t_color c2)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = c1.r + c2.r;
	g = c1.g + c2.g;
	b = c1.b + c2.b;
	if (r > 255)
		r = 255;
	if (b > 255)
		b = 255;
	if (g > 255)
		g = 255;
	return ((t_color){.r = (unsigned char)r, .g = (unsigned char)g,
		.b = (unsigned char)b});
}

t_color	color_absorb(t_color c1, t_color c2)
{
	long double	r;
	long double	g;
	long double	b;

	r = ((long double)c1.r / 255.L) * ((long double)c2.r / 255.L);
	r *= 255;
	g = ((long double)c1.g / 255.L) * ((long double)c2.g / 255.L);
	g *= 255;
	b = ((long double)c1.b / 255.L) * ((long double)c2.b / 255.L);
	b *= 255;
	return ((t_color){.r = (unsigned char)r, .g = (unsigned char)g,
		.b = (unsigned char)b});
}

t_color	color_multiply(t_color c1, long double s)
{
	long double	r;
	long double	g;
	long double	b;

	if (s <= 0)
		s = 0;
	r = ((long double)c1.r / 255.L) * s;
	r *= 255;
	g = ((long double)c1.g / 255.L) * s;
	g *= 255;
	b = ((long double)c1.b / 255.L) * s;
	b *= 255;
	return ((t_color){.r = (unsigned char)r, .g = (unsigned char)g,
		.b = (unsigned char)b});
}

#pragma clang diagnostic pop
