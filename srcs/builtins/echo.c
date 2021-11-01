/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:29:03 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/26 10:27:42 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo2(char **argv, int i)
{
	while (argv[i])
	{
		if (argv[i][0] == '$' && argv[i][1] == '?' && !argv[i][2])
			ft_putnbr_fd((int)g_mini.output_code, STDOUT_FILENO);
		else	
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

	i = 0;
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
