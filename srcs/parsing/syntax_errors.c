/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:03:49 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/28 10:28:59 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	verify_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (g_mini.open_quote == false && (str[i] == 34 || str[i] == 39))
		{
			g_mini.open_quote = true;
			g_mini.char_quote = str[i];
		}
		else if (g_mini.open_quote == true && str[i] == g_mini.char_quote)
			g_mini.open_quote = false;
		i++;
	}
	return (g_mini.open_quote);
}

int	unex_token3(int i)
{
	manage_syntax(g_mini.syntax + i);
	if (g_mini.is_error == 0)
	{
		if (g_mini.syntax[i] == '>' && g_mini.syntax[i + 1] == '|')
			i += manage_syntax3(g_mini.syntax + i + 1);
		else
			i += manage_syntax3(g_mini.syntax + i);
	}
	return (i);
}

void	unex_token2(void)
{
	int	i;

	i = -1;
	while (g_mini.syntax[++i] && !g_mini.is_error)
	{
		if (g_mini.open_quote == false && (g_mini.syntax[i] == 34
				|| g_mini.syntax[i] == 39))
		{
			g_mini.open_quote = true;
			g_mini.char_quote = g_mini.syntax[i];
		}
		else if (g_mini.open_quote == true
			&& g_mini.syntax[i] == g_mini.char_quote)
			g_mini.open_quote = false;
		else if (!g_mini.open_quote && ft_strchr(SYNTAX, g_mini.syntax[i]))
			i = unex_token3(i);
	}
}

void	unex_token1(char *str)
{
	if (g_mini.syntax[0]
		&& ft_strchr("<|>;", g_mini.syntax[ft_strlen(str) - 1]))
	{
		manage_newline();
		if (!g_mini.is_error)
			unex_token2();
	}
	else
		unex_token2();
}

void	unex_token(char *str)
{
	g_mini.is_error = 0;
	g_mini.open_quote = false;
	g_mini.syntax = ft_strtrim((const char *)str, WHITESPACES);
	if (g_mini.syntax[0] && g_mini.syntax[0] == '|')
	{
		if (g_mini.syntax[1] && g_mini.syntax[1] == '|')
			print_error(NULL, NULL, UNEX_PIPES, SYNTAX_ERR);
		else
			print_error(NULL, NULL, UNEX_PIPE, SYNTAX_ERR);
	}
	if (g_mini.syntax[0] && g_mini.syntax[0] == ';')
	{
		if (g_mini.syntax[1] && g_mini.syntax[1] == ';')
			print_error(NULL, NULL, UNEX_SEMICS, SYNTAX_ERR);
		else
			print_error(NULL, NULL, UNEX_SEMIC, SYNTAX_ERR);
	}
	else
		unex_token1(str);
	free (g_mini.syntax);
}
