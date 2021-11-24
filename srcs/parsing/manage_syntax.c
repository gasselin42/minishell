/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:19:41 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/22 16:02:05 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	manage_syntax3(char *str)
{
	char	*trim;
	int		i;

	trim = ft_strtrim((const char *)str + 1, WHITESPACES);
	i = (int)(ft_strlen(str) - ft_strlen(trim));
	if (str[0] == '|')
		;
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
	free (trim);
	return (i);
}

void	manage_syntax2(char *trim)
{
	if (trim[0] == '>')
		print_error(NULL, NULL, UNEX_REDIR_R, SYNTAX_ERR);
	else if (trim[0] == '<' && trim[1] == '<')
		print_error(NULL, NULL, UNEX_REDIRS_L, SYNTAX_ERR);
	else if (trim[0] == '<')
		print_error(NULL, NULL, UNEX_REDIR_L, SYNTAX_ERR);
	else if (trim[0] == ';' && trim[1] == ';')
		print_error(NULL, NULL, UNEX_SEMICS, SYNTAX_ERR);
	else if (trim[0] == ';')
		print_error(NULL, NULL, UNEX_SEMIC, SYNTAX_ERR);
}

void	manage_syntax(char *str)
{
	char	*trim;

	if ((str[0] == '<' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<')
		|| (str[0] == '>' && str[1] == '>'))
	{
		g_mini.dbl_redir = true;
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
		else
			manage_syntax2(trim);
		free (trim);
	}
}
