/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:03:27 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/31 18:19:35 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

char	*case_hexupper(int i, size_t *count);
char	*case_hexlower(int i, size_t *count);
char	*case_address(long i, size_t *count);
void	case_unsigned(unsigned int n, int fd, size_t *count);
int		ft_printf(const char *format, ...);

#endif
