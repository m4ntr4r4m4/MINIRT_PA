/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_orientation_vector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:14:40 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:14:42 by priezu-m         ###   ########.fr       */
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
		ft_putstr_fileno(STDERR_FILENO, " vector is not three"
			" floating point values separated by comas\n");
		return (false);
	}
	return (true);
}

static void	check_normal(t_vector orientation, bool *parsing_error,
				size_t lineno)
{
	if ((orientation.x < -1 || orientation.x > 1)
		|| (orientation.y < -1 || orientation.y > 1)
		|| (orientation.z < -1 || orientation.z > 1)
		|| is_normal(orientation) == false)
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " vector is not a normalized"
			" vector composed three floating point values in the range from"
			" -1 to 1\n");
	}
}

t_vector	parse_orientation_vector(t_line *line, int *i, bool *parsing_error,
				size_t lineno)
{
	t_vector	orientation;

	orientation.x = parse_float(line, i, parsing_error, lineno);
	if ((*parsing_error == true)
		|| (check_comma(line, i, parsing_error, lineno) == false))
		return (orientation);
	(*i)++;
	orientation.y = parse_float(line, i, parsing_error, lineno);
	if ((*parsing_error == true)
		|| (check_comma(line, i, parsing_error, lineno) == false))
		return (orientation);
	(*i)++;
	orientation.z = parse_float(line, i, parsing_error, lineno);
	check_normal(orientation, parsing_error, lineno);
	return (orientation);
}
