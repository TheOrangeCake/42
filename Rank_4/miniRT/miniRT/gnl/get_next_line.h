/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:42:57 by maw               #+#    #+#             */
/*   Updated: 2025/06/14 18:50:16 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/libft.h"

size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);

char	*ft_strdup(const char *source);
char	*ft_strjoin(const char *s1, const char *s2);
//char	*ft_strchr(const char *str, char c);
char	*ft_substr(const char *str, unsigned int start, size_t len);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 124
# endif
#endif
