/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:03:27 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/01 12:22:29 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

void	case_hexupper(unsigned int j, size_t *count);
void	case_hexlower(unsigned int j, size_t *count);
void	case_address(unsigned long j, size_t *count);
void	case_unsigned(unsigned int n, int fd, size_t *count);
int		ft_printf(const char *format, ...);

#endif
