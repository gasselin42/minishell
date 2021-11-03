/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:43:09 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/03 11:43:10 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_trim_args(char **arr)
{
	char	**dup;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	dup[i] = NULL;
	i = -1;
	while (arr[++i])
		dup[i] = ft_strtrim(arr[i], WHITESPACES);
	ft_strarr_free(arr);
	arr = NULL;
	return (dup);
}

t_token	*add_pipe(t_token *token, t_token *pipe)
{
	t_token	*tmp;

	tmp = token;
	if (token == NULL)
		return (pipe);
	while (tmp->pipe != NULL)
		tmp = tmp->pipe;
	while (tmp->next != NULL)
	{
		tmp->pipe = pipe;
		tmp = tmp->next;
	}
	tmp->pipe = pipe;
	return (token);
}

t_token	*ft_args(char *line)
{
	t_token	*token;
	t_token	*pipe;
	int		i;

	i = 0;
	token = NULL;
	while (i < (int)ft_strlen(line))
	{
		pipe = parse_args(line, &i);
		token = add_pipe(token, pipe);
	}
	return (token);
}
