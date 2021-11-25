/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:27:22 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/25 10:33:27 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_entry(int i)
{
	char	**arr;
	int		j;
	int		k;

	j = 0;
	k = 0;
	arr = (char **)ft_calloc(ft_strarr_size(g_mini.env), sizeof(char *));
	while (j < ft_strarr_size(g_mini.env))
	{
		if (j != i)
			arr[k++] = ft_strdup(g_mini.env[j]);
		j++;
	}
	ft_strarr_free(g_mini.env);
	g_mini.env = arr;
	g_mini.env_size = ft_strarr_size(g_mini.env);
}

void	ft_unset(char **argv)
{
	int	i;
	int	j;

	i = 0;
	g_mini.output_code = SUCCESS;
	while (argv[i])
	{
		if (ft_isdigit(argv[i][0]) || ft_count_char(argv[i], NAMESET) \
			!= (int)ft_strlen(argv[i]))
			print_error("unset", argv[i], NO_IDENT, GEN_ERR);
		else if (ft_strarr_index(g_mini.env, argv[i], "=") >= 0)
		{
			j = ft_strarr_index(g_mini.env, argv[i], "=");
			delete_entry(j);
		}
		i++;
	}
}
