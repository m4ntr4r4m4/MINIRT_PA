/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:14:30 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:14:32 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

static bool	check_comma(t_line *line, int *i, bool *parsing_error,
				size_t lineno)
{
	if (line->line[*i] != ',')
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " coordinates are not three floating "
			"point values separated by comas\n");
		return (false);
	}
	return (true);
}

t_vector	parse_coordinates(t_line *line, int *i, bool *parsing_error,
					size_t lineno)
{
	t_vector	coordinates;

	coordinates.x = parse_float(line, i, parsing_error, lineno);
	if ((*parsing_error == true) || (check_comma(line, i, parsing_error, lineno)
			== false))
		return (coordinates);
	(*i)++;
	coordinates.y = parse_float(line, i, parsing_error, lineno);
	if ((*parsing_error == true) || (check_comma(line, i, parsing_error, lineno)
			== false))
		return (coordinates);
	(*i)++;
	coordinates.z = parse_float(line, i, parsing_error, lineno);
	return (coordinates);
}
