/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:59:18 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/21 10:55:07 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(const char *v1, const char *v2, const char *v3, int code)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	if (v1)
	{
		ft_putstr_fd(v1, STDOUT_FILENO);
		ft_putstr_fd(": ", STDOUT_FILENO);
	}
	if (v2)
	{
		ft_putstr_fd(v2, STDOUT_FILENO);
		ft_putstr_fd(": ", STDOUT_FILENO);
	}
	ft_putendl_fd(v3, STDOUT_FILENO);
	g_mini.output_code = code;
}
