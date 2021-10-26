/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:36:42 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/26 14:11:41 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cell(t_token **token, char **cmd)
{
	t_token *new_token;
	t_token	*tmp;

	new_token = ft_calloc(1, sizeof(t_token));
	new_token->cmd = cmd;
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
