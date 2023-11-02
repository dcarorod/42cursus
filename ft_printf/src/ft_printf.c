/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:21:29 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/31 14:21:43 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	size_t	i;
	int		char_count;
	va_list	args;

	va_start(args, format);
	i = 0;
	char_count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			format++;
			char_count += ft_handle_specifier(format[i], args);
			while (format[i] && !ft_isformatspecifier(format[i]))
				format++;
		}
		else
			char_count += ft_putchar(format[i]);
		format++;
	}
	va_end(args);
	return (char_count);
}
