/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:29:40 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/21 13:38:17 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	g_mini.output_code = SUCCESS;
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		print_error("pwd", NULL, strerror(errno), GEN_ERR);
		return ;
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
}
