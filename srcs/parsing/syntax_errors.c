/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:03:49 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/26 15:55:04 by gasselin         ###   ########.fr       */
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

bool	unexpected_token(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && (ft_iswhitespace(line[i]) || line[i] == '<'
		|| line[i] == '>' || line[i] == '|' || line[i] == ';'))
	{
		if (line[i] == '|' || line[i] == ';')
		{
			if (line[i] == '|')
				print_error(NULL, NULL, UNEX_PIPE, SYNTAX_ERR);
			if (line[i] == ';')
				print_error(NULL, NULL, UNEX_SEMIC, SYNTAX_ERR);
			return (false);
		}
	}
	return (true);
}
