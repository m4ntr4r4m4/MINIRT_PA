/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_parameters_internal.c                                      */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/13 18:37:45                                            */
/*   Updated:  2024/01/14 11:56:08                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

t_parameters	get_parameters_internal(char *filename,
					t_element_count element_count)
{
	t_parameters	parameters;

	parameters = (t_parameters){.parameters_valid = true};
	set_ambient_lighting(filename, element_count, &parameters);
	set_camera(filename, &parameters);
	set_light(filename, element_count, &parameters);
	set_sphere_list(filename, element_count, &parameters);
	set_plane_list(filename, element_count, &parameters);
	set_cylinder_list(filename, element_count, &parameters);
	return (parameters);
}
