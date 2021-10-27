/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:43:09 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/27 10:06:27 by gasselin         ###   ########.fr       */
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

char	**parse_args(char *line, int *index)
{
	int		i;
	int		j;
	char	**token;

	i = *index;
	j = *index - 1;
	token = NULL;
	while (line[++j])
	{
		if (line[j] == '|')
		{
			if (!ft_iswhitespace(line[j - 1]))
				token = ft_strarr_addback(token, ft_substr(line, i, j - i));
			j++;
			while (ft_iswhitespace(line[j]))
				j++;
			break ;
		}
		else if (line[j] == 34 || line[j] == 39)
		{
			g_mini.open_quote = true;
			g_mini.char_quote = line[j];
			j++;
			while (line[j] && (g_mini.open_quote || !ft_iswhitespace(line[j])))
			{
				if (g_mini.open_quote == false && line[j] == '|')
				{
					token = ft_strarr_addback(token, ft_substr(line, i, j - i));
					j++;
					while (ft_iswhitespace(line[j]))
						j++;
					*index = j;
					return (token);
				}
				if (g_mini.open_quote && line[j] == g_mini.char_quote)
					g_mini.open_quote = false;
				if (!g_mini.open_quote && (line[j + 1] == 34 || line[j + 1] == 39))
				{
					j++;
					g_mini.open_quote = true;
					g_mini.char_quote = line[j];
				}
				j++;
			}
			while (ft_iswhitespace(line[j]))
				j++;
			token = ft_strarr_addback(token, ft_substr(line, i, j - i));
			i = j + 1;
		}
		else if (ft_iswhitespace(line[j]))
		{
			while (ft_iswhitespace(line[j]))
				j++;
			token = ft_strarr_addback(token, ft_substr(line, i, j - i));
			i = j;
			j--; 
		}
		else if (!line[j + 1])
		{
			token = ft_strarr_addback(token, ft_substr(line, i, j + 1 - i));
			j++;
			break ;
		}
	}
	*index = j;
	return (token);
}

t_token	*ft_args(char *line)
{
	t_token	*token;
	int		i;

	i = 0;
	token = NULL;
	while (i < (int)ft_strlen(line))
		add_cell(&token, parse_args(line, &i));
	token->cmd = ft_trim_args(token->cmd);
	return (token);
}
