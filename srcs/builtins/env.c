/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:29:13 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/11 13:57:34 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **argv)
{
	int	i;

	i = 0;
	g_mini.output_code = SUCCESS;
	if (argv[1])
	{
		print_error("env", NULL, ARGS_ERR, GEN_ERR);
		return ;
	}
	while (g_mini.env[i])
	{
		if (ft_strchr(g_mini.env[i], '='))
			ft_putendl_fd(g_mini.env[i], STDOUT_FILENO);
		i++;
	}
}
