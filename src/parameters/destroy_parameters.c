/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_parameters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:16:16 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:16:18 by priezu-m         ###   ########.fr       */
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
