/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:10:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/16 13:31:06 by gasselin         ###   ########.fr       */
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

void	heredoc_loop(t_job *jobs, int *fd)
{
	char	*input;

	signal(SIGINT, exit_heredoc);
	jobs->hdoc_inputs = NULL;
	close(fd[0]);
	while (true)
	{
		input = readline("> ");
		if (!ft_strcmp(input, jobs->hdoc))
			break ;
		jobs->hdoc_inputs = join_inputs(jobs, input);
		free (input);
	}
	jobs->hdoc_inputs = join_inputs(jobs, "");
	ft_putstr_fd(jobs->hdoc_inputs, fd[1]);
	free (input);
	free (jobs->hdoc);
	free (jobs->hdoc_inputs);
	exit (0);
}

void	redir_heredocs(t_job *jobs, int i)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	signal(SIGINT, do_nothing);
	jobs->hdoc = jobs->redirs[i];
	pipe(fd);
	pid = fork();
	if (pid == 0)
		heredoc_loop(jobs, fd);
	waitpid(pid, &status, 0);
	read_input(jobs, fd);
}

void	hdoc_write(t_job *jobs)
{
	pipe(jobs->hdoc_fd);
	dup2(jobs->hdoc_fd[0], 0);
	ft_putstr_fd(jobs->hdoc, jobs->hdoc_fd[1]);
	close(jobs->hdoc_fd[0]);
	close(jobs->hdoc_fd[1]);
	free (jobs->hdoc);
}

void	ms_check_heredocs(t_token *token, t_job *jobs)
{
	t_job	*tmp;
	int		i;

	(void)token;
	tmp = jobs;
	while (tmp)
	{
		i = 0;
		if (tmp->redirs)
		{
			while (tmp->redirs[i])
			{
				if (ft_strcmp(tmp->redirs[i], "<<") == 0)
					redir_heredocs(tmp, i + 1);
				i += 2;
			}
		}
		tmp = tmp->next;
	}
}
