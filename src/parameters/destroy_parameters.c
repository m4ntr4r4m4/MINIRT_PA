/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: destroy_parameters.c                                           */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/21 09:23:05                                            */
/*   Updated:  2023/11/14 23:46:11                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include <stdlib.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

void	destroy_parameters(t_parameters parameters)
{
	free(parameters.cylinder_list.cylinders);
	free(parameters.plane_list.planes);
	free(parameters.sphere_list.spheres);
}

#pragma clang diagnostic pop
