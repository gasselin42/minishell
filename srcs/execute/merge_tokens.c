/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:37:26 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/16 13:42:40 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_tokens3(t_token **tmp, char **str, char **str2)
{
	while ((*tmp)->over != DONE)
	{
		*str2 = ft_strjoin(*str, (*tmp)->cmd);
		free ((*str));
		*str = *str2;
		*tmp = (*tmp)->next;
	}
	*str2 = ft_strjoin(*str, (*tmp)->cmd);
	free (*str);
}

char	**merge_tokens2(t_token *tmp, char **merge, int i)
{
	char	*str;
	char	*str2;

	while (tmp != NULL)
	{
		if (!(tmp->over == DONE && !(tmp->type == TEXT && tmp->cmd[0] == '\0'
					&& (!tmp->prev || tmp->prev->over == DONE))))
		{
			tmp = tmp->next;
			continue ;
		}
		str = ft_strdup("");
		merge_tokens3(&tmp, &str, &str2);
		merge[i++] = ft_strdup(str2);
		free (str2);
		tmp = tmp->next;
	}
	merge[i] = NULL;
	return (merge);
}

char	**merge_tokens(t_token *token)
{
	char	**merge;
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	merge = malloc(sizeof(char *) * define_size(token));
	merge = merge_tokens2(tmp, merge, i);
	return (merge);
}

char	*merge_cmd(char **merge)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	line = NULL;
	if (merge && *merge)
	{
		line = ft_strdup(merge[0]);
		while (merge[++i])
		{
			tmp = ft_strjoin_triple(line, " ", merge[i]);
			free (line);
			line = ft_strdup(tmp);
			free (tmp);
		}
	}
	return (line);
}
