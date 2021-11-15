/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:29:29 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/15 16:05:31 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_split(char *str, int equal)
{
	char	**name;
	size_t	len;

	len = 0;
	if (equal)
	{
		name = ft_calloc(3, sizeof(char *));
		while (str[len] != '=')
			len++;
		name[0] = ft_substr(str, 0, len);
		name[1] = ft_strdup(ft_strnstr(str, "=", ft_strlen(str)) + 1);
	}
	else
	{
		name = ft_calloc(2, sizeof(char *));
		name[0] = ft_strdup(str);
	}
	return (name);
}

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
		name = ms_split(argv[i], equal);
		if (ft_isdigit(name[0][0]) || ft_count_char(name[0], NAMESET) \
			!= (int)ft_strlen(name[0]))
			print_error("export", name[0], NO_IDENT, GEN_ERR);
		else
		{
			if (ft_getenv(name[0]) && ft_strchr(argv[i], '=') && !name[1])
				reset_env(name, equal);
			else if (name[1] != NULL)
				ft_setenv(name[0], name[1], equal);
			else
				ft_setenv(name[0], NULL, equal);
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
		ft_strarr_sort(sort, g_mini.env_size);
		while (++i < g_mini.env_size)
			ft_putendl_fd(sort[i], STDOUT_FILENO);
	}
	else
		verify_name(argv);
}
