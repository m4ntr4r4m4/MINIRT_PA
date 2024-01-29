/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fileno.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:12:33 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:12:34 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

static uintmax_t	get_magnitude(uintmax_t n)
{
	uintmax_t	magnitude;

	if (n == 0)
		return (1);
	magnitude = 0;
	while (n != 0)
	{
		if (magnitude == 0)
			magnitude = 1;
		else
			magnitude *= 10;
		n /= 10;
	}
	return (magnitude);
}

void	ft_putnbr_fileno(int fileno, uintmax_t nbr)
{
	uintmax_t	n;
	int			i;
	uintmax_t	magnitude;
	char		str[20];

	n = nbr;
	i = 0;
	magnitude = get_magnitude(n);
	while (magnitude > 0)
	{
		str[i] = ((char)((n / magnitude) % 10)) + '0';
		magnitude /= 10;
		i++;
	}
	write(fileno, str, (size_t)i);
}
