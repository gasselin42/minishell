/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:47:03 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/01 16:50:32 by gasselin         ###   ########.fr       */
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

void	parse_cmds(t_token *token)
{
	char	**arg;

	arg = merge_tokens(token);
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
	else
		ms_exec(token);
}

void	ctrl_backslash(int sig)
{
	(void)sig;
	printf("Quit");
	g_mini.output_code = CTRL_B;
}

void	ctrl_d(int sig)
{
	(void)sig;
	printf("\n");
	g_mini.output_code = CTRL_D;
}

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_mini.output_code = CTRL_C;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;

	(void) argc;
	(void) argv;
	init_minishell(envp);
	// line = "Allo$LOGNAME";
	// token = ft_args(line);
	// token = manage_env(token);
	// signal(SIGINT, ctrl_c);
	// signal(SIGQUIT, SIG_IGN);
	// int i = -1;
	// while (g_mini.path[++i])
	// 	printf("%s\n", g_mini.path[i]);
	// char **arg = malloc(sizeof(char *) * 3);
	// arg[0] = ft_strdup("ls");
	// arg[1] = ft_strdup("-la");
	// arg[2] = NULL;
	// execve("/bin/ls", arg, envp);
	while (1)
	{
		line = readline("\033[0;34mminishell-1.0$ \033[0m");
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			g_mini.open_quote = false;
			g_mini.char_quote = 0;
			unex_token(line);
			if (verify_quotes(line))
			{
				print_error(NULL, NULL, QUOTES, SYNTAX_ERR);
				free (line);
				continue ;
			}
			if (g_mini.is_error)
			{
				free (line);
				continue ;
			}
			token = ft_args(line);
			token = manage_env(token);
			parse_cmds(token);
			// char **merge = merge_tokens(token);
			// printf("%s\n", merge[0]);
			// printf("%s\n", merge[1]);
			// printf("%s\n", merge[2]);
			// printf("%s\n", token->cmd);
			// printf("%s\n", token->next->cmd);
			// printf("%s\n", token->pipe->cmd);
			// printf("%u\n", token->pipe->over);
			// printf("%u\n", token->pipe->type);
			// printf("%s\n", token->pipe->next->cmd);
			// printf("%u\n", token->pipe->next->over);
			// printf("%u\n", token->pipe->next->type);
			free(line);
			ft_free_tokens(&token);
		}
	}
	printf("Program Exited!");
	return (EXIT_SUCCESS);
}
