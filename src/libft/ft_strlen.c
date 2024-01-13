/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_strlen.c                                                    */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 20:57:55                                            */
/*   Updated:  2023/10/07 20:58:44                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

#pragma clang diagnostic pop
