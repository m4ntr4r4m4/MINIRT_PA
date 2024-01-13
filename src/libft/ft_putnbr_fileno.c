/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_putnbr_fileno.c                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 20:59:04                                            */
/*   Updated:  2023/10/13 18:08:27                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

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

#pragma clang diagnostic pop
