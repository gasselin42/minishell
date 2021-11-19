/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:42:38 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/19 15:31:52 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*place_env2(char *var, t_type type, t_token *token, int j)
{
	char	*env;
	char	**split;
	char	*ret;
	char	*tmp;
	int		i;

	i = -1;
	(void)token;
	if (ft_getenv(var) == NULL)
		return (NULL);
	env = ft_strdup(ft_getenv(var));
	if (type == D_QUOTE)
		return (env);
	split = ft_split(env, ' ');
	ret = ft_strdup("");
	if (env[0] == ' ' && j > 2)
	{
		tmp = ft_strjoin(ret, " ");
		free (ret);
		ret = ft_strdup(tmp);
		free (tmp); 
	}
	while (split[++i + 1])
	{
		tmp = ft_strjoin_triple(ret, split[i], " ");
		free (ret);
		ret = ft_strdup(tmp);
		free (tmp); 
	}
	tmp = ft_strjoin(ret, split[i]);
	free (ret);
	ret = ft_strdup(tmp);
	free (tmp);
	if ((token->cmd[j] && env[ft_strlen(env) - 1] == ' ')
		|| (token->over == CONTINUE && (token->next->type == S_QUOTE || token->next->type == D_QUOTE)))
	{
		tmp = ft_strjoin(ret, " ");
		free (ret);
		ret = ft_strdup(tmp);
		free (tmp);
	}
	free (env);
	ft_strarr_free(split);
	return (ret);
}

/*
export A='   bonjour   je   suis  splited '
echo $A -> 'bonjour je suis splited'
echo Allo$A -> 'Allo bonjour je suis splited'
echo $A"ALLO" -> 'bonjour je suis splited ALLO'
*/

char	*place_env(char *cmd, int *i, t_type type, t_token *token)
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
	env = place_env2(var, type, token, *i);
	free (var);
	var = ft_substr(cmd, 0, (size_t)(j - 1));
	if (env)
		tmp = ft_strjoin_triple(var, env, cmd + *i);
	else
		tmp = ft_strjoin(var, cmd + *i);
	*i = (int)(ft_strlen(var) + ft_strlen(env) - 1);
	if (env)
		free (env);
	free (cmd);
	free (var);
	return (tmp);
}

char	*place_code(char *cmd, int *i)
{
	char	*tmp;
	char	*debut;
	char	*code;

	debut = ft_substr(cmd, 0, *i);
	code = ft_itoa((int)g_mini.output_code);
	tmp = ft_strjoin_triple(debut, code, cmd + *i + 2);
	*i = (int)(ft_strlen(debut) + ft_strlen(code) - 1);
	free (cmd);
	free (code);
	free (debut);
	return (tmp);
}

void	manage_dollar(t_token **tmp, t_type type)
{
	int	i;

	i = -1;
	while ((*tmp)->cmd[++i])
	{
		if ((*tmp)->cmd[i] == '$' && (*tmp)->cmd[i + 1]
			&& ft_strchr(NAMESET, (*tmp)->cmd[i + 1]))
			(*tmp)->cmd = place_env((*tmp)->cmd, &i, type, (*tmp));
		else if ((*tmp)->cmd[i] == '$' && (*tmp)->cmd[i + 1]
			&& (*tmp)->cmd[i + 1] == '?')
			(*tmp)->cmd = place_code((*tmp)->cmd, &i);
	}
}

t_token	*manage_env(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type != S_QUOTE && ft_strchr(tmp->cmd, '$'))
			manage_dollar(&tmp, tmp->type);
		if (tmp->next == NULL && tmp->pipe)
		{
			tmp = tmp->pipe;
			continue ;
		}
		tmp = tmp->next;
	}
	return (token);
}
