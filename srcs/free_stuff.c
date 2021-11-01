/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:06:30 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/01 14:19:49 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_token **token)
{
	t_token *tmp;
	
	if (token)
	{
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
}
