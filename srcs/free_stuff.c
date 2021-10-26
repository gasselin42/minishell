/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:06:30 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/26 14:12:41 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_token **token)
{
	t_token *tmp;
	t_token	*tmp2;
	
	if ((*token))
	{
		tmp = *token;
		while (tmp != NULL)
		{
			tmp2 = (*token)->next;
			ft_strarr_free(tmp->cmd);
			tmp->next = NULL;
			tmp->prev = NULL;
			tmp = tmp2;
		}
	}
}
