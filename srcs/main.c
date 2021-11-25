/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:47:03 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/25 16:13:58 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	g_mini;

void	ms_free_line(char **line)
{
	if ((*line))
	{
		free((*line));
		*line = NULL;
	}
}

void	init_minishell(char **envp)
{
	g_mini.env = ft_strarr_dup(envp, 0);
	g_mini.env_size = ft_strarr_size(g_mini.env);
	g_mini.output_code = SUCCESS;
	g_mini.fdin = dup(0);
	g_mini.fdout = dup(1);
}

void	exec_start(char **line)
{
	t_token	*token;
	t_job	*jobs;
	char	*path;

	path = ft_getenv("PATH");
	g_mini.path = ft_split(path, ':');
	token = ft_args(*line);
	ms_free_line(line);
	token = manage_env(token);
	token = init_merge(token);
	jobs = init_jobs(token);
	ft_free_token(&token);
	ms_check_heredocs(jobs);
	ms_start_exec(jobs);
	ft_free_jobs(&jobs);
}

void	minishell_loop(void)
{
	char	*line;
	char	*trim_line;

	while (42)
	{
		set_signals();
		line = readline("\e[1;34mminishell-1.0$ \e[0m");
		if (!line)
			ctrl_d();
		if (ft_strlen(line) > 0)
			add_history(line);
		trim_line = ft_strtrim(line, WHITESPACES);
		free (line);
		if (ft_strlen(trim_line) > 0)
		{
			unex_token(trim_line);
			if (!g_mini.is_error && !check_dot(trim_line)
				&& !verify_quotes(trim_line))
				exec_start(&trim_line);
		}
		ms_free_line(&trim_line);
	}
}

int	main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;
	init_minishell(envp);
	change_level();
	minishell_loop();
	return (EXIT_SUCCESS);
}
