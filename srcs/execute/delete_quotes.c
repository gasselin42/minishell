/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:42:38 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/28 12:07:01 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_quotes(char **cmd)
{
	int	i;
}

t_token	*delete_quotes(t_token *token)
{
	t_token	*tmp;
	int		i;
	
	tmp = token;
	while (tmp == NULL)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (ft_strchr(tmp->cmd[i], '\"') || ft_strchr(tmp->cmd[i], '\''))
				manage_quotes(&tmp->cmd[i]);
			i++;
		}
	}
	return (token);
}