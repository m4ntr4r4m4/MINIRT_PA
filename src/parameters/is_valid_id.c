/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:16:27 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:16:28 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stddef.h>

static bool	there_is_match(t_line *line, const char *id, int i)
{
	int	k;

	if ((size_t)(line->size - i) < ft_strlen(id))
		return (false);
	k = 0;
	while (id[k] != '\0')
	{
		if (line->line[i] != id[k])
		{
			if ((ft_isspace(line->line[i]) == true)
				&& (id[k] == '\0'))
				return (true);
			break ;
		}
		k++;
		i++;
	}
	if ((ft_isspace(line->line[i]) == true)
		&& (id[k] == '\0'))
		return (true);
	return (false);
}

bool	is_valid_id(const char **valid_element_ids, t_line *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line->line[i]) == true)
		i++;
	if (i == line->size)
		return (false);
	while (*valid_element_ids != NULL)
	{
		if (there_is_match(line, *valid_element_ids, i))
			return (true);
		valid_element_ids++;
	}
	return (false);
}
