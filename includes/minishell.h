/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:46:28 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/26 15:52:47 by gasselin         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define NO_HOME "HOME not set"
# define NO_FLDIR "No such file or directory"
# define ARGS_ERR "too many arguments"
# define NO_IDENT "not a valid identifier"
# define NUM_ERR "numeric argument required"
# define QUOTES "unclosed quote(s)"
# define UNEX_PIPE "syntax error near unexpected token '|'"
# define UNEX_SEMIC "syntax error near unexpected token ';'"

# define SUCCESS 0
# define GEN_ERR 1
# define SYNTAX_ERR 2
# define EXIT_ERR 255

# define WHITESPACES "\t\n\v\f\r "
# define NAMESET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_"

typedef struct s_pipes
{
	int	fdout;
	int fdin;
}	t_pipes;

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			**cmd;
}	t_token;

typedef struct s_minishell
{
	char		**env;
	char		**path;
	int			env_size;
	long int	output_code;
	bool		open_quote;
	char		char_quote;
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

t_token	*ft_args(char *line);
void	add_cell(t_token **token, char **cmd);

bool	unexpected_token(char *line);
bool	verify_quotes(const char *str);
void	print_error(const char *v1, const char *v2, const char *v3, int code);

void	ft_free_tokens(t_token **token);

#endif