/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:11:27 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:11:30 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

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
