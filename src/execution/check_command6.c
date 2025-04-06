/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:39 by smishos           #+#    #+#             */
/*   Updated: 2025/04/06 16:33:51 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*check_for_dot(t_ms *shell, t_command *command)
{
	ft_putstr_fd("minishell: .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	shell->exit_code = 2;
	shell->select_command_found = 1;
	command = command->next;
	return (command);
}

int	is_dir(char *str)
{
	int		fd3;

	fd3 = open(str, O_DIRECTORY);
	if (fd3 != -1)
	{
		close(fd3);
		return (1);
	}
	return (0);
}

void	error_free_clean_exit(t_ms *shell, char *message)
{
	perror(message);
	free(shell->commands->heredoc_line);
	cleanup(shell, 1);
	exit(EXIT_FAILURE);
}
