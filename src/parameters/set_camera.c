/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: set_camera.c                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/19 21:29:44                                            */
/*   Updated:  2023/11/10 18:57:47                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

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

static void	field_of_view_check(t_camera camera, char c, bool *parsing_error,
				size_t lineno)
{
	if (*parsing_error == true)
		return ;
	if ((!!ft_isspace(c) == false && c != '\0')
		|| (camera.field_of_view < 0 || camera.field_of_view > 180))
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " field of view floating point value"
			" does not match regex (-?[0-9]{0,19}(\\.[0-9]{1,18})?),\n"
			"or is not in the range of 0 to 180, or does not end in a newline"
			" or space.\n");
	}
}

static t_camera	parse_camera(t_line *line, bool *parsing_error, size_t lineno)
{
	t_camera	camera;
	int			i;

	i = 0;
	while (ft_isspace(line->line[i]) != false)
		i++;
	while (ft_isalpha(line->line[i]) != false)
		i++;
	while (ft_isspace(line->line[i]) != false)
		i++;
	camera.position
		= parse_coordinates(line, &i, parsing_error, lineno);
	if (*parsing_error == true || !check_space(line, i, parsing_error, lineno))
		return (camera);
	while (ft_isspace(line->line[i]) != false)
		i++;
	camera.orientation
		= parse_orientation_vector(line, &i, parsing_error, lineno);
	if (*parsing_error == true || !check_space(line, i, parsing_error, lineno))
		return (camera);
	while (ft_isspace(line->line[i]) != false)
		i++;
	camera.field_of_view = parse_float(line, &i, parsing_error, lineno);
	field_of_view_check(camera, line->line[i], parsing_error, lineno);
	return (camera);
}

static void	set_camera_internal(t_parameters *parameters, int fileno)
{
	t_buffer	buf;
	t_line		line;
	size_t		i;
	bool		parsing_error;

	parsing_error = false;
	i = 1;
	load_line_initial(&line, &buf, fileno);
	while (line.size > 0 && first_char_of_line(&line) != 'C')
	{
		load_line(&line, &buf, fileno);
		i++;
	}
	parameters->camera = parse_camera(&line, &parsing_error, i);
	if (parsing_error == true)
		parameters->parameters_valid = false;
}

void	set_camera(char *filename, t_parameters *parameters)
{
	const int		fileno = open(filename, O_RDONLY);

	if (parameters->parameters_valid == false)
		return ;
	if (fileno == -1)
	{
		perror("Error\nCould not open input file");
		parameters->parameters_valid = false;
		return ;
	}
	set_camera_internal(parameters, fileno);
	close(fileno);
}

#pragma clang diagnostic pop
