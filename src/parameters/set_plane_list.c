/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: set_plane_list.c                                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/21 08:06:20                                            */
/*   Updated:  2023/11/10 18:58:35                                            */
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
			"by a space from the next descriptor.\n");
		return (false);
	}
	return (true);
}

static t_plane	parse_plane(t_line *line, bool *parsing_error,
								size_t lineno)
{
	t_plane	plane;
	int		i;

	i = 0;
	while (ft_isspace(line->line[i]) != false)
		i++;
	while (ft_isalpha(line->line[i]) != false)
		i++;
	while (ft_isspace(line->line[i]) != false)
		i++;
	plane.position = parse_coordinates(line, &i, parsing_error, lineno);
	if (*parsing_error == true || !check_space(line, i, parsing_error, lineno))
		return (plane);
	while (ft_isspace(line->line[i]) != false)
		i++;
	plane.normal
		= parse_orientation_vector(line, &i, parsing_error, lineno);
	if (*parsing_error == true || !check_space(line, i, parsing_error, lineno))
		return (plane);
	while (ft_isspace(line->line[i]) != false)
		i++;
	plane.color = parse_color(line, &i, parsing_error, lineno);
	return (plane);
}

static void	set_plane_list_internal(t_parameters *parameters, int fileno)
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
		if (first_char_of_line(&line) == 'p')
		{
			parameters->plane_list.planes[j++]
				= parse_plane(&line, &parsing_error, i);
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

void	set_plane_list(char *filename, t_element_count element_count,
				t_parameters *parameters)
{
	const int		fileno = open(filename, O_RDONLY);

	parameters->plane_list.size = element_count.plane_count;
	if ((parameters->parameters_valid == false)
		|| (element_count.plane_count == 0))
	{
		parameters->plane_list.planes = NULL;
		return ;
	}
	if (fileno == -1)
	{
		perror("Error\nCould not open input file");
		parameters->parameters_valid = false;
		return ;
	}
	parameters->plane_list.planes
		= malloc((size_t)element_count.plane_count * sizeof(t_plane));
	if (parameters->plane_list.planes == NULL)
	{
		perror("Error\nCould not reserve enough memory");
		parameters->parameters_valid = false;
		return ;
	}
	set_plane_list_internal(parameters, fileno);
	close(fileno);
}

#pragma clang diagnostic pop
