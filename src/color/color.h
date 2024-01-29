/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:11:37 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:19:21 by priezu-m         ###   ########.fr       */
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
}	t_color __attribute__((aligned(4)));

t_color	color_add(t_color c1, t_color c2);
t_color	color_absorb(t_color c1, t_color c2);
t_color	color_multiply(t_color c1, long double s);

#endif
