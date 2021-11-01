/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_triple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:31:49 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/20 11:48:51 by gasselin         ###   ########.fr       */
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
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_triple(const char *s1, const char *s2, const char *s3)
{
	size_t	size;
	char	*str;

	if (s1 && s2 && s3)
	{
		size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
		str = (char *)malloc(size * sizeof(char));
		if (!str)
			return (NULL);
		ft_strcpy(str, s1);
		ft_strcpy(str + ft_strlen(s1), s2);
		ft_strcpy(str + ft_strlen(str), s3);
		return (str);
	}
	return (NULL);
}