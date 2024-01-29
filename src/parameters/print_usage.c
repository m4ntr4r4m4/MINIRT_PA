/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:15:46 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:15:48 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include <unistd.h>

void	print_usage(void)
{
	const char	msg[]
		= "Usage: ./minirt SCENE_FILE\n"
		"Render scene described in SCENE_FILE and show it in screen\n"
		"for more information on how a SCENE_FILE should look, see\n"
		"man minirt(1)\n";

	write(STDOUT_FILENO, msg, sizeof(msg));
}
