/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: destroy_parameters.c                                           */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/21 09:23:05                                            */
/*   Updated:  2024/01/14 11:55:58                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include <stdlib.h>

void	destroy_parameters(t_parameters parameters)
{
	free(parameters.cylinder_list.cylinders);
	free(parameters.plane_list.planes);
	free(parameters.sphere_list.spheres);
}
