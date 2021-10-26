/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:38:08 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/21 13:37:34 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_env(void)
{
	int		i;
	char	*pwd;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		print_error("cd", NULL, strerror(errno), GEN_ERR);
		return ;
	}
	pwd = ft_getenv("PWD");
	if (pwd)
		ft_setenv("OLDPWD", pwd, 1);
	ft_setenv("PWD", cwd, 1);
	free (cwd);
}

void	ft_cd(char **argv)
{
	g_mini.output_code = SUCCESS;
	if (!argv[1])
	{
		if (ft_getenv("HOME") == NULL)
			print_error("cd", NULL, NO_HOME, GEN_ERR);
		else if (chdir(ft_getenv("HOME=")) == -1)
			print_error("cd", ft_getenv("HOME"), strerror(errno), GEN_ERR);
		else
			modify_env();
	}
	else
	{
		if (argv[2])
			print_error("cd", NULL, ARGS_ERR, GEN_ERR);
		else if (chdir(argv[1]) == -1)
			print_error("cd", argv[1], strerror(errno), GEN_ERR);
		else
			modify_env();
	}
}
