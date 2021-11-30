/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:59:18 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/25 15:56:49 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_d(void)
{
	ft_putendl_fd("Exit", 2);
	ft_strarr_free(g_mini.env);
	exit(g_mini.output_code);
}

void	ms_pipe_wait(t_job *jobs, t_pipe *pids, int nb_pipe)
{
	t_job	*tmp;
	int		i;

	i = 0;
	tmp = jobs;
	while (i++ <= nb_pipe)
	{
		waitpid(tmp->pid, &(tmp->status), 0);
		if (tmp->next)
			tmp = tmp->next;
	}
	free (pids);
}

bool	check_dot(char *line)
{
	if (ft_strcmp(line, ".") == 0)
	{
		print_error(NULL, ".", FILE_NAME_RQD, SYNTAX_ERR);
		return (true);
	}
	return (false);
}

void	print_error(const char *v1, const char *v2, const char *v3, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (v1)
	{
		ft_putstr_fd(v1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (v2)
	{
		ft_putstr_fd(v2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(v3, STDERR_FILENO);
	g_mini.output_code = code;
	g_mini.is_error = 1;
}
