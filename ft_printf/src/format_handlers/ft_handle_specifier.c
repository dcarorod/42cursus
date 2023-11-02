/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_specifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:23:55 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/01 11:25:21 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_handle_specifier(const char f, va_list args)
{
	if (ft_isformatspecifier(f))
	{
		if (f == 'c')
			return (ft_handle_char(args));
		else if (f == 's')
			return (ft_handle_str(args));
		else if (f == 'd' || f == 'i')
			return (ft_handle_int(va_arg(args, int)));
		else if (f == 'u')
			return (ft_handle_uint(va_arg(args, unsigned int)));
		else if (f == 'p')
			return (ft_handle_ptr(args));
		else if (f == 'x')
			return (ft_handle_hex(args, 0));
		else if (f == 'X')
			return (ft_handle_hex(args, 1));
		else if (f == '%')
			return (ft_handle_percent());
	}
	return (0);
}
