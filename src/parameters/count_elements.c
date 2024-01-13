/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: count_elements.c                                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 19:49:21                                            */
/*   Updated:  2023/10/20 06:26:50                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parameters.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static void	add_to_count(t_element_count *element_count, t_line *line,
				size_t lineno)
{
	const char	*valid_element_ids[] = {"C", "A", "L", "sp", "cy", "pl", NULL};

	if (line->size == MAX_LINE_SIZE)
	{
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " too big to parse.\n");
		element_count->count_failed = true;
		return ;
	}
	if (line->io_error == true)
	{
		element_count->count_failed = true;
		perror("Error\nCould not read from input file");
		return ;
	}
	if (is_valid_id(valid_element_ids, line) == false)
	{
		ft_putstr_fileno(STDERR_FILENO, "Error\nLine ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " no valid element id given.\n");
		element_count->count_failed = true;
		return ;
	}
	add_to_count_helper(line, element_count, lineno);
}

static void	read_file(t_line *line, t_buffer *buf,
				t_element_count *element_count, int fileno)
{
	size_t	i;

	i = 0;
	load_line(line, buf, fileno);
	while (line->size > 0)
	{
		if (line->line[0] != '\n')
			add_to_count(element_count, line, i + 1);
		if (element_count->count_failed)
			return ;
		load_line(line, buf, fileno);
		i++;
	}
	if (element_count->camera_count != 1)
	{
		ft_putstr_fileno(STDERR_FILENO,
			"Error\nThe camera element was not defined\n");
		element_count->count_failed = true;
	}
}

t_element_count	count_elements(char *filename)
{
	const int		fileno = open(filename, O_RDONLY);
	t_element_count	element_count;
	t_buffer		buf;
	t_line			line;

	if (fileno == -1)
	{
		perror("Error\nCould not open input file");
		return ((t_element_count){.count_failed = true});
	}
	element_count = (t_element_count){.count_failed = false};
	line = (t_line){0};
	buf = (t_buffer){0};
	read_file(&line, &buf, &element_count, fileno);
	close(fileno);
	return (element_count);
}

#pragma clang diagnostic pop
