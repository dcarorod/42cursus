/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:21:03 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:21:07 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

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
