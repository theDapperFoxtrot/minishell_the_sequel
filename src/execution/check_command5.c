/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:08:57 by smishos           #+#    #+#             */
/*   Updated: 2025/04/01 18:49:59 by smishos          ###   ########.fr       */
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

char	*cmd_not_found(char *splitted_args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(splitted_args, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

void	perm_den_exit(char *executable_path)
{
	ft_putendl_fd("minishell: Permission denied:", 2);
	free(executable_path);
	exit(126);
}
