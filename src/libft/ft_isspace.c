/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_isspace.c                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 21:14:04                                            */
/*   Updated:  2023/10/13 17:37:07                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

#pragma clang diagnostic pop
