/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:21:47 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:21:52 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

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
