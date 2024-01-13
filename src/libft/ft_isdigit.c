/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_isdigit.c                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/17 00:06:16                                            */
/*   Updated:  2023/10/17 00:07:16                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

#pragma clang diagnostic pop
