/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:38:34 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/23 18:05:47 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_pwd(void)
{
	char	dir[1024];
	char	*str;

	str = getcwd(dir, sizeof(dir) - 1);
	if (!str)
	{
		perror("Error getting pwd");
		return (1);
	}
	printf("%s\n", dir);
	return (0);
}
