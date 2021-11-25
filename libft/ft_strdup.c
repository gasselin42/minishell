/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 09:13:38 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/25 11:19:51 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!str)
		return (NULL);
	str = ft_strcpy(str, s);
	return (str);
}
