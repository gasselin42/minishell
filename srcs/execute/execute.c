/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:25:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/10 14:52:47 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 	i = 0;
// 	saved_stdin = dup(0);
// 	tmp = token;
// 	if (token)
// 	{
// 		while (tmp->pipe)
// 		{
// 			arg = merge_tokens(tmp);
// 			child_process(arg);
// 			ft_strarr_free(arg);
// 			arg = NULL;
// 			tmp = tmp->pipe;
// 		}
// 		arg = merge_tokens(tmp);
// 		parent_process(arg);
// 		dup2(saved_stdin, 0);
// 		close(saved_stdin);
// 		ft_strarr_free(arg);
// 		arg = NULL;
// 	}
// 	return ;
// }

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
		ft_unset(jobs->cmd);
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
	if (WIFEXITED(status))
		g_mini.output_code = WEXITSTATUS(status);
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

void	create_dup(t_job *jobs, t_pipe *pipes, int i)
{
	if (i > 0)
	{
		dup2(pipes->prev_fd[0], 0);
		close(pipes->prev_fd[0]);
		close(pipes->prev_fd[1]);
	}
	if (jobs->next)
	{
		dup2(pipes->pipe_fd[1], 1);
		close(pipes->pipe_fd[1]);
		close(pipes->pipe_fd[0]);
	}
}

void	ms_pipe(t_job *jobs)
{
	int	i;
	t_job	*tmp;
	t_pipe	*pipes;

	i = 0;
	pipes = malloc(sizeof(t_pipe));
	pipes->nb_pipe = pipe_count(jobs);
	tmp = jobs;
	while (tmp)
	{
		if (i < pipes->nb_pipe)
			pipe(pipes->pipe_fd);
		tmp->pid = fork();
		if (tmp->pid == 0)
		{
			create_dup(tmp, pipes, i);
			init_redirs(tmp);
			ms_pipe_exec(tmp);
		}
		tmp = tmp->next;
		i++;
	}
}

void	ms_start_exec(t_job *jobs)
{
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
		ms_pipe(jobs);
}
