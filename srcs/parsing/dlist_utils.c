/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:36:42 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/17 14:19:36 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(t_job *jobs)
{
	int		count;
	t_job	*tmp;

	tmp = jobs;
	count = 0;
	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	add_cell(t_token **token, char *cmd, t_type type, t_over over)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = ft_calloc(1, sizeof(t_token));
	new_token->cmd = ft_strdup(cmd);
	free (cmd);
	new_token->type = type;
	new_token->over = over;
	new_token->pipe = NULL;
	new_token->next = NULL;
	if ((*token) == NULL)
	{
		(*token) = new_token;
		return ;
	}
	tmp = (*token);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->prev = tmp;
}
