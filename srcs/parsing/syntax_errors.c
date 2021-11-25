/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:03:49 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/25 16:21:48 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	verify_quotes(char *str)
{
	int			i;
	t_quotes	quotes;

	i = 0;
	quotes = init_quotes(false, 0);
	while (str[i])
	{
		if (quotes.open_quote == false && (str[i] == 34 || str[i] == 39))
		{
			quotes.open_quote = true;
			quotes.char_quote = str[i];
		}
		else if (quotes.open_quote == true && str[i] == quotes.char_quote)
			quotes.open_quote = false;
		i++;
	}
	if (quotes.open_quote)
		print_error(NULL, NULL, QUOTES, SYNTAX_ERR);
	return (quotes.open_quote);
}

int	unex_token3(int i)
{
	bool	dbl_redir;

	dbl_redir = manage_syntax(g_mini.syntax + i);
	if (g_mini.is_error == 0 && !dbl_redir)
		i += manage_syntax3(g_mini.syntax + i);
	return (i);
}

void	unex_token2(void)
{
	int			i;
	t_quotes	quotes;

	i = -1;
	quotes = init_quotes(false, 0);
	while (g_mini.syntax[++i] && !g_mini.is_error)
	{
		if (quotes.open_quote == false && (g_mini.syntax[i] == 34
				|| g_mini.syntax[i] == 39))
		{
			quotes.open_quote = true;
			quotes.char_quote = g_mini.syntax[i];
		}
		else if (quotes.open_quote == true
			&& g_mini.syntax[i] == quotes.char_quote)
			quotes.open_quote = false;
		else if (!quotes.open_quote && ft_strchr(SYNTAX, g_mini.syntax[i]))
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
