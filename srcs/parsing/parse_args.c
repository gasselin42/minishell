/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:43:09 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/01 16:35:00 by gasselin         ###   ########.fr       */
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

t_token *parse_args(char *line, int *index)
{
	int		i;
	int		j;
	t_token	*token;
	t_type	type;
	t_over	over;

	i = *index;
	j = *index - 1;
	token = NULL;
	while (line[++j])
	{
		over = DONE;
		if (line[j] == '|')
		{
			if (!ft_iswhitespace(line[j - 1]))
				add_cell(&token, ft_substr(line, i, j - i), TEXT, DONE);
			j++;
			while (ft_iswhitespace(line[j]))
				j++;
			break ;
		}
		else if (line[j] == 34 || line[j] == 39)
		{
			g_mini.open_quote = true;
			g_mini.char_quote = line[j];
			if (line[j] == 34)
				type = D_QUOTE;
			else
				type = S_QUOTE;
			j++;
			i = j;
			while (line[j] && g_mini.open_quote)
			{
				if (g_mini.open_quote && line[j] == g_mini.char_quote)
					g_mini.open_quote = false;
				j++;
			}
			if (line[j] && (!ft_iswhitespace(line[j]) && line[j] != '|'))
				over = CONTINUE;
			add_cell(&token, ft_substr(line, i, j - i - 1), type, over);
			while (ft_iswhitespace(line[j]))
				j++;
			i = j;
			j--;
		}
		else if (ft_iswhitespace(line[j]))
		{
			add_cell(&token, ft_substr(line, i, j - i), TEXT, DONE);
			while (ft_iswhitespace(line[j]))
				j++;
			i = j;
			j--; 
		}
		else if (!line[j + 1])
		{
			j++;
			add_cell(&token, ft_substr(line, i, j - i), TEXT, DONE);
			break ;
		}
	}
	*index = j;
	return (token);
}

t_token	*add_pipe(t_token *token, t_token *pipe)
{
	t_token *tmp;

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
