/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:01:14 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/08/04 02:30:32 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

static void	resize_tokens_array(t_lexer *lexer, int new_capacity)
{
	int		i;
	t_token	**new_tokens;

	new_tokens = malloc(sizeof(t_token *) * new_capacity);
	if (!new_tokens)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < lexer->count)
	{
		new_tokens[i] = lexer->tokens[i];
		i++;
	}
	free(lexer->tokens);
	lexer->tokens = new_tokens;
	lexer->capacity = new_capacity;
}

/* Add a token to the lexer state */
void	add_token(t_lexer *lexer, t_token *token)
{
	int		new_capacity;

	if (lexer->count >= lexer->capacity)
	{
		if (lexer->capacity == 0)
			new_capacity = 8;
		else
			new_capacity = lexer->capacity * 2;
		resize_tokens_array(lexer, new_capacity);
	}
	lexer->tokens[lexer->count++] = token;
}

/* Frees the memory allocated for tokens in the lexer state */
void	free_tokens(t_lexer *lexer)
{
	int	i;

	if (lexer)
	{
		i = 0;
		while (i < lexer->count)
		{
			free(lexer->tokens[i]->value);
			free(lexer->tokens[i]);
			i++;
		}
		free(lexer->tokens);
		lexer->tokens = NULL;
	}
}

void	print_tokens(t_lexer *lexer)
{
	int		i;
	t_token	*token;

	if (!lexer || !lexer->tokens)
	{
		printf("No tokens to print\n");
		return ;
	}
	i = 0;
	while (i < lexer->count)
	{
		token = lexer->tokens[i];
		printf("Token %d: Type = %d, Value = %s\n",
			i, token->type, token->value);
		i++;
	}
}
