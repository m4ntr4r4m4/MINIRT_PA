/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parse_float.c                                                  */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/18 16:23:54                                            */
/*   Updated:  2023/10/20 06:17:51                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

_Static_assert(sizeof(unsigned long int) == 8,
	"Code is not portable to this system\n");

static unsigned long int	get_num(t_line *line, int *i,
								unsigned long int *magnitude)
{
	unsigned long int	res;

	res = 0;
	*magnitude = 1;
	while (ft_isdigit(line->line[*i]) != false)
	{
		res *= 10;
		*magnitude *= 10;
		res += (unsigned)line->line[*i] - '0';
		(*i)++;
	}
	return (res);
}

static long double	parse_float_internal(t_line *line, int *i)
{
	unsigned long int	integer_part;
	unsigned long int	decimal_part;
	unsigned long int	magnitude;

	integer_part = 0;
	decimal_part = 0;
	magnitude = 0;
	if (line->line[*i] != '.')
		integer_part = get_num(line, i, &magnitude);
	if (line->line[*i] == '.')
	{
		(*i)++;
		decimal_part = get_num(line, i, &magnitude);
	}
	return ((((long double)integer_part * (long double)magnitude)
			+ (long double)decimal_part) / (long double)magnitude);
}

static bool	check_regex_match(t_line *line, int i)
{
	int	count;

	count = 0;
	if (line->line[i] == '-')
		i++;
	while (ft_isdigit(line->line[i]) != false)
	{
		count++;
		i++;
	}
	if (count > 19)
		return (false);
	if (line->line[i++] == '.')
	{
		count = 0;
		while (ft_isdigit(line->line[i++]) != false)
			count++;
		if (count == 0 || count > 18)
			return (false);
	}
	if (count == 0)
		return (false);
	return (true);
}

long double	parse_float(t_line *line, int *i, bool *parsing_error,
				size_t lineno)
{
	if (check_regex_match(line, *i) == false)
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " floating point value does not match"
			" regex (-?[0-9]{0,19}(\\.[0-9]{1,18})?).\n");
		return (0);
	}
	if (line->line[*i] == '-')
	{
		(*i)++;
		return (-parse_float_internal(line, i));
	}
	return (parse_float_internal(line, i));
}

#pragma clang diagnostic pop
