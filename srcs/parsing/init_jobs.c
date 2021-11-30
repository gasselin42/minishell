/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:57:07 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/16 14:33:10 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job	*get_last_job(t_job	*job)
{
	t_job	*tmp;

	tmp = job;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_job	*add_back_job(t_job *job)
{
	t_job	*tmp;
	t_job	*new_job;

	tmp = job;
	new_job = ft_calloc(1, sizeof(t_job));
	if (!job)
		return (new_job);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_job;
	return (job);
}

char	**fill_cmd(t_token *token, int redirs)
{
	char	**cmd;
	int		count;
	int		i;
	int		j;

	i = -1;
	j = -1;
	count = ft_strarr_iter(token->merge) - redirs;
	cmd = (char **)malloc(sizeof(char *) * (count + 1));
	cmd[count] = NULL;
	while (token->merge[++j])
	{
		if (!is_redirection(token->merge[j]))
			cmd[++i] = ft_strdup(token->merge[j]);
		else
			j++;
	}
	return (cmd);
}

char	**fill_redirs(t_token *token, int count)
{
	char	**redirs;
	int		i;
	int		j;

	i = -1;
	j = -1;
	redirs = (char **)malloc(sizeof(char *) * (count + 1));
	redirs[count] = NULL;
	while (token->merge[++j])
	{
		if (is_redirection(token->merge[j]))
		{
			redirs[++i] = ft_strdup(token->merge[j]);
			j++;
			redirs[++i] = ft_strdup(token->merge[j]);
		}
	}
	return (redirs);
}

t_job	*init_jobs(t_token *token)
{
	t_job	*jobs;
	t_job	*active_job;
	t_token	*tmp;
	int		count;

	tmp = token;
	jobs = NULL;
	while (tmp)
	{
		jobs = add_back_job(jobs);
		active_job = get_last_job(jobs);
		count = count_redirs(tmp);
		if (count)
			active_job->redirs = fill_redirs(tmp, count);
		if (count < ft_strarr_iter(tmp->merge))
			active_job->cmd = fill_cmd(tmp, count);
		tmp = tmp->pipe;
	}
	return (jobs);
}
