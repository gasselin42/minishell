/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:47:03 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/09 12:10:46 by gasselin         ###   ########.fr       */
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
	g_mini.fdin = dup(0);
	g_mini.fdout = dup(1);
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

bool	init_exec(char *line, t_job **jobs, t_token **token)
{
	unex_token(line);
	if (g_mini.is_error)
	{
		free (line);
		return (false);
	}
	if (verify_quotes(line))
	{
		print_error(NULL, NULL, QUOTES, SYNTAX_ERR);
		free (line);
		return (false);
	}
	*token = ft_args(line);
	*token = manage_env(*token);
	*token = init_merge(*token);
	*jobs =	init_jobs(*token);
	free (line);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;
	t_job	*jobs;

	(void) argc;
	(void) argv;
	init_minishell(envp);
	// signal(SIGINT, ctrl_c);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("\033[0;34mminishell-1.0$ \033[0m");
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			g_mini.open_quote = false;
			g_mini.char_quote = 0;
			if (!init_exec(line, &jobs, &token))
				continue;
			ms_check_heredocs(token, jobs);
			ms_start_exec(jobs);
			ft_free_stuff(&token, &jobs);
		}
	}
	return (EXIT_SUCCESS);
}
