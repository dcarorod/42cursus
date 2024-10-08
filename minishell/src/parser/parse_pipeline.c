/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:01:18 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/27 13:47:56 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_pipeline(t_ast **cmd_node, t_lexer *lexer, int *index)
{
	if (!parse_command(*cmd_node, lexer, index))
	{
		free_ast(*cmd_node);
		return (FALSE);
	}
	return (TRUE);
}
