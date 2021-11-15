/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:30:36 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/15 11:27:49 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_nothing(int sig)
{
	(void)sig;
}

// void	ctrl_backslash(int sig)
// {
// 	(void)sig;
// 	printf("Quit");
// 	g_mini.output_code = CTRL_B;
// }

// void	ctrl_d(int sig)
// {
// 	(void)sig;
// 	printf("\n");
// 	g_mini.output_code = CTRL_D;
// }

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_mini.output_code = CTRL_C;
}

void	manage_signals(int status)
{
	if (WIFEXITED(status))
		g_mini.output_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putendl_fd("^C", 1);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit", 1);
	}
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
