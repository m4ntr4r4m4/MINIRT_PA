/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parameters_internal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:15:18 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:15:20 by priezu-m         ###   ########.fr       */
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
