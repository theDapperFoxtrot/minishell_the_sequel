/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:01:20 by saylital          #+#    #+#             */
/*   Updated: 2025/03/28 21:41:41 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_line(char *string, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*words;

	i = ft_strlennl(string) + ft_strlennl(buffer);
	j = 0;
	words = malloc((i + 1) * sizeof(char));
	if (words == NULL)
		return (NULL);
	i = 0;
	if (string)
	{
		while (string[i] != '\0')
		{
			words[i] = string[i];
			i++;
		}
	}
	while (buffer[j] != '\0')
	{
		words[i + j] = buffer[j];
		j++;
	}
	words[i + j] = '\0';
	return (words);
}

char	*ft_strchrnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup_newline(char *s1)
{
	size_t	i;
	size_t	j;
	char	*word;

	if (!s1)
		return (NULL);
	i = ft_strlen_newline(s1);
	j = 0;
	word = malloc((i + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (s1[j] != '\0' && s1[j] != '\n')
	{
		word[j] = s1[j];
		j++;
	}
	if (s1[j] == '\n')
	{
		word[j] = s1[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

size_t	ft_strlen_newline(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	if (str[i] == '\n')
		i++;
	return (i);
}

size_t	ft_strlennl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
