/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:08:57 by smishos           #+#    #+#             */
/*   Updated: 2025/03/30 15:14:58 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parent_wait(t_ms *shell, t_command *command, int *pipefd)
{
	int	check_pid;

	check_pid = 1;
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (command->redir_out)
		write_file(shell, command->command_input[2]);
	while (check_pid > 0)
		check_pid = waitpid(-1, NULL, 0);
}

int	run_builtin(t_ms *shell, char **command, \
	void (*function)(char **, t_ms *))
{
	function(command, shell);
	return (1);
}

t_command	*check_for_dots(t_command *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	command = command->next;
	return (command);
}
