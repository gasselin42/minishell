/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:55:37 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/22 15:55:22 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_output(char *next)
{
	int	file;

	file = open(next, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	redir_append(char *next)
{
	int	file;

	file = open(next, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	redir_input(char *next)
{
	int	file;

	file = open(next, O_RDONLY);
	if (file == -1)
	{
		print_error(next, NULL, NO_FLDIR, GEN_ERR);
		return ;
	}
	dup2(file, STDIN_FILENO);
	close(file);
}

int	count_redirs(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == REDIR_L || token->type == REDIR_R
			|| token->type == APPEND || token->type == HEREDOC)
			count += 2;
		token = token->next;
	}
	return (count);
}

void	init_redirs(t_job *jobs)
{
	int	i;

	i = 0;
	g_mini.is_error = 0;
	if (jobs->redirs)
	{
		while (jobs->redirs[i])
		{
			if (ft_strcmp(jobs->redirs[i], ">>") == 0)
				redir_append(jobs->redirs[i + 1]);
			else if (ft_strcmp(jobs->redirs[i], "<<") == 0)
				hdoc_write(jobs);
			else if (ft_strcmp(jobs->redirs[i], ">") == 0)
				redir_output(jobs->redirs[i + 1]);
			else if (ft_strcmp(jobs->redirs[i], "<") == 0)
				redir_input(jobs->redirs[i + 1]);
			i += 2;
		}
	}
}
