/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:08:29 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/20 14:47:16 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarr_index(char **arr, const char *str, const char *sep)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], str, ft_strlen(str)) == 0)
		{
			if (!(arr[i][ft_strlen(str)])
				|| ft_strchr(sep, arr[i][ft_strlen(str)]))
				return (i);
		}
		i++;
	}
	if (str == NULL)
		return (i);
	return (-1);
}