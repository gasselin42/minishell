/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:29:29 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/25 11:35:32 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	verify_name(char **argv)
{
	int		i;
	char	**name;

	i = 0;
	while (argv[i])
	{
		name = ft_split(argv[i], '=');
		if (ft_isdigit(name[0][0]) || ft_count_char(name[0], NAMESET) \
			!= (int)ft_strlen(name[0]))
			print_error("export", name[0], NO_IDENT, GEN_ERR);
		else
		{
			if (name[1])
				ft_setenv(name[0], argv[i] + ft_strlen(name[0]) + 1, 1);
			else
				ft_setenv(name[0], NULL, 1);
		}
		ft_strarr_free(name);
		i++;
	}
}

void	ft_export(char **argv)
{
	char	**sort;
	int		i;

	i = -1;
	g_mini.output_code = SUCCESS;
	if (!argv[0])
	{
		sort = ft_strarr_dup(g_mini.env, 0);
		ft_strarr_sort(sort, g_mini.env_size);
		while (++i < g_mini.env_size)
			ft_putendl_fd(sort[i], STDOUT_FILENO);
	}
	else
		verify_name(argv);
}
