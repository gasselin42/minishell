/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:42:38 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/02 13:33:20 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*place_env(char *cmd, int *i)
{
	char	*tmp;
	char	*env;
	char	*var;
	int		j;

	*i = *i + 1;
	j = *i;
	while (cmd[*i] && ft_strchr(NAMESET, cmd[*i]))
		*i = *i + 1;
	var = ft_substr(cmd, j, (size_t)(*i - j));
	env = ft_getenv(var);
	free (var);
	var = ft_substr(cmd, 0, (size_t)(j - 1));
	if (env)
		tmp = ft_strjoin_triple(var, env, cmd + *i);
	else
		tmp = ft_strjoin(var, cmd + *i);
	*i = (int)(ft_strlen(var) + ft_strlen(env) - 1);
	free (cmd);
	free (var);
	return (tmp);
}

char	*place_code(char *cmd, int *i)
{
	char	*tmp;
	char	*debut;
	char	*code;

	debut = ft_substr(cmd, 0, (size_t)*i);
	code = ft_itoa((int)g_mini.output_code);
	tmp = ft_strjoin_triple(debut, code, cmd + *i + 2);
	*i = (int)(ft_strlen(debut) + ft_strlen(code) - 1);
	free (cmd);
	free (code);
	free (debut);
	return (tmp);
}

t_token	*manage_env(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	while (tmp != NULL)
	{
		i = -1;
		if (tmp->type != S_QUOTE && ft_strchr(tmp->cmd, '$'))
		{
			while (tmp->cmd[++i])
			{
				if (tmp->cmd[i] == '$' && tmp->cmd[i + 1]
					&& ft_strchr(NAMESET, tmp->cmd[i + 1]))
					tmp->cmd = place_env(tmp->cmd, &i);
				else if (tmp->cmd[i] == '$' && tmp->cmd[i + 1]
					&& tmp->cmd[i + 1] == '?')
					tmp->cmd = place_code(tmp->cmd, &i);
			}
		}
		if (tmp->next == NULL && tmp->pipe)
		{
			tmp = tmp->pipe;
			continue ;
		}
		tmp = tmp->next;
	}
	return (token);
}
