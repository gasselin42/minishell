/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:55:37 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/09 15:41:58 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_output(char *next) // >
{
	int	file;

	file = open(next, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	redir_append(char *next) // >>
{
	int	file;

	file = open(next, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	redir_input(char *next) // <
{
	int	file;

	file = open(next, O_RDONLY);
	dup2(file, STDIN_FILENO);
	close(file);
}

int	is_redirection(char	*cmd)
{
	return ((ft_strcmp(cmd, ">>") == 0) || (ft_strcmp(cmd, "<<") == 0)
		|| (ft_strcmp(cmd, ">") == 0) || (ft_strcmp(cmd, "<") == 0));
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

/* pour les redirection:
check si les redirections sont a NULL
sinon open le file mentionner
dup2 le file open au bon stdin 
ramene le saved_stdin

pour le here doc:
same mais tu prend les inputs dans le get_next_line*/
