/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:25:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/16 11:43:32 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_builtins(t_job *jobs)
{
	if (ft_strcmp("exit", jobs->cmd[0]) == 0)
		ft_exit(jobs->cmd);
	else if (ft_strcmp("export", jobs->cmd[0]) == 0)
		ft_export(jobs->cmd);
	else if (ft_strcmp("echo", jobs->cmd[0]) == 0)
		ft_echo(jobs->cmd);
	else if (ft_strcmp("cd", jobs->cmd[0]) == 0)
		ft_cd(jobs->cmd);
	else if (ft_strcmp("unset", jobs->cmd[0]) == 0)
		ft_unset(jobs->cmd + 1);
	else if (ft_strcmp("pwd", jobs->cmd[0]) == 0)
		ft_pwd();
	else if (ft_strcmp("env", jobs->cmd[0]) == 0)
		ft_env(jobs->cmd);
	else
		return (false);
	return (true);
}

void	parent_process(t_job *jobs)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		execute(jobs->cmd);
	waitpid(pid, &status, 0);
	manage_signals(status);
}

void	ms_start_exec(t_job *jobs)
{
	signal(SIGINT, do_nothing);
	signal(SIGQUIT, do_nothing);
	if (jobs->next == NULL)
	{
		init_redirs(jobs);
		if (!check_builtins(jobs))
			parent_process(jobs);
		dup2(g_mini.fdin, 0);
		dup2(g_mini.fdout, 1);
	}
	else
		ms_pipe(jobs);
}
