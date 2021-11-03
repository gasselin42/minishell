/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:55:37 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/03 11:28:44 by gasselin         ###   ########.fr       */
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

// void	redir_heredocs(t_token *token) // <<
// {
// 	(void)token;
// }

/* pour les redirection:
check si les redirections sont a NULL
sinon open le file mentionner
dup2 le file open au bon stdin 
ramene le saved_stdin

pour le here doc:
same mais tu prend les inputs dans le get_next_line

est-ce que le pipe prend le dessus sur la redir ou l'inverse? */
