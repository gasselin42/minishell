/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:29:29 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/26 11:47:33 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	verify_name(char **argv)
{
	int		i;
	char	**name;
	int		equal;

	i = 0;
	while (argv[++i])
	{
		equal = 1;
		if (!ft_strchr(argv[i], '='))
			equal = 0;
		name = ft_split(argv[i], '=');
		if (ft_isdigit(name[0][0]) || ft_count_char(name[0], NAMESET) \
			!= (int)ft_strlen(name[0]))
			print_error("export", argv[i], NO_IDENT, GEN_ERR);
		else
		{
			if (ft_getenv(name[0]) && ft_strchr(argv[i], '=') && !name[1])
				reset_env(name, equal);
			else if (name[1] != NULL)
				ft_setenv(name[0], argv[i] + ft_strlen(name[0]) + 1, equal);
			else
				ft_setenv(name[0], "", equal);
		}
		ft_strarr_free(name);
	}
}

void	ft_export(char **argv)
{
	char	**sort;
	int		i;

	i = -1;
	g_mini.output_code = SUCCESS;
	if (!argv[1])
	{
		sort = ft_strarr_dup(g_mini.env, 0);
		ft_strarr_sort(sort, ft_strarr_size(g_mini.env));
		while (sort[++i])
			ft_putendl_fd(sort[i], STDOUT_FILENO);
		ft_strarr_free(sort);
	}
	else
		verify_name(argv);
}
