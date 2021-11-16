/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:40:08 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/16 13:20:31 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char	*cmd)
{
	return ((ft_strcmp(cmd, ">>") == 0) || (ft_strcmp(cmd, "<<") == 0)
		|| (ft_strcmp(cmd, ">") == 0) || (ft_strcmp(cmd, "<") == 0));
}

bool	check_level(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (false);
	return (true);
}

bool	is_level_numeric(int *lvl)
{
	char	*value;

	value = ft_getenv("SHLVL");
	if (!value[0])
		return (false);
	if (!check_level(value))
		return (false);
	*lvl = ft_atoi(value);
	return (true);
}

void	change_level(void)
{
	int		lvl;
	char	*nb;

	if (ft_getenv("SHLVL") && is_level_numeric(&lvl))
	{
		nb = ft_itoa(lvl + 1);
		ft_setenv("SHLVL", nb, 1);
		free (nb);
	}
}
