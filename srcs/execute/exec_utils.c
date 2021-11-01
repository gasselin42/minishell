/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:04:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/01 16:32:15 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(const char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (g_mini.path[i])
	{
		path = ft_strjoin_triple(g_mini.path[i], "/", cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	return (NULL);
}

void	execute(char **cmd)
{
	g_mini.output_code = SUCCESS;
	if (ft_strchr(cmd[0], '/'))
		print_error(NULL, cmd[0], NO_FLDIR, FILE_ERR);
	else if (execve(find_path(cmd[0]), cmd, g_mini.env) == -1)
		print_error(cmd[0], NULL, strerror(errno), errno);
}

int	define_size(t_token *token)
{
	int		size;
	t_token	*tmp;

	size = 0;
	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->over == DONE)
			size++;
		tmp = tmp->next;
	}
	return (size + 1);
}

char	**merge_tokens(t_token *token)
{
	char	**merge;
	t_token	*tmp;
	int		i;
	char	*str;
	char	*str2;

	tmp = token;
	i = 0;
	merge = malloc(sizeof(char *) * define_size(token));
	while (tmp != NULL)
	{
		str = ft_strdup("");
		while (tmp->over != DONE)
		{
			str2 = ft_strjoin(str, tmp->cmd);
			free (str);
			str = str2;
			tmp = tmp->next;
		}
		str2 = ft_strjoin(str, tmp->cmd);
		free (str);
		merge[i++] = ft_strdup(str2);
		free (str2);
		tmp = tmp->next;
	}
	merge[i] = NULL;
	return (merge);
}
