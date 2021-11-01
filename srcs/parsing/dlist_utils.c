/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:36:42 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/01 16:08:55 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cell(t_token **token, char *cmd, t_type type, t_over over)
{
	t_token *new_token;
	t_token	*tmp;

	new_token = ft_calloc(1, sizeof(t_token));
	new_token->cmd = cmd;
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
