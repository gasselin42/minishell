/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:03:49 by gasselin          #+#    #+#             */
/*   Updated: 2021/12/06 14:31:20 by gasselin         ###   ########.fr       */
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

int	unex_token3(int i, char *syntax)
{
	bool	dbl_redir;

	dbl_redir = manage_syntax(syntax + i);
	if (g_mini.is_error == 0 && !dbl_redir)
		i += manage_syntax3(syntax + i);
	return (i);
}

void	unex_token2(char *syntax)
{
	int			i;
	t_quotes	quotes;

	i = -1;
	quotes = init_quotes(false, 0);
	while (syntax[++i] && !g_mini.is_error)
	{
		if (quotes.open_quote == false && (syntax[i] == 34
				|| syntax[i] == 39))
		{
			quotes.open_quote = true;
			quotes.char_quote = syntax[i];
		}
		else if (quotes.open_quote == true && syntax[i] == quotes.char_quote)
			quotes.open_quote = false;
		else if (!quotes.open_quote && ft_strchr(SYNTAX, syntax[i]))
			i = unex_token3(i, syntax);
	}
}

void	unex_token1(char *str, char *syntax)
{
	if (syntax[0] && ft_strchr("<|>;", syntax[ft_strlen(str) - 1]))
	{
		manage_newline(syntax);
		if (!g_mini.is_error)
			unex_token2(syntax);
	}
	else
		unex_token2(syntax);
}

void	unex_token(char *str)
{
	char	*syntax;

	g_mini.is_error = 0;
	syntax = ft_strtrim((const char *)str, WHITESPACES);
	if (syntax[0] && syntax[0] == '|')
	{
		if (syntax[1] && syntax[1] == '|')
			print_error(NULL, NULL, UNEX_PIPES, SYNTAX_ERR);
		else
			print_error(NULL, NULL, UNEX_PIPE, SYNTAX_ERR);
	}
	else
		unex_token1(str, syntax);
	free (syntax);
}
