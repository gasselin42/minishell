/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:35:12 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/16 11:45:57 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pipe_exec(t_job *jobs)
{
	if (!check_builtins(jobs))
		execute(jobs->cmd);
	exit(g_mini.output_code);
}

void	create_dup(t_job *jobs, t_pipe *data, int i)
{
	if (i > 0)
	{
		dup2(data->prev_pipe[0], 0);
		close(data->prev_pipe[0]);
		close(data->prev_pipe[1]);
	}
	if (jobs->next)
	{
		dup2(data->pipe_fd[1], 1);
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
	}
}

void	ms_pipe_wait(t_job *jobs)
{
	t_job	*tmp;
	int		i;

	i = 0;
	tmp = jobs;
	while (i++ <= g_mini.nb_pipe)
	{
		waitpid(tmp->pid, &(tmp->status), 0);
		if (tmp->next)
			tmp = tmp->next;
	}
}

void	child_process(t_job *tmp, t_pipe *pids, int i)
{
	create_dup(tmp, pids, i);
	init_redirs(tmp);
	ms_pipe_exec(tmp);
}

void	ms_pipe(t_job *jobs)
{
	int		i;
	t_job	*tmp;
	t_pipe	*pids;

	i = -1;
	tmp = jobs;
	pids = malloc(sizeof(t_pipe));
	g_mini.nb_pipe = pipe_count(jobs);
	while (++i <= g_mini.nb_pipe)
	{
		if (i < g_mini.nb_pipe)
			pipe(pids->pipe_fd);
		tmp->pid = fork();
		if (tmp->pid == 0)
			child_process(tmp, pids, i);
		if (i > 0)
		{
			close(pids->prev_pipe[0]);
			close(pids->prev_pipe[1]);
		}
		tmp = tmp->next;
		pids->prev_pipe[0] = pids->pipe_fd[0];
		pids->prev_pipe[1] = pids->pipe_fd[1];
	}
	ms_pipe_wait(jobs);
}
