/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_putstr_fileno.c                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 20:56:52                                            */
/*   Updated:  2024/01/14 11:54:07                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fileno(int fileno, const char *str)
{
	write(fileno, str, ft_strlen(str));
}
