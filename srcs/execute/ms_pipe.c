/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:35:12 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/29 15:55:10 by gasselin         ###   ########.fr       */
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
		execute(jobs->cmd, jobs);
	else
	{
		ft_free_jobs(&job_head);
		ft_strarr_free(g_mini.env);
	}
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

void	free_fd(t_job *job_head)
{
	while (job_head)
	{
		close(job_head->fd[0]);
		close(job_head->fd[1]);
		job_head = job_head->next;
	}
}

void	child_process(t_job *jobs, t_job *job_head)
{
	if (jobs->prev != NULL)
		dup2(jobs->prev->fd[0], 0);
	if (jobs->next)
		dup2(jobs->fd[1], 1);
	init_redirs(jobs);
	if (g_mini.is_error)
	{
		ft_free_jobs(&job_head);
		ft_strarr_free(g_mini.env);
		exit (g_mini.output_code);
	}
	close(jobs->fd[0]);
	close(jobs->fd[1]);
	// free_fd(job_head);
	ms_pipe_exec(jobs, job_head);
}

void	ms_pipe(t_job *jobs)
{
	t_job	*tmp;
	int		nb_pipe;

	tmp = jobs;
	nb_pipe = pipe_count(jobs);
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
			child_process(tmp, jobs);
		if (jobs->prev)
			close(jobs->prev->fd[0]);
		close(jobs->fd[1]);
		tmp = tmp->next;
	}
	ms_pipe_wait(jobs, nb_pipe);
}
