/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:47:03 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/16 13:16:49 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	g_mini;

void	init_minishell(char **envp)
{
	g_mini.env = ft_strarr_dup(envp, 0);
	g_mini.env_size = ft_strarr_size(g_mini.env);
	g_mini.output_code = SUCCESS;
	g_mini.open_quote = false;
	g_mini.char_quote = 0;
	g_mini.fdin = dup(0);
	g_mini.fdout = dup(1);
}

void	exec_start(char *line)
{
	t_token	*token;
	t_job	*jobs;
	char	*path;

	path = ft_getenv("PATH");
	g_mini.path = ft_split(path, ':');
	g_mini.open_quote = false;
	g_mini.char_quote = 0;
	token = ft_args(line);
	token = manage_env(token);
	token = init_merge(token);
	jobs = init_jobs(token);
	ms_check_heredocs(token, jobs);
	ms_start_exec(jobs);
	ft_free_stuff(&token, &jobs);
}

void	minishell_loop(void)
{
	char	*line;
	char	*trim_line;

	while (42)
	{
		line = readline("\033[0;34mminishell-1.0$ \033[0m");
		if (!line)
		{
			ft_putendl_fd("Exit", 2);
			exit(g_mini.output_code);
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		trim_line = ft_strtrim(line, WHITESPACES);
		free (line);
		if (ft_strlen(trim_line) > 0)
		{
			unex_token(trim_line);
			if (!g_mini.is_error && !check_dot(trim_line)
				&& !verify_quotes(trim_line))
				exec_start(trim_line);
		}
		free (trim_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_minishell(envp);
	change_level();
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	minishell_loop();
	return (EXIT_SUCCESS);
}
