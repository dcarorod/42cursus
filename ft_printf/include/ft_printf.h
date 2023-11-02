/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:20:19 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/01 11:24:22 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_handle_specifier(const char f, va_list args);
int	ft_handle_char(va_list args);
int	ft_handle_str(va_list args);
int	ft_handle_int(int n);
int	ft_handle_uint(unsigned int n);
int	ft_handle_hex(va_list args, int is_upper);
int	ft_handle_ptr(va_list args);
int	ft_handle_percent(void);
int	ft_putchar(int c);
int	ft_putstr(const char *str);
int	ft_strlen(char *str);
int	ft_isformatspecifier(const char f);

#endif
