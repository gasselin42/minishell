/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:59:18 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/16 13:57:58 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_dot(char *line)
{
	if (ft_strcmp(line, ".") == 0)
	{
		print_error(NULL, ".", FILE_NAME_RQD, SYNTAX_ERR);
		return (true);
	}
	return (false);
}

void	print_error(const char *v1, const char *v2, const char *v3, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (v1)
	{
		ft_putstr_fd(v1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (v2)
	{
		ft_putstr_fd(v2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(v3, STDERR_FILENO);
	g_mini.output_code = code;
	g_mini.is_error = 1;
}
