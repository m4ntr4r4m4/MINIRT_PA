/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: set_sphere_list.c                                              */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/21 03:23:04                                            */
/*   Updated:  2023/11/14 16:33:07                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
			"by a space from the diameter descriptor.\n");
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
			"by a space from the color descriptor. Or is less than 0.\n");
		return (false);
	}
	return (true);
}

static t_sphere	parse_sphere(t_line *line, bool *parsing_error,
								size_t lineno)
{
	t_sphere	sphere;
	int			i;

	i = 0;
	while (ft_isspace(line->line[i]) != false)
		i++;
	while (ft_isalpha(line->line[i]) != false)
		i++;
	while (ft_isspace(line->line[i]) != false)
		i++;
	sphere.center = parse_coordinates(line, &i, parsing_error, lineno);
	if (*parsing_error == true || !check_space(line, i, parsing_error, lineno))
		return (sphere);
	while (ft_isspace(line->line[i]) != false)
		i++;
	sphere.diameter = parse_float(line, &i, parsing_error, lineno);
	if ((*parsing_error == true)
		|| (check_for_space_float(line->line[i], parsing_error, lineno,
				sphere.diameter) == false))
		return (sphere);
	while (ft_isspace(line->line[i]) != false)
		i++;
	sphere.color = parse_color(line, &i, parsing_error, lineno);
	return (sphere);
}

static void	set_sphere_list_internal(t_parameters *parameters, int fileno)
{
	t_buffer	buf;
	t_line		line;
	size_t		i;
	int			j;
	bool		parsing_error;

	i = 1;
	j = 0;
	parsing_error = false;
	load_line_initial(&line, &buf, fileno);
	while (line.size > 0)
	{
		if (first_char_of_line(&line) == 's')
		{
			parameters->sphere_list.spheres[j++]
				= parse_sphere(&line, &parsing_error, i);
			if (parsing_error == true)
			{
				parameters->parameters_valid = false;
				return ;
			}
		}
		load_line(&line, &buf, fileno);
		i++;
	}
}

void	set_sphere_list(char *filename, t_element_count element_count,
				t_parameters *parameters)
{
	const int		fileno = open(filename, O_RDONLY);

	parameters->sphere_list.size = element_count.sphere_count;
	if ((parameters->parameters_valid == false)
		|| (element_count.sphere_count == 0))
	{
		parameters->sphere_list.spheres = NULL;
		return ;
	}
	if (fileno == -1)
	{
		perror("Error\nCould not open input file");
		parameters->parameters_valid = false;
		return ;
	}
	parameters->sphere_list.spheres
		= malloc((size_t)element_count.sphere_count * sizeof(t_sphere));
	if (parameters->sphere_list.spheres == NULL)
	{
		perror("Error\nCould not reserve enough memory");
		parameters->parameters_valid = false;
		return ;
	}
	set_sphere_list_internal(parameters, fileno);
	close(fileno);
}

#pragma clang diagnostic pop
