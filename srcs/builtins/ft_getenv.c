/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:13:36 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/24 17:32:12 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*place_env3(t_token *token, t_env env)
{
	while (env.split[++(env.i) + 1])
	{
		env.tmp = ft_strjoin_triple(env.ret, env.split[env.i], " ");
		free (env.ret);
		env.ret = ft_strdup(env.tmp);
		free (env.tmp);
	}
	env.tmp = ft_strjoin(env.ret, env.split[env.i]);
	free (env.ret);
	env.ret = ft_strdup(env.tmp);
	free (env.tmp);
	if (env.env[ft_strlen(env.env) - 1] == ' ' && (token->cmd[env.j]
			|| token->over == CONTINUE))
	{
		env.tmp = ft_strjoin(env.ret, " ");
		free (env.ret);
		env.ret = ft_strdup(env.tmp);
		free (env.tmp);
	}
	free (env.env);
	ft_strarr_free(env.split);
	return (env.ret);
}

char	*place_env2(char *var, t_type type, t_token *token, int j)
{
	t_env	env;

	env.i = -1;
	env.j = j;
	if (ft_getenv(var) == NULL)
		return (NULL);
	env.env = ft_strdup(ft_getenv(var));
	if (type == D_QUOTE)
		return (env.env);
	if (ft_strcmp(env.env, "") == 0)
		env.split = split_null();
	else
		env.split = ft_split(env.env, ' ');
	env.ret = ft_strdup("");
	if (env.env[0] == ' ' && env.j > 2
		&& ft_strlen(token->cmd) != ft_strlen(var) + 1)
	{
		env.tmp = ft_strjoin(env.ret, " ");
		free (env.ret);
		env.ret = ft_strdup(env.tmp);
		free (env.tmp);
	}
	return (place_env3(token, env));
}

void	ft_addenv(const char *name, const char *value, int equal)
{
	char	**env;
	char	*str;

	env = ft_strarr_dup(g_mini.env, 1);
	ft_strarr_free(g_mini.env);
	g_mini.env = env;
	g_mini.env[ft_strarr_size(g_mini.env)] = ft_strdup(name);
	if (equal)
	{
		str = ft_strjoin_triple(name, "=", value);
		free (g_mini.env[ft_strarr_size(g_mini.env) - 1]);
		g_mini.env[ft_strarr_size(g_mini.env) - 1] = ft_strdup(str);
		free (str);
	}
	g_mini.env_size = ft_strarr_size(g_mini.env);
}

int	ft_setenv(const char *name, const char *value, int equal)
{
	int		i;

	if (name == NULL || ft_strlen(name) == 0 || ft_strchr(name, '='))
		return (-1);
	if (ft_getenv(name) && equal == 0)
		return (0);
	if (ft_getenv(name) == NULL)
	{
		ft_addenv(name, value, equal);
		return (0);
	}
	i = ft_strarr_index(g_mini.env, name, "=");
	if (equal)
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
		if (ft_strncmp(g_mini.env[i], name, size) == 0
			|| ft_strncmp(g_mini.env[i], str, size) == 0)
		{
			free (str);
			return (g_mini.env[i] + size);
		}
		i++;
	}
	free (str);
	return (NULL);
}
