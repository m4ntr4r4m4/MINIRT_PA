/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: print_usage.c                                                  */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/06 18:09:42                                            */
/*   Updated:  2023/10/07 21:33:00                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

void	print_usage(void)
{
	const char	msg[]
		= "Usage: ./minirt SCENE_FILE\n"
		"Render scene described in SCENE_FILE and show it in screen\n"
		"for more information on how a SCENE_FILE should look, see\n"
		"man minirt(1)\n";

	write(STDOUT_FILENO, msg, sizeof(msg));
}

#pragma clang diagnostic pop
