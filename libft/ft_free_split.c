/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:06:10 by thedapperfo       #+#    #+#             */
/*   Updated: 2025/03/28 17:45:08 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **split_array)
{
	int	i;

	i = 0;
	if (!split_array)
		return ;
	if (split_array != NULL)
	{
		while (split_array[i] != NULL)
		{
			free(split_array[i]);
			split_array[i] = NULL;
			i++;
		}
		free(split_array);
		split_array = NULL;
	}
}
