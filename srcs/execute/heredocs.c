/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:10:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/29 16:13:51 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_job *jobs, int *fd)
{
	int		ret;
	char	buff[2];
	char	*line;

	close(fd[1]);
	line = NULL;
	while (true)
	{
		ret = read(fd[0], &buff, 1);
		buff[1] = '\0';
		if (ret == 0)
			break ;
		line = ft_str_append(line, buff[0]);
	}
	jobs->hdoc = line;
	close(fd[0]);
}

void	heredoc_loop(t_job *jobs, t_job *job_head, int *fd, char *limiter)
{
	char	*input;

	signal(SIGINT, exit_heredoc);
	(void)job_head;
	(void)jobs;
	while (true)
	{
		input = readline("> ");
		if (!ft_strcmp(input, limiter))
		{
			close(fd[0]);
			close(fd[1]);
			break ;
		}
		ft_putendl_fd(input, fd[1]);
		free (input);
	}
	free (input);
	// ft_free_jobs(&job_head);
	// ft_strarr_free(g_mini.env);
	exit (0);
}

int	redir_heredocs(t_job *jobs, t_job *job_head, char *limiter)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	signal(SIGINT, do_nothing);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		heredoc_loop(jobs, job_head, fd, limiter);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_mini.output_code = WEXITSTATUS(status);
	dup2(fd[0], jobs->fd[0]);
	close(fd[1]);
	close(fd[0]);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (1);
	return (0);
}

int	ms_check_heredocs(t_job *jobs)
{
	t_job	*tmp;
	int		i;

	tmp = jobs;
	while (tmp)
	{
		i = 0;
		if (tmp->redirs)
		{
			while (tmp->redirs[i])
			{
				if (ft_strcmp(tmp->redirs[i], "<<") == 0)
					if (redir_heredocs(tmp, jobs, tmp->redirs[i + 1]) == 1)
						return (1);
				i += 2;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
