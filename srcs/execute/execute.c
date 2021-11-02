/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:25:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/02 11:00:15 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	check_builtins(char **arg)
{
	if (ft_strcmp("exit", arg[0]) == 0)
		ft_exit(arg);
	else if (ft_strcmp("export", arg[0]) == 0)
		ft_export(arg);
	else if (ft_strcmp("echo", arg[0]) == 0)
		ft_echo(arg);
	else if (ft_strcmp("cd", arg[0]) == 0)
		ft_cd(arg);
	else if (ft_strcmp("unset", arg[0]) == 0)
		ft_unset(arg);
	else if (ft_strcmp("pwd", arg[0]) == 0)
		ft_pwd();
	else if (ft_strcmp("env", arg[0]) == 0)
		ft_env(arg);
	else
		return (false);
	return (true);
}

void	parent_process(char **arg)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork didn't work!");
	if (pid == 0)
	{
		if (!check_builtins(arg))
			execute(arg);
	}
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
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (!check_builtins(arg))
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