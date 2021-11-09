/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:46:28 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/09 16:09:49 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define NO_HOME "HOME not set"
# define NO_FLDIR "No such file or directory"
# define ARGS_ERR "too many arguments"
# define NO_IDENT "not a valid identifier"
# define NUM_ERR "numeric argument required"
# define QUOTES "unclosed quote(s)"
# define DIRECTORY "is a directory"
# define CMD_NOT_FOUND "command not found"

# define UNEX_PIPE "syntax error near unexpected token '|'"
# define UNEX_PIPES "syntax error near unexpected token '||'"
# define UNEX_REDIR_L "syntax error near unexpected token '<'"
# define UNEX_REDIRS_L "syntax error near unexpected token '<<'"
# define UNEX_REDIR_R "syntax error near unexpected token '>'"
# define UNEX_REDIRS_R "syntax error near unexpected token '>>'"
# define UNEX_REDIRS_LR "syntax error near unexpected token '<>'"
# define UNEX_SEMIC "syntax error near unexpected token ';'"
# define UNEX_SEMICS "syntax error near unexpected token ';;'"
# define UNEX_NEWLINE "syntax error near unexpected token `newline'"

# define SUCCESS 0
# define GEN_ERR 1
# define SYNTAX_ERR 2
# define DIR_ERR 126
# define FILE_ERR 127
# define EXIT_ERR 255

# define CTRL_B 131
# define CTRL_C 1
# define CTRL_D 0

# define WHITESPACES "\t\n\v\f\r "
# define NAMESET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_"
# define SYNTAX "<|>"

typedef enum e_over
{
	DONE,
	CONTINUE,
}	t_over;

typedef enum e_type
{
	TEXT,
	S_QUOTE,
	D_QUOTE,
	REDIR_L,
	REDIR_R,
	HEREDOC,
	APPEND
}	t_type;

typedef struct s_redirs
{
	t_type	type;
	char	**file;
}	t_redirs;

typedef struct s_job
{
	char			**cmd;
	char			**redirs;
	char			*hdoc;
	char			*hdoc_inputs;
	int				hdoc_fd[2];
	struct s_job	*next;
}	t_job;

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	struct s_token	*pipe;
	char			*cmd;
	char			*merge_cmd;
	char			**merge;
	pid_t			fd[2];
	t_type			type;
	t_over			over;
	t_redirs		*redirs;
}	t_token;

typedef struct s_minishell
{
	char		**env;
	char		**path;
	int			env_size;
	long int	output_code;
	int			is_error;
	bool		open_quote;
	char		char_quote;
	char		*syntax;
	// bool		dbl_redir;
	pid_t		pid;
	// char		*heredoc_pwd;
	char		*cwd_exec;
	char		*path_exec;
	int			fdin;
	int			fdout;
	int			**fd_pipe;
}	t_minishell;

extern t_minishell g_mini;

void	ft_echo(char **argv);
void	ft_cd(char **argv);
void	ft_env(char **argv);
void	ft_export(char **argv);
void	ft_unset(char **argv);
void	ft_pwd(void);
void	ft_exit(char **argv);

char	*ft_getenv(const char *name);
int		ft_setenv(const char *name, const char *value, int overwrite);
void	ft_addenv(const char *name, const char *value);

t_token	*init_merge(t_token *token);
t_token	*ft_args(char *line);
t_token *parse_args(char *line, int *index);
t_job	*init_jobs(t_token *token);
void	add_cell(t_token **token, char *cmd, t_type type, t_over over);

void	unex_token(char *str);
bool	verify_quotes(char *str);
void	manage_syntax(char *str);
int		manage_syntax3(char *str);
void	manage_newline(void);

t_token	*manage_env(t_token *token);
char	*place_env(char *cmd, int *i);
char	**merge_tokens(t_token *token);
int		count_redirs(t_token *token);
int		is_redirection(char	*cmd);

void	ms_start_exec(t_job *jobs);
void	ms_exec(t_token *token);
void	execute(char **cmd);
char	*find_path(const char *cmd);

void	init_redirs(t_job *jobs);
void	redir_heredocs(t_job *jobs, int i);
void	hdoc_write(t_job *jobs);
void	ms_check_heredocs(t_token *token, t_job *jobs);

void	print_error(const char *v1, const char *v2, const char *v3, int code);

void	ft_free_stuff(t_token **token, t_job **jobs);

int		pipe_count(t_job *jobs);

#endif