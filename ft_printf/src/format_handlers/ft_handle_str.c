/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:24:09 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/31 14:24:20 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_handle_str(va_list args)
{
	char	*str;
	char	*s;

	s = "(null)";
	str = va_arg(args, char *);
	if (!str)
		return (ft_putstr(s));
	return (ft_putstr(str));
}
