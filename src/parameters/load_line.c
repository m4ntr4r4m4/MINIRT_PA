/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: load_line.c                                                    */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 19:54:14                                            */
/*   Updated:  2023/10/21 11:40:39                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

char	first_char_of_line(t_line *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line->line[i]) != false && line->line[i] != '\n')
		i++;
	return (line->line[i]);
}

void	load_line_initial(t_line *line, t_buffer *buf, int fileno)
{
	*line = (t_line){0};
	*buf = (t_buffer){0};
	load_line(line, buf, fileno);
}

static char	get_char_from_buf(t_buffer *buf, int fileno)
{
	if (buf->index == buf->size)
		buf->size = (int)read(fileno, buf->buf, BUFSIZE);
	if (buf->size == -1)
	{
		buf->io_error = true;
		return ('\0');
	}
	if (buf->size == 0)
		return ('\0');
	buf->index++;
	return (buf->buf[buf->index - 1]);
}

void	load_line(t_line *line, t_buffer *buf, int fileno)
{
	int	i;

	i = 0;
	line->line[i] = get_char_from_buf(buf, fileno);
	while ((line->line[i] != '\n') && (line->line[i] != '\0'))
	{
		i++;
		if (i == MAX_LINE_SIZE)
		{
			line->size = i;
			return ;
		}
		line->line[i] = get_char_from_buf(buf, fileno);
	}
	if (line->line[i] == '\n')
		i++;
	if (buf->io_error == true)
	{
		line->io_error = true;
		i = 1;
	}
	line->size = i;
}

#pragma clang diagnostic pop
