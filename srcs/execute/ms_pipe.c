/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:35:12 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/30 10:41:06 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pids(t_pipe *pids)
{
	close(pids->prev_pipe[0]);
	close(pids->prev_pipe[1]);
}

void	ms_pipe_exec(t_job *jobs, t_job *job_head)
{
	if (!check_builtins(jobs))
		execute(jobs->cmd, job_head);
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

void	child_process(t_job *tmp, t_pipe *pids, int i, t_job *job_head)
{
	create_dup(tmp, pids, i);
	init_redirs(tmp);
	if (g_mini.is_error)
	{
		garbage_collector(&job_head);
		exit (g_mini.output_code);
	}
	ms_pipe_exec(tmp, job_head);
}

void	ms_pipe(t_job *jobs)
{
	int		i;
	t_job	*tmp;
	t_pipe	*pids;
	int		nb_pipe;

	i = -1;
	tmp = jobs;
	pids = malloc(sizeof(t_pipe));
	nb_pipe = pipe_count(jobs);
	while (++i <= nb_pipe)
	{
		if (i < nb_pipe)
			pipe(pids->pipe_fd);
		tmp->pid = fork();
		if (tmp->pid == 0)
			child_process(tmp, pids, i, jobs);
		if (i > 0)
			close_pids(pids);
		tmp = tmp->next;
		pids->prev_pipe[0] = pids->pipe_fd[0];
		pids->prev_pipe[1] = pids->pipe_fd[1];
	}
	ms_pipe_wait(jobs, pids, nb_pipe);
}
