/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_putstr_fileno.c                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 20:56:52                                            */
/*   Updated:  2023/10/07 20:57:41                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

void	ft_putstr_fileno(int fileno, const char *str)
{
	write(fileno, str, ft_strlen(str));
}

#pragma clang diagnostic pop
