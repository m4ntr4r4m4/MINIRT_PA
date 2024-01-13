/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: libft.h                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/04 01:13:48                                            */
/*   Updated:  2023/10/17 00:06:07                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

void	ft_putstr(const char *str);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isalpha(char c);
int		ft_isspace(char c);
int		ft_isdigit(char c);
void	ft_putstr_fileno(int fileno, const char *str);
void	ft_putnbr_fileno(int fileno, uintmax_t nbr);

# pragma clang diagnostic pop

#endif
