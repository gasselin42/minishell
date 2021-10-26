/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:04:43 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/21 14:42:02 by gasselin         ###   ########.fr       */
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
		if (access(path, F_OK))
			return (path);
		free (path);
		i++;
	}
	return (NULL);
}

void	execute(char **cmd)
{
	g_mini.output_code = SUCCESS;
	if (execve(find_path(cmd[0]), cmd, g_mini.env) == -1)
		print_error(cmd[0], NULL, strerror(errno), errno);
}
