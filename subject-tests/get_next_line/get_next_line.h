/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:44:55 by phakakos          #+#    #+#             */
/*   Updated: 2019/11/12 13:33:31 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 100000000
# define FD_LIMIT 4865

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(const int ft, char **line);
char	*ft_strnew(size_t len);
char	*ft_strncat(char *s1, const char *s2, size_t n);
char	*ft_strcreate(char const *s, size_t len);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);

#endif
