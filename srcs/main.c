/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:47:03 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/27 15:49:08 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	g_mini;

void	init_minishell(char **envp)
{
	char	*path;

	g_mini.env = ft_strarr_dup(envp, 0);
	g_mini.env_size = ft_strarr_size(g_mini.env);
	path = getenv("PATH");
	g_mini.path = ft_split(path, ':');
	g_mini.output_code = SUCCESS;
	g_mini.open_quote = false;
	g_mini.char_quote = 0;
}

void	parse_cmds(char **arg)
{
	if (ft_strcmp(arg[0], "export") == 0)
		ft_export(arg + 1);
	else if (ft_strcmp(arg[0], "unset") == 0)
		ft_unset(arg + 1);
	else if (ft_strcmp(arg[0], "env") == 0)
		ft_env(arg + 1);
	else if (ft_strcmp(arg[0], "echo") == 0)
		ft_echo(arg + 1);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(arg[0], "cd") == 0)
		ft_cd(arg);
	else if (ft_strcmp(arg[0], "exit") == 0)
		ft_exit(arg);
	// execve
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;

	(void) argc;
	(void) argv;
	init_minishell(envp);
	while (1)
	{
		line = readline("\033[0;34mminishell-1.0$ \033[0m");
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			g_mini.open_quote = false;
			g_mini.char_quote = 0;
			unex_token(line);
			if (g_mini.is_error)
			{
				free (line);
				continue ;
			}
			if (verify_quotes(line))
			{
				print_error(NULL, NULL, QUOTES, SYNTAX_ERR);
				free (line);
				continue ;
			}
			token = ft_args(line);
			free(line);
			parse_cmds(&token->cmd[0]);
			ft_free_tokens(&token);
		}
	}
	return (EXIT_SUCCESS);
}
