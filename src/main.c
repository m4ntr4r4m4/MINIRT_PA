/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:17:20 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:17:34 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameters/parameters.h"
#include "render_scene/render_scene.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_parameters	parameters;

	if (argc != 2)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	parameters = get_parameters(argv[1]);
	if (parameters.parameters_valid == false)
	{
		destroy_parameters(parameters);
		return (EXIT_FAILURE);
	}
	render_scene(parameters);
	return (EXIT_SUCCESS);
}
