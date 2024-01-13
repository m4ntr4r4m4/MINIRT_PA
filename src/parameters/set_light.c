/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: set_light.c                                                    */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/20 06:47:13                                            */
/*   Updated:  2023/11/10 18:58:08                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stdio.h>
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
			"by a space from the brightness descriptor.\n");
		return (false);
	}
	return (true);
}

static bool	check_for_space_float(char c, bool *parsing_error,
				size_t lineno, long double x)
{
	if (!!ft_isspace(c) == false || x < 0 || x > 1)
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " floating point value does not match"
			" regex (-?[0-9]{0,19}(\\.[0-9]{1,18})?). Or is not separated\n"
			"by a space from the color descriptor. Or is not in the range"
			" of 0 to 1.\n");
		return (false);
	}
	return (true);
}

static t_light	parse_light(t_line *line, bool *parsing_error,
								size_t lineno)
{
	t_light	light;
	int		i;

	i = 0;
	light.initialized = true;
	while (ft_isspace(line->line[i]) != false)
		i++;
	while (ft_isalpha(line->line[i]) != false)
		i++;
	while (ft_isspace(line->line[i]) != false)
		i++;
	light.position = parse_coordinates(line, &i, parsing_error, lineno);
	if (*parsing_error == true || !check_space(line, i, parsing_error, lineno))
		return (light);
	while (ft_isspace(line->line[i]) != false)
		i++;
	light.brightness = parse_float(line, &i, parsing_error, lineno);
	if ((*parsing_error == true)
		|| (check_for_space_float(line->line[i], parsing_error, lineno,
				light.brightness) == false))
		return (light);
	while (ft_isspace(line->line[i]) != false)
		i++;
	light.color = parse_color(line, &i, parsing_error, lineno);
	return (light);
}

static void	set_light_internal(t_parameters *parameters, int fileno)
{
	t_buffer	buf;
	t_line		line;
	size_t		i;
	bool		parsing_error;

	i = 1;
	parsing_error = false;
	load_line_initial(&line, &buf, fileno);
	while (line.size > 0 && first_char_of_line(&line) != 'L')
	{
		load_line(&line, &buf, fileno);
		i++;
	}
	parameters->light = parse_light(&line, &parsing_error, i);
	if (parsing_error == true)
		parameters->parameters_valid = false;
}

void	set_light(char *filename, t_element_count element_count,
				t_parameters *parameters)
{
	const int		fileno = open(filename, O_RDONLY);

	if (parameters->parameters_valid == false)
		return ;
	if (element_count.light_count == 0)
	{
		parameters->light.initialized = false;
		return ;
	}
	if (fileno == -1)
	{
		perror("Error\nCould not open input file");
		parameters->parameters_valid = false;
		return ;
	}
	set_light_internal(parameters, fileno);
	close(fileno);
}

#pragma clang diagnostic pop
