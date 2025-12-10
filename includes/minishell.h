/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:11:35 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/10 13:49:09 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
# include "../libft/libft.h"

/* Colors */
# define BLUE "\033[34m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

typedef enum e_tokentype
{
	T_INPUT = 1,		//  <
	T_HEREDOC,			//  <<
	T_TRUNC,			//  >
	T_APPEND,			//  >>
	T_PIPE,				//  |
	T_CMD,				//  command name
	T_ARG,				//  argument
}	t_tokentype;

typedef struct s_token
{
	char			*str;
	t_tokentype		type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;		//NULL terminated
	int				infile;		//fd or stdin
	int				outfile;	//fd or stdout
	bool			error;		//error flag
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char	**envp;		//pointer array, NULL terminated
	char	*pwd;		//current working directory
	char	*oldpwd;	//previous working directory
	char	*home;		//home directory
}	t_env;

typedef struct s_data
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		cmd_count;
	int		here_doc;
	char	*eof_str;
	int		last_exit_status;
	t_env	*env;
}	t_data;

typedef enum e_export_type
{
	EXPORT_INVALID,
	EXPORT_NO_VALUE,	//VAR
	EXPORT_SET,			//VAR=value
	EXPORT_APPEND,		//VAR+=value
}	t_export_type;

typedef struct s_export
{
	char			*key;
	char			*value;
	t_export_type	type;
}	t_export;

/* exec.c */
void	exec_cmd(t_data *data);
bool	is_builtin_in_parent(t_cmd *cmd);

/* exec_single_cmd.c */
void	exec_child(t_cmd *cmd, t_env *env, t_token *tokens);
void	exec_single_cmd(t_cmd *cmd, char **envp);
bool	is_builtin_child(t_cmd *cmd);

/* exec_pipeline.c */
int		count_pipes(t_token *tokens);
int		**init_pipes(int nbr_cmds);
void	exec_pipeline(t_cmd *cmd, t_env *env, t_token *tokens);

/* redirection.c */
int		open_input_file(t_cmd *cmd, const char *file);
int		open_output_trunc(t_cmd *cmd, const char *file);
int		open_output_append(t_cmd *cmd, const char *file);
int		put_error(t_cmd *cmd, const char *msg);
void	apply_redirections_to_cmd(t_cmd *cmd, t_token *tokens);

/* find_path.c */
char	**parse_envp(char **envp);
char	*get_full_path(char *dir, char *cmd);
char	*check_path(int n, char **paths, char *cmd);
bool	exists_n_executable(char *path);
char	*find_cmd(t_cmd *cmd, char **envp);

/* heredoc.c */
int		fill_here_doc(t_cmd *cmd, const char *limiter, int write_fd);
int		create_heredoc(t_cmd *cmd, const char *limiter);

/* pipeline_utils.c */
bool	have_redirections(t_cmd *cmd);
int		command_not_found(t_cmd *cmd);
int		**pipe_error(int **pipe_fd, int nbr_pipes);

/* close_all.c */
void	close_fds(t_cmd *cmd);
void	close_pipes_fds(int **pipe_fd, int nbr_pipes);
void	close_all_pipes(int **pipe_fd, int nbr_pipes, t_cmd *cmd);

/* free_pipe.c */
int		free_all_pipes(int **pipe_fd, int nbr_pipes);

/* pwd.c */
void	ft_pwd(void);

/* echo.c */
void	ft_echo(char **args);

/* env.c */
int		ft_env(char **args, char **envp);

/* exit.c */
int		ft_exit(char **args, t_data *data);

/* cd.c */
int		ft_cd(char **args, t_env *env);

/* unset.c */
void	ft_unset(char **args, t_env *env);

/* export.c */
void	ft_export(char **args, t_env *env);
char	**env_remove(t_env *env, t_export export);

/* export copy */
char	**env_copy(t_env *env);
char	**env_init(char **envp);
void	copy_env(t_env *env, char **new_envp);
void	copy_update_env(t_env *env, char **new_envp, int env_size, t_export export);
void	copy_remove_env(t_env *env, char **new_envp, int env_size, t_export export);

/* set_envp_path.c */
void	set_envp_paths(t_env *env);
char	*get_home_directory(t_env *env);
char	*get_oldpwd_directory(t_env *env);
char	*get_current_directory(void);
bool	verif_dir(const char *home, const char *oldpwd, const char *current);

/* update_env.c */
void	free_envp(char **envp);
char	**new_envp(t_env *env);

/* cd.c helpers */
void	update_env_paths(t_env *env);
int		no_file_or_dir(char *path);

/* unset.c */
bool	is_valid_identifier(char *arg);
bool	env_exist(t_env *env, char *arg);

//parsing
void	add_token(t_token **tokens, char *str, t_tokentype type);
int		is_redir(char *line, char *next_line, t_token **tokens);
int		is_pipe(char *line, t_token **tokens);
int		is_cmd(char *line, t_token **tokens);
int		count_cmd_data(t_data *data);
t_token	*lexer(char *line);
t_cmd	*build_cmd(t_token *tokens);
char	*expand(char *str);
char	*remove_quotes(char *str, int *quote);

//cleanup
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	cleanup_iteration(t_data *data);

//signals
void	setup_prompt_signals(void);
void	setup_heredoc_signals(void);
void	setup_child_signals(void);

//utils
void	free_envp(char **envp);
char	**new_envp(t_env *env);
int		get_env_size(t_env *env);
void	write_env_var(char *dest, t_export export, int key_len);
int		count_cmd_data(t_data *data);

#endif 