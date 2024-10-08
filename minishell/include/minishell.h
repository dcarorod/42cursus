/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:28:31 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/03 11:30:56 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "lexer.h"
# include "ast.h"
# include "ms_signals.h"
# include "ms_hashmap.h"

# define ERROR_HEREDOC "miniHELL: warning: here-document at one line delimited \
by end-of-file (wanted `"

/*to know from which function comes the realloc function*/
typedef enum e_function
{
	EXP,
	UNSET
}	t_function;

typedef struct s_index_exit
{
	int	i;
	int	flag;
}	t_index_exit;

/* Utils */
void	*ms_print_message(const char *message, t_print_type print_type);
int		ms_log_val(t_print_type print_type, const char *str, int value);
void	*pfree_ast(t_ast *ast, const char *message, t_print_type print_type);
void	*update_exit_status(t_global *glob, int exit_status);
void	*free_ptr_update_exit(void *ptr_to_free,
			t_global *glob, int exit_status);
int		bool_update_status(t_global *glob, int exit_status, int return_value);
void	update_exit_set_sigstatus(t_global *glob,
			int exit_status, int signal_status);
void	print_error_cmd(char *cmd);
void	*str_realloc(void *ptr, size_t old_size, size_t new_size);
void	get_heredoc_line(char *heredoc, int fd, t_redir *dir);

/*Exec*/
int		start_exec(t_ast *root, t_global *glob, int heredoc);
char	*handle_type_cmd(t_ast *root, t_global *glob);
int		exec_cmd(t_ast *root, t_command *cmd, t_global *glob);
int		exec_builtin(t_ast *root, char **args, t_global *glob);
char	**ft_split_path(char const *s, char c);
int		is_child_builtin(t_ast *root);
int		exec_redir(t_redir *dir);
int		handle_append(t_redir *dir);
int		handle_redir_out(t_redir *dir);
int		handle_redir_in(t_redir *dir);
int		reset_all_fds(t_ast *root);
void	close_all_fds(t_ast *root);
void	redir_with_heredoc(t_redir *dir);
int		handle_heredocuments(t_ast *root);
int		check_num_heredoc(t_ast *root);

/* Builtin export */
int		ms_export(char **args, t_hashmap *map, t_ast *root);
int		parse_export_args(char *arg);
int		export_error_message(char *arg);
int		sort_export(t_hashmap *map);

/*Builtin utils*/
void	copy_actual_env(char **env, char **n_env);
int		handle_exp_change(char **n_env, char *arg, int len);
char	**get_good_args(char **args);

/*Builtin cd*/
int		ms_cd(char **arg, t_global *glob);
int		ft_change_dir(char *arg, char *oldpwd, t_global *glob);
int		handle_simple_cd(t_hashmap *map, t_global *glob);
int		cd_error(char *arg, int flag);
int		new_oldpwd(t_global *glob, char *opwd, char *dir);

/*Builtin echo*/
int		handle_newline(char *arg);
int		ms_echo(char **args, t_global *glob);
void	print_line(char **args, int flag);

/*Builtin env*/
int		ms_env(char **env);

/*Builtin exit*/
int		ms_exit(char **args, t_global *glob, t_ast *root);
int		rest_of_exit(char **arg, t_global *glob, t_ast *root, int flag);
void	handle_non_numeric_args(char *arg, t_global *glob,
			t_ast *root, int flag);

/*Builtin pwd*/
int		ms_pwd(void);

/*Builtin unset*/
int		ms_unset(char **args, t_hashmap *map, t_global *glob);
char	**resize_env_array(t_hashmap *map, t_global *glob,
			char **args, t_function type);
size_t	get_array_size(t_hashmap *map);

/*Env utils*/
char	*extract_name(char *env, char *key);
int		handle_cd_change(t_global *glob, char **args);
char	**add_to_array(char **env, char *str, int len);
int		search_to_add(t_global *glob, char *dir, int len);
int		should_unset(char **args, char *env_var);

/*Creation de l env*/
void	init_struct_glob(t_global *glob);
int		create_env_list(t_global *global, char **envp);
char	**get_envp_array(char **envp);
char	*each_envp_line(char *env_line, int name);

#endif
