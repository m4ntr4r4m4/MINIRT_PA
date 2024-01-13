/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_parameters.c                                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/06 18:23:36                                            */
/*   Updated:  2023/10/14 01:42:49                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parameters.h"
#include <stdbool.h>
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static bool	filename_extension_correct(char *filename)
{
	const size_t	len = ft_strlen(filename);
	const char		msg[]
		= "Error\ngiven file does not have a .rt extension\n";

	if (len < 4)
	{
		ft_putstr_fileno(STDERR_FILENO, msg);
		return (false);
	}
	if (ft_strcmp(&filename[len - 3], ".rt") != 0)
	{
		ft_putstr_fileno(STDERR_FILENO, msg);
		return (false);
	}
	return (true);
}

t_parameters	get_parameters(char *filename)
{
	t_parameters	parameters;
	t_element_count	element_count;

	parameters = (t_parameters){.parameters_valid = true};
	if (filename_extension_correct(filename) == false)
	{
		parameters.parameters_valid = false;
		return (parameters);
	}
	element_count = count_elements(filename);
	if (element_count.count_failed == true)
	{
		parameters.parameters_valid = false;
		return (parameters);
	}
	parameters = get_parameters_internal(filename, element_count);
	return (parameters);
}

#pragma clang diagnostic pop
