/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: add_to_count_helper.c                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 20:42:38                                            */
/*   Updated:  2023/10/21 08:03:21                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <unistd.h>
#include <limits.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static void	check_camera(t_line *line,
				t_element_count *element_count, size_t i, size_t lineno)
{
	if (line->line[i] == 'C')
	{
		element_count->camera_count++;
		if (element_count->camera_count == 2)
		{
			ft_putstr_fileno(STDERR_FILENO, "Error\nLine ");
			ft_putnbr_fileno(STDERR_FILENO, lineno);
			ft_putstr_fileno(STDERR_FILENO,
				" redefinition of the camera element\n");
			element_count->count_failed = true;
		}
	}
}

static void	check_ambient_light(t_line *line,
				t_element_count *element_count, size_t i, size_t lineno)
{
	if (line->line[i] == 'A')
	{
		element_count->ambient_lighting_count++;
		if (element_count->ambient_lighting_count == 2)
		{
			ft_putstr_fileno(STDERR_FILENO, "Error\nLine ");
			ft_putnbr_fileno(STDERR_FILENO, lineno);
			ft_putstr_fileno(STDERR_FILENO,
				" redefinition of the ambient lighting element\n");
			element_count->count_failed = true;
		}
	}
}

static void	check_light(t_line *line,
				t_element_count *element_count, size_t i, size_t lineno)
{
	if (line->line[i] == 'L')
	{
		element_count->light_count++;
		if (element_count->light_count == 2)
		{
			ft_putstr_fileno(STDERR_FILENO, "Error\nLine ");
			ft_putnbr_fileno(STDERR_FILENO, lineno);
			ft_putstr_fileno(STDERR_FILENO,
				" redefinition of the light element\n");
			element_count->count_failed = true;
		}
	}
}

static void	check_sphere_and_cylinders(t_line *line,
				t_element_count *element_count, size_t i, size_t lineno)
{
	if (line->line[i] == 's')
	{
		if (element_count->sphere_count == INT_MAX)
		{
			ft_putstr_fileno(STDERR_FILENO, "Error\nLine ");
			ft_putnbr_fileno(STDERR_FILENO, lineno);
			ft_putstr_fileno(STDERR_FILENO,
				" too many sphere elements\n");
			element_count->count_failed = true;
		}
		element_count->sphere_count++;
	}
	else if (line->line[i] == 'c')
	{
		if (element_count->cylinder_count == INT_MAX)
		{
			ft_putstr_fileno(STDERR_FILENO, "Error\nLine ");
			ft_putnbr_fileno(STDERR_FILENO, lineno);
			ft_putstr_fileno(STDERR_FILENO,
				" too many cylinder elements\n");
			element_count->count_failed = true;
		}
		element_count->cylinder_count++;
	}
}

void	add_to_count_helper(t_line *line,
			t_element_count *element_count, size_t lineno)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line->line[i]) == true)
		i++;
	check_ambient_light(line, element_count, i, lineno);
	check_camera(line, element_count, i, lineno);
	check_light(line, element_count, i, lineno);
	check_sphere_and_cylinders(line, element_count, i, lineno);
	if (line->line[i] == 'p')
	{
		if (element_count->plane_count == INT_MAX)
		{
			ft_putstr_fileno(STDERR_FILENO, "Error\nLine ");
			ft_putnbr_fileno(STDERR_FILENO, lineno);
			ft_putstr_fileno(STDERR_FILENO, " too many plane elements\n");
			element_count->count_failed = true;
		}
		element_count->plane_count++;
	}
}

#pragma clang diagnostic pop
