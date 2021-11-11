/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:30:36 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/11 14:31:10 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_backslash(int sig)
{
	(void)sig;
	printf("Quit");
	g_mini.output_code = CTRL_B;
}

void	ctrl_d(int sig)
{
	(void)sig;
	printf("\n");
	g_mini.output_code = CTRL_D;
}

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_mini.output_code = CTRL_C;
}
