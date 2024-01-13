/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: set_cylinder_list.c                                            */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/21 08:22:29                                            */
/*   Updated:  2023/11/14 23:45:44                                            */
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

static void	set_cylinder_list_internal(t_parameters *parameters, int fileno)
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
		if (first_char_of_line(&line) == 'c')
		{
			parameters->cylinder_list.cylinders[j++]
				= parse_cylinder(&line, &parsing_error, i);
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

void	set_cylinder_list(char *filename, t_element_count element_count,
				t_parameters *parameters)
{
	const int		fileno = open(filename, O_RDONLY);

	parameters->cylinder_list.size = element_count.cylinder_count;
	if ((parameters->parameters_valid == false)
		|| (element_count.cylinder_count == 0))
	{
		parameters->cylinder_list.cylinders = NULL;
		return ;
	}
	if (fileno == -1)
	{
		perror("Error\nCould not open input file");
		parameters->parameters_valid = false;
		return ;
	}
	parameters->cylinder_list.cylinders
		= malloc((size_t)element_count.cylinder_count * sizeof(t_cylinder));
	if (parameters->cylinder_list.cylinders == NULL)
	{
		perror("Error\nCould not reserve enough memory");
		parameters->parameters_valid = false;
		return ;
	}
	set_cylinder_list_internal(parameters, fileno);
	close(fileno);
}

#pragma clang diagnostic pop
