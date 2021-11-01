/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:25:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/01 16:17:55 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	get_next_line(char **line)
// {
// 	char	*buffer;
// 	int		i;
// 	int		ret;
// 	char	c;

// 	i = -1;
// 	ret = 0;
// 	buffer = (char *)malloc(10000);
// 	if (!buffer)
// 		return (-1);
// 	ret = read(0, &c, 1);
// 	while (ret && c != '\n' && c != '\0')
// 	{
// 		if (c != '\n' && c != '\0')
// 			buffer[i] = c;
// 		i++;
// 		ret = read(0, &c, 1);
// 	}
// 	buffer[i] = '\n';
// 	buffer[++i] = '\0';
// 	*line = buffer;
// 	free(buffer);
// 	return (ret);
// }

// int	open_file(char *argv, int i)
// {
// 	int	file;

// 	file = 0;
// 	if (i == 0)
// 		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	else if (i == 1)
// 		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	else if (i == 2)
// 		file = open(argv, O_RDONLY, 0777);
// 	/* if (file == -1)
// 		erreur d'ouverture de file */
// 	return (file);
// }

void	parent_process(char **arg)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork didn't work!");
	if (pid == 0)
		execute(arg);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_mini.output_code = WEXITSTATUS(status);
	}
}

void	child_process(char **arg)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	status = 0;
	if (pipe(fd) == -1)
		printf("Dang! This pipe didn't work!");
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork didn't work!");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(arg);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0); 
		if (WIFEXITED(status))
			g_mini.output_code = WEXITSTATUS(status);
	}
}

void	ms_exec(t_token *token)
{
	int	i;
	int	saved_stdin;
	t_token	*tmp;
	char	**arg;

	i = 0;
	saved_stdin = dup(0);
	tmp = token;
	if (token)
	{
		while (tmp->pipe)
		{
			arg = merge_tokens(tmp);
			child_process(arg);
			ft_strarr_free(arg);
			arg = NULL;
			tmp = tmp->pipe;
		}
		arg = merge_tokens(tmp);
		parent_process(arg);
		dup2(saved_stdin, 0);
		close(saved_stdin);
		ft_strarr_free(arg);
		arg = NULL;
	}
	return ;
}