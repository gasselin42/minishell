/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:04:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/10 10:59:11 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(const char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	if (g_mini.path != NULL)
	{
		while (g_mini.path[i])
		{
			path = ft_strjoin_triple(g_mini.path[i], "/", cmd);
			if (access(path, F_OK) == 0)
				return (path);
			free (path);
			i++;
		}
	}
	return (NULL);
}

void	verify_dir(char **cmd)
{
	struct stat	info;
	
	stat(cmd[0], &info);
	if (S_ISDIR(info.st_mode))
	{
		dup2(g_mini.fdin, 0);
		dup2(g_mini.fdout, 1);
		print_error(NULL, cmd[0], DIRECTORY, DIR_ERR);
		exit (1);
	}
	return ;
}

void	execute(char **cmd)
{
	g_mini.output_code = SUCCESS;
	g_mini.path_exec = find_path(cmd[0]);
	if (g_mini.path_exec == NULL)
	{
		print_error(NULL, cmd[0], NO_FLDIR, FILE_ERR);
		exit (0);
	}
	if (ft_strchr(cmd[0], '/'))
		verify_dir(cmd);
	execve(cmd[0], cmd, g_mini.env);
	if (ft_strchr(cmd[0], '/'))
		print_error(NULL, cmd[0], NO_FLDIR, FILE_ERR);
	else if (execve(g_mini.path_exec, cmd, g_mini.env) == -1)
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
		if (tmp->over == DONE && !(tmp->type == TEXT && tmp->cmd[0] == '\0'
			&& (!tmp->prev || tmp->prev->over == DONE)))
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
		if (!(tmp->over == DONE && !(tmp->type == TEXT && tmp->cmd[0] == '\0'
			&& (!tmp->prev || tmp->prev->over == DONE))))
		{
			tmp = tmp->next;
			continue ;
		}
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

char	*merge_cmd(char **merge)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	line = NULL;
	if (merge && *merge)
	{
		line = ft_strdup(merge[0]);
		while (merge[++i])
		{
			tmp = ft_strjoin_triple(line, " ", merge[i]);
			free (line);
			line = ft_strdup(tmp);
			free (tmp);
		}
	}
	return (line);
}

t_token	*init_merge(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		tmp->merge = merge_tokens(tmp);
		tmp->merge_cmd = merge_cmd(tmp->merge);
		tmp = tmp->pipe;
	}
	return (token);
}
