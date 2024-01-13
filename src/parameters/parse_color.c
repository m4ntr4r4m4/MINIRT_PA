/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parse_color.c                                                  */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/18 17:30:30                                            */
/*   Updated:  2023/10/20 08:31:10                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static unsigned char	get_color(t_line *line, int *i, bool *parsing_error)
{
	int	res;

	res = -1;
	if (ft_isdigit(line->line[*i]) != false)
	{
		res = 0;
		while (ft_isdigit(line->line[*i]) != false)
		{
			res *= 10;
			res += line->line[*i] - '0';
			if (res > 255)
				break ;
			(*i)++;
		}
	}
	if ((res == -1) || (res > 255))
	{
		*parsing_error = true;
		return (0);
	}
	return ((unsigned char)res);
}

static void	check_for_space(t_line *line, int *i, bool *parsing_error,
				size_t lineno)
{
	if (!!ft_isspace(line->line[*i]) == false && (line->line[*i]) != '\0')
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " color is not three integers in the"
			" range of 0 to 255 separated by comas endign in\n"
			"a space or newline\n");
	}
}

t_color	parse_color(t_line *line, int *i, bool *parsing_error, size_t lineno)
{
	t_color	color;

	color.r = get_color(line, i, parsing_error);
	if (line->line[(*i)++] != ',' || *parsing_error == true)
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " color is not three integers in the"
			" range of 0 to 255 separated by comas\n");
		return (color);
	}
	color.g = get_color(line, i, parsing_error);
	if (line->line[(*i)++] != ',' || *parsing_error == true)
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " color is not three integers in the"
			" range of 0 to 255 separated by comas\n");
		return (color);
	}
	color.b = get_color(line, i, parsing_error);
	check_for_space(line, i, parsing_error, lineno);
	return (color);
}

#pragma clang diagnostic pop
