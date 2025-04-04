/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:49 by smishos           #+#    #+#             */
/*   Updated: 2025/04/04 12:30:12 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_substrings(const char *str, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*str == c)
		str++;
	while (*str)
	{
		if (*str != c && in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		else if (*str == c)
			in_substring = 0;
		str++;
	}
	return (count);
}

char	*substring_create(const char *str, int start, int finish)
{
	char	*substr;
	int		i;

	i = 0;
	substr = (char *)malloc((finish - start + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (start < finish)
		substr[i++] = str[start++];
	substr[i] = '\0';
	return (substr);
}

void	free_result_array(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		result[j] = NULL;
		j--;
	}
	free(result);
	result = NULL;
}

int	split_string(char const *s, char c, char **result, int count)
{
	size_t	i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	while (j < count)
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || !s[i]) && index >= 0)
		{
			result[j] = substring_create(s, index, i);
			if (!result[j])
			{
				free_result_array(result, j);
				return (1);
			}
			index = -1;
			j++;
		}
		i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		split_check;
	char	**result;

	if (!s)
		return (NULL);
	count = count_substrings(s, c);
	if (count == 0)
	{
		return (NULL);
	}
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	split_check = split_string(s, c, result, count);
	if (split_check == 1)
	{
		return (NULL);
	}
	else
	{
		result[count] = NULL;
		return (result);
	}
}
