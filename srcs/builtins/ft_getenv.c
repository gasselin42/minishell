/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:13:36 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/25 11:35:58 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_addenv(const char *name, const char *value)
{
	char	**env;
	char	*str;

	env = ft_strarr_dup(g_mini.env, 1);
	ft_strarr_free(g_mini.env);
	g_mini.env = env;
	g_mini.env[g_mini.env_size] = ft_strdup(name);
	if (value)
	{
		free (g_mini.env[g_mini.env_size]);
		str = ft_strjoin_triple(name, "=", value);
		g_mini.env[g_mini.env_size] = str;
	}
	g_mini.env[g_mini.env_size + 1] = NULL;
	g_mini.env_size = ft_strarr_size(g_mini.env);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	int		i;

	if (name == NULL || ft_strlen(name) == 0 || ft_strchr(name, '='))
		return (-1);
	if (ft_getenv(name) && overwrite == 0)
		return (0);
	if (ft_getenv(name) == NULL)
	{
		ft_addenv(name, value);
		return (0);
	}
	i = ft_strarr_index(g_mini.env, name, "=");
	if (value && overwrite)
	{
		free (g_mini.env[i]);
		g_mini.env[i] = ft_strjoin_triple(name, "=", value);
	}
	return (0);
}

char	*ft_getenv(const char *name)
{
	int		i;
	char	*str;
	size_t	size;

	i = 0;
	str = ft_strjoin(name, "=");
	size = ft_strlen(str);
	while (g_mini.env[i] != NULL)
	{
		if (ft_strncmp(g_mini.env[i], str, size) == 0)
		{
			free (str);
			return (g_mini.env[i] + size);
		}
		i++;
	}
	free (str);
	return (NULL);
}
