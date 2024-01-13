/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parse_cylinder.c                                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/21 08:49:29                                            */
/*   Updated:  2023/11/10 18:56:24                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static bool	check_space(t_line *line, int i, bool *parsing_error,
				size_t lineno)
{
	if (!!ft_isspace(line->line[i]) == false)
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " floating point value does not match"
			" regex (-?[0-9]{0,19}(\\.[0-9]{1,18})?). Or is not separated\n"
			"by a space from the next descriptor.\n");
		return (false);
	}
	return (true);
}

static bool	check_for_space_float(char c, bool *parsing_error,
				size_t lineno, long double x)
{
	if (!!ft_isspace(c) == false || x < 0)
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " floating point value does not match"
			" regex (-?[0-9]{0,19}(\\.[0-9]{1,18})?). Or is not separated\n"
			"by a space from the next descriptor. Or is less than 0.\n");
		return (false);
	}
	return (true);
}

static bool	parse_cylinder_helper(t_line *line, int *i, size_t lineno,
				t_cylinder *cylinder)
{
	bool	parsing_error;

	parsing_error = false;
	cylinder->geometric_center
		= parse_coordinates(line, i, &parsing_error, lineno);
	if (parsing_error == true || !check_space(line, *i, &parsing_error, lineno))
		return (true);
	while (ft_isspace(line->line[*i]) != false)
		(*i)++;
	cylinder->direction
		= parse_orientation_vector(line, i, &parsing_error, lineno);
	if (parsing_error == true || !check_space(line, *i, &parsing_error, lineno))
		return (true);
	while (ft_isspace(line->line[*i]) != false)
		(*i)++;
	cylinder->diameter = parse_float(line, i, &parsing_error, lineno);
	if ((parsing_error == true)
		|| (check_for_space_float(line->line[*i], &parsing_error, lineno,
				cylinder->diameter) == false))
		return (true);
	while (ft_isspace(line->line[*i]) != false)
		(*i)++;
	return (false);
}

t_cylinder	parse_cylinder(t_line *line, bool *parsing_error,
								size_t lineno)
{
	t_cylinder	cylinder;
	int			i;

	i = 0;
	while (ft_isspace(line->line[i]) != false)
		i++;
	while (ft_isalpha(line->line[i]) != false)
		i++;
	while (ft_isspace(line->line[i]) != false)
		i++;
	*parsing_error = parse_cylinder_helper(line, &i, lineno, &cylinder);
	if (*parsing_error == true)
		return (cylinder);
	cylinder.height = parse_float(line, &i, parsing_error, lineno);
	if ((*parsing_error == true)
		|| (check_for_space_float(line->line[i], parsing_error, lineno,
				cylinder.height) == false))
		return (cylinder);
	while (ft_isspace(line->line[i]) != false)
		i++;
	cylinder.color = parse_color(line, &i, parsing_error, lineno);
	return (cylinder);
}

#pragma clang diagnostic pop
