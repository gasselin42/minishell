/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:19:41 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/26 11:41:14 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_newline(char *syntax)
{
	size_t	i;

	i = ft_strlen(syntax) - 1;
	if (!ft_strchr_rev(syntax, syntax[i]))
	{
		if (i < 2)
			print_error(NULL, NULL, UNEX_NEWLINE, SYNTAX_ERR);
	}
	else if (ft_strchr("<|>", syntax[i]))
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

bool	manage_syntax(char *str)
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
		else
			manage_syntax2(trim);
		free (trim);
		return (true);
	}
	return (false);
}
