/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:29:03 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/02 13:37:28 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo2(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (!argv[i])
			break ;
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

void	ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && ft_strncmp("-n", argv[i], 2) == 0)
	{
		if (ft_strchr_rev(argv[i] + 1, 'n') != NULL)
			break ;
		newline = 0;
		i++;
	}
	ft_echo2(argv, i);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
