/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:23:28 by smishos           #+#    #+#             */
/*   Updated: 2025/04/04 13:05:37 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	actually_exit(t_ms *shell)
{
	if (shell->pipe_count == 0)
	{
		cleanup(shell, 1);
		exit(shell->exit_code);
	}
	return (1);
}

long long	msatol(const char *str)
{
	int			i;
	long long	sign;
	long long	ret;
	long long	check;

	i = 0;
	sign = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = sign * -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = ret;
		ret = (ret * 10) + (str[i++] - 48);
		if (check > ret && sign == 1)
			return (-1);
		if (check > ret && sign == -1)
			return (-1);
	}
	return (ret * sign);
}
