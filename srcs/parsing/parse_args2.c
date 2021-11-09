/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:56:45 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/09 11:46:50 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redirs(t_token **token, char *line, int *i, int *j)
{
	if (!ft_iswhitespace(line[*j - 1]))
		add_cell(token, ft_substr(line, *i, *j - *i), TEXT, DONE);
	if (line[*j] == '>' && line[*j + 1] == '>')
		add_cell(token, ft_substr(line, *j, 2), APPEND, DONE);
	else if (line[*j] == '<' && line[*j + 1] == '<')
		add_cell(token, ft_substr(line, *j, 2), HEREDOC, DONE);
	else if (line[*j] == '>')
		add_cell(token, ft_substr(line, *j, 1), REDIR_R, DONE);
	else if (line[*j] == '<')
		add_cell(token, ft_substr(line, *j, 1), REDIR_L, DONE);
	*j += 1;
	if (ft_strchr(SYNTAX, line[*j]))
		*j += 1;
	while (ft_iswhitespace(line[*j]))
		*j += 1;
	*i = *j;
	*j -= 1;
}

void	parse_quotes(t_token **token, char *line, int *i, int *j)
{
	t_type	type;
	t_over	over;

	over = DONE;
	g_mini.open_quote = true;
	g_mini.char_quote = line[*j];
	type = S_QUOTE;
	if (line[*j] == 34)
		type = D_QUOTE;
	*j += 1;
	*i = *j;
	while (line[*j] && g_mini.open_quote)
	{
		if (g_mini.open_quote && line[*j] == g_mini.char_quote)
			g_mini.open_quote = false;
		*j += 1;
	}
	if (line[*j] && (!ft_iswhitespace(line[*j]) && line[*j] != '|'))
		over = CONTINUE;
	add_cell(token, ft_substr(line, *i, *j - *i - 1), type, over);
	while (ft_iswhitespace(line[*j]))
		*j += 1;
	*i = *j;
	*j -= 1;
}

void	parse_args2(t_token **token, char *line, int *i, int *j)
{
	if (line[*j] == 34 || line[*j] == 39)
	{
		if (!ft_iswhitespace(line[*j - 1]))
			add_cell(token, ft_substr(line, *i, *j - *i), TEXT, CONTINUE);
		parse_quotes(token, line, i, j);
	}
	else if (ft_iswhitespace(line[*j]))
	{
		add_cell(token, ft_substr(line, *i, *j - *i), TEXT, DONE);
		while (ft_iswhitespace(line[*j]))
			*j += 1;
		*i = *j;
		*j -= 1;
	}
	else if (line[*j] == '<' || line[*j] == '>')
		parse_redirs(token, line, i, j);
}

void	parse_pipes(t_token **token, char *line, int *i, int *j)
{
	if (!ft_iswhitespace(line[*j - 1]))
		add_cell(token, ft_substr(line, *i, *j - *i), TEXT, DONE);
	*j += 1;
	while (ft_iswhitespace(line[*j]))
		*j += 1;
}

t_token	*parse_args(char *line, int *index)
{
	int		i;
	int		j;
	t_token	*token;

	i = *index;
	j = *index - 1;
	token = NULL;
	while (line[++j])
	{
		if (line[j] == '|')
		{
			parse_pipes(&token, line, &i, &j);
			break ;
		}
		else if (!line[j + 1])
		{
			j++;
			add_cell(&token, ft_substr(line, i, j - i), TEXT, DONE);
			break ;
		}
		else
			parse_args2(&token, line, &i, &j);
	}
	*index = j;
	return (token);
}
