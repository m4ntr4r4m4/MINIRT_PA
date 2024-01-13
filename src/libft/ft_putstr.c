/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_putstr.c                                                    */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 20:54:18                                            */
/*   Updated:  2023/10/07 20:55:35                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

void	ft_putstr(const char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
}

#pragma clang diagnostic pop
