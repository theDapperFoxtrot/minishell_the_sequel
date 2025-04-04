/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:54:03 by saylital          #+#    #+#             */
/*   Updated: 2025/03/28 21:42:08 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*get_string(char *string, char *buffer, int fd)
{
	int		i;
	char	*temp;

	i = 1;
	while (i != 0 && !ft_strchrnl(string, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			if (string)
			{
				free(string);
				string = NULL;
			}
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		temp = string;
		string = ft_strjoin_line(string, buffer);
		free(temp);
	}
	free(buffer);
	return (string);
}

static	char	*find_newline(char *string)
{
	int		i;
	int		j;
	char	*save_str;

	i = ft_strlen_newline(string);
	j = 0;
	while (string[i + j] != '\0')
		j++;
	save_str = malloc((j + 1) * sizeof(char));
	if (!save_str)
	{
		free(string);
		return (NULL);
	}
	j = 0;
	while (string[i + j] != '\0')
	{
		save_str[j] = string[i + j];
		j++;
	}
	save_str[j] = '\0';
	free(string);
	return (save_str);
}

static	void	freestring(char **str)
{
	free(*str);
	*str = NULL;
}

char	*get_next_line(int fd)
{
	static char	*store_str;
	char		*newline_str;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		freestring(&store_str);
		return (NULL);
	}
	store_str = get_string(store_str, buffer, fd);
	if (!store_str)
		return (NULL);
	if (ft_strlennl(store_str) == 0)
		freestring(&store_str);
	newline_str = ft_strdup_newline(store_str);
	if (!newline_str)
	{
		freestring(&store_str);
		return (NULL);
	}
	store_str = find_newline(store_str);
	return (newline_str);
}
