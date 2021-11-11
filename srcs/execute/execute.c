/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:25:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/11 14:36:38 by gasselin         ###   ########.fr       */
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
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_mini.output_code = WEXITSTATUS(status);
	}
}

void	ms_pipe_exec(t_job *jobs)
{
	if (!check_builtins(jobs))
		execute(jobs->cmd);
	exit(0);
}

void	child_process(t_job *jobs)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == 0)
		ms_pipe_exec(jobs);
	waitpid(pid, &status, 0);
	dup2(g_mini.fdin, 0);
	dup2(g_mini.fdout, 1);
	if (WIFEXITED(status))
		g_mini.output_code = WEXITSTATUS(status);
}

void	create_dup(t_job *jobs, int i)
{
	if (i > 0)
		dup2(g_mini.fd_pipe[i - 1][0], 0);
	if (jobs->next)
	{
		dup2(g_mini.fd_pipe[i][1], 1);
		if (i > 0)
			close(g_mini.fd_pipe[i - 1][0]);
		close(g_mini.fd_pipe[i][1]);
	}
	if (jobs->next == NULL)
		dup2(g_mini.fdout, 1);
}

void	ms_pipe(t_job *jobs)
{
	int		i;
	t_job	*tmp;

	i = 0;
	tmp = jobs;
	while (tmp)
	{
		create_dup(tmp, i);
		init_redirs(tmp);
		child_process(tmp);
		tmp = tmp->next;
		i++;
	}
}

void	ms_start_exec(t_job *jobs)
{
	int	count;
	int	i;

	if (jobs->next == NULL)
	{
		init_redirs(jobs);
		if (!check_builtins(jobs))
			parent_process(jobs);
		dup2(g_mini.fdin, 0);
		dup2(g_mini.fdout, 1);
	}
	else
	{
		i = 0;
		count = pipe_count(jobs);
		g_mini.fd_pipe = ft_calloc(sizeof(int), count + 1);
		while (count > 0)
		{
			g_mini.fd_pipe[i] = malloc(sizeof(int) * 2);
			pipe(g_mini.fd_pipe[i]);
			i++;
			count--;
		}
		ms_pipe(jobs);
	}
}
