/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_isalpha.c                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/13 19:39:20                                            */
/*   Updated:  2023/10/13 19:41:17                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

int	ft_isalpha(char c)
{
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
		return (1);
	return (0);
}

#pragma clang diagnostic pop
