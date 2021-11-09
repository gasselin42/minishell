/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:56:09 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/08 11:01:57 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_append(char *str, int c)
{
	char	*line;
	int		i;

	i = -1;
	if (str == NULL)
	{
		line = ft_calloc(2, sizeof(char));
		line[0] = c;
		return (line);
	}
	line = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while (str[++i])
		line[i] = str[i];
	line[i] = c;
	free (str);
	return (line);
}
