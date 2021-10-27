/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:03:49 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/27 16:13:02 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	verify_quotes(const char *str)
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

void	manage_newline(void)
{
	size_t	i;
	
	i = ft_strlen(g_mini.syntax) - 1;
	if (!ft_strchr_rev(g_mini.syntax, g_mini.syntax[i]))
	{
		if (i < 2)
			print_error(NULL, NULL, UNEX_NEWLINE, SYNTAX_ERR);
	}
	else if (ft_strchr("<|>", g_mini.syntax[i]))
		print_error(NULL, NULL, UNEX_NEWLINE, SYNTAX_ERR);
}

int	manage_syntax2(char *str)
{
	char	*trim;
	int		i;
	
	trim = ft_strtrim((const char *)str + 1, WHITESPACES);
	i = (int)(ft_strlen(str) - ft_strlen(trim));
	if (trim[0] == '|' && trim[1] == '|')
		print_error(NULL, NULL, UNEX_PIPES, SYNTAX_ERR);
	else if (trim[0] == '|')
		print_error(NULL, NULL, UNEX_PIPE, SYNTAX_ERR);
	else if (trim[0] == '<' && trim[1] == '>')
		print_error(NULL, NULL, UNEX_REDIRS_LR, SYNTAX_ERR);
	else if (trim[0] == '>' && trim[1] == '>')
		print_error(NULL, NULL, UNEX_REDIRS_R, SYNTAX_ERR);
	else if (trim[0] == '>')
		print_error(NULL, NULL, UNEX_REDIR_R, SYNTAX_ERR);
	else if (trim[0] == '<' && trim[1] == '<')
		print_error(NULL, NULL, UNEX_REDIRS_L, SYNTAX_ERR);
	else if (trim[0] == '<')
		print_error(NULL, NULL, UNEX_REDIR_L, SYNTAX_ERR);
	else if (trim[0] == ';' && trim[1] == ';')
		print_error(NULL, NULL, UNEX_SEMICS, SYNTAX_ERR);
	else if (trim[0] == ';')
		print_error(NULL, NULL, UNEX_SEMIC, SYNTAX_ERR);
	free (trim);
	return (i);
}

void	manage_syntax(char *str)
{
	char	*trim;
	
	if ((str[0] == '<' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<')
		|| (str[0] == '>' && str[1] == '>'))
	{
		trim = ft_strtrim((const char *)str + 2, WHITESPACES);
		if (str[0] == '<' && str[1] == '>' && !ft_strchr("<|>", trim[0]))
			print_error(NULL, NULL, UNEX_REDIRS_LR, SYNTAX_ERR);
		else if (trim[0] == '|' && trim[1] == '|')
			print_error(NULL, NULL, UNEX_PIPES, SYNTAX_ERR);
		else if (trim[0] == '|')
			print_error(NULL, NULL, UNEX_PIPE, SYNTAX_ERR);
		else if (trim[0] == '<' && trim[1] == '>')
			print_error(NULL, NULL, UNEX_REDIRS_LR, SYNTAX_ERR);
		else if (trim[0] == '>' && trim[1] == '>')
			print_error(NULL, NULL, UNEX_REDIRS_R, SYNTAX_ERR);
		else if (trim[0] == '>')
			print_error(NULL, NULL, UNEX_REDIR_R, SYNTAX_ERR);
		else if (trim[0] == '<' && trim[1] == '<')
			print_error(NULL, NULL, UNEX_REDIRS_L, SYNTAX_ERR);
		else if (trim[0] == '<')
			print_error(NULL, NULL, UNEX_REDIR_L, SYNTAX_ERR);
		else if (trim[0] == ';' && trim[1] == ';')
			print_error(NULL, NULL, UNEX_SEMICS, SYNTAX_ERR);
		else if (trim[0] == ';')
			print_error(NULL, NULL, UNEX_SEMIC, SYNTAX_ERR);
		free (trim);
	}
}

void	unex_token2(void)
{
	int	i;
	
	i = -1;
	while (g_mini.syntax[++i] && !g_mini.is_error)
	{
		if (g_mini.open_quote == false && (g_mini.syntax[i] == 34 || g_mini.syntax[i] == 39))
		{
			g_mini.open_quote = true;
			g_mini.char_quote = g_mini.syntax[i];
		}
		else if (g_mini.open_quote == true && g_mini.syntax[i] == g_mini.char_quote)
			g_mini.open_quote = false;
		else if (!g_mini.open_quote && ft_strchr(SYNTAX, g_mini.syntax[i]))
		{
			manage_syntax(g_mini.syntax + i);
			if (g_mini.is_error == 0)
				i += manage_syntax2(g_mini.syntax + i);
		}
	}
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
	else if (g_mini.syntax[0] && ft_strchr("<|>;", g_mini.syntax[ft_strlen(str) - 1]))
	{
		manage_newline();
		if (!g_mini.is_error)
			unex_token2();
	}
	else
		unex_token2();
	free (g_mini.syntax);
}
