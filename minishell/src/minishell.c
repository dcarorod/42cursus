/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:34:28 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/03 11:06:09 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_only_redir(t_ast *root)
{
	if (root->cmd && !root->left)
	{
		if (root->cmd->args[0] == NULL && root->redir)
			return (0);
	}
	return (1);
}

void	init_struct_glob(t_global *glob)
{
	glob->absolute_path = NULL;
	glob->env_arr = NULL;
	glob->env_head = NULL;
	glob->lex_head = NULL;
	glob->hashmap = NULL;
	glob->exit_status = 0;
}

int	launch_exec(t_ast *ast, t_global *glob)
{
	int	heredoc;
	int	value;

	heredoc = 0;
	value = 0;
	heredoc = check_num_heredoc(ast);
	if (check_only_redir(ast) == 0)
	{
		if (heredoc)
			return (handle_heredocuments(ast));
		if (exec_redir(ast->redir) == 1)
			value = 1;
		reset_all_fds(ast);
		if (value == 0)
			hashmap_insert(glob->hashmap, "?", "0", QMARK);
		else
			hashmap_insert(glob->hashmap, "?", "1", QMARK);
		return (0);
	}
	else
		return (start_exec(ast, glob, heredoc));
}

int	process_input(t_global *glob, char *input, t_ast *ast)
{
	char	*trimmed;

	trimmed = preprocess_input(input, glob);
	if (!trimmed)
		return (1);
	add_history(trimmed);
	glob->lex_head = ms_lexer(trimmed, glob);
	if (glob->lex_head)
	{
		ast = parse_tokens(glob->lex_head);
		if (ast)
		{
			if (launch_exec(ast, glob))
				return (1);
			close_all_fds(ast);
			free_ast(ast);
		}
		else
			update_exit_status(glob, 2);
		free_lexer_state(glob->lex_head);
	}
	else
		update_exit_status(glob, 2);
	free(trimmed);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_ast		ast_root;
	t_global	glob;

	if (argc != 1 && !argv[0])
		return (write (2, "Wrong number of arguments\n", 26));
	init_struct_glob(&glob);
	create_env_list(&glob, envp);
	setup_signals();
	while (TRUE)
	{
		input = readline("miniHELL> ");
		handle_ctrl_d(input);
		if (g_signal_status == SIGINT)
			update_exit_set_sigstatus(&glob, 130, 0);
		process_input(&glob, input, &ast_root);
		if (g_signal_status == 1)
			update_exit_set_sigstatus(&glob, 130, 0);
		if (access("/tmp/heredoctmp", F_OK) == 0)
			unlink("/tmp/heredoctmp");
		rl_on_new_line();
		free(input);
	}
	return (0);
}
