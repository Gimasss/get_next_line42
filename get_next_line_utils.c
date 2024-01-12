/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmastroc <gmastroc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:58:45 by gmastroc          #+#    #+#             */
/*   Updated: 2024/01/11 18:04:53 by gmastroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*dup;

	i = 0;
	size = ft_strlen(s);
	dup = malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int				i;
	char			*cat;
	char			*sc1;
	char			*sc2;

	i = 0;
	sc1 = (char *)s1;
	sc2 = (char *)s2;
	cat = ft_calloc((ft_strlen(sc1) + ft_strlen(sc2) + 1), sizeof(char));
	if (!cat)
		return (NULL);
	while (*sc1)
	{
		cat[i] = *sc1;
		i++;
		sc1++;
	}
	while (*sc2)
	{
		cat[i] = *sc2;
		i++;
		sc2++;
	}
	return (cat);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c > 127)
		c = c % 128;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			s_len;
	size_t			sub_len;
	unsigned char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	sub_len = s_len - start;
	sub = ft_calloc((sub_len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	return ((char *)sub);
}