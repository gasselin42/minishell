/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:55:37 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/02 14:15:47 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_output(t_token *token) // >
{
	int	file;

	file = open(token->next->cmd, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	redir_append(t_token *token) // >>
{
	int	file;

	file = open(token->next->cmd, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	redir_input(t_token *token) // <
{
	int	file;

	file = open(token->next->cmd, O_RDONLY);
	dup2(file, STDIN_FILENO);
	close(file);
}

void	redir_heredocs(t_token *token) // <<
{
	
}
