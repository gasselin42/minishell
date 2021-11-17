/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:06:30 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/17 14:22:45 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_merge(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		free (tmp->merge_cmd);
		ft_strarr_free(tmp->merge);
		tmp->merge = NULL;
		tmp = tmp->pipe;
	}
}

void	ft_free_jobs(t_job **jobs)
{
	t_job	*tmp;

	if (jobs)
	{
		while ((*jobs) != NULL)
		{
			tmp = (*jobs)->next;
			if ((*jobs)->cmd)
				ft_strarr_free((*jobs)->cmd);
			if ((*jobs)->redirs)
				ft_strarr_free((*jobs)->redirs);
			if ((*jobs)->hdoc)
			{
				free ((*jobs)->hdoc);
				(*jobs)->hdoc = NULL;
			}
			free ((*jobs));
			*jobs = tmp;
		}
	}
}

void	ft_free_stuff(t_token **token, t_job **jobs)
{
	t_token	*tmp;

	ft_strarr_free(g_mini.path);
	if (token)
	{
		ft_free_merge(token);
		while ((*token) != NULL)
		{
			tmp = (*token)->next;
			if (tmp == NULL && (*token)->pipe)
				tmp = (*token)->pipe;
			free ((*token)->cmd);
			free ((*token));
			*token = tmp;
		}
	}
	ft_free_jobs(jobs);
}
