/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_isdigit.c                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/17 00:06:16                                            */
/*   Updated:  2024/01/14 11:53:48                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
