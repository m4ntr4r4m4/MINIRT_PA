/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:13:39 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:13:41 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>

;
void	ft_putstr(const char *str);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isalpha(char c);
int		ft_isspace(char c);
int		ft_isdigit(char c);
void	ft_putstr_fileno(int fileno, const char *str);
void	ft_putnbr_fileno(int fileno, uintmax_t nbr);

#endif
