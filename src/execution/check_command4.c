/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:08:54 by smishos           #+#    #+#             */
/*   Updated: 2025/03/30 15:14:39 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**check_empty_args(t_command *command, t_ms *shell)
{
	char	**args;

	args = command->args;
	while (args && *args && (*args)[0] == '\0')
		args++;
	if (!args || !args[0] || args[0][0] == '\0')
	{
		cleanup(shell, 1);
		exit(0);
	}
	return (args);
}

void	execute_command(t_ms *shell, char **args)
{
	char	*path;

	if (!shell->exec)
	{
		path = find_executable_path(shell, args);
		if (!path)
		{
			cleanup(shell, 1);
			exit(127);
		}
		if (execve(path, args, shell->env_list) == -1)
		{
			if (g_signal == SIGINT)
				write(1, "\n", 1);
			perror("minishell");
			shell->exit_code = 126;
			cleanup(shell, 1);
			exit(shell->exit_code);
		}
	}
}

void	child_process(t_ms *shell, t_command *command, int *new_pipe)
{
	int		i;
	char	**args;

	if (default_signals() == 1)
		print_error("Error: default_signals failed", shell, 1, 1);
	start_sig_checkers(&sig_handler_child);
	if (shell->prev_pipe_in != -1)
	{
		dup2(shell->prev_pipe_in, STDIN_FILENO);
		close(shell->prev_pipe_in);
	}
	if (command->next)
	{
		close(new_pipe[0]);
		dup2(new_pipe[1], STDOUT_FILENO);
		close(new_pipe[1]);
	}
	i = -1;
	while (command->command_input[++i])
		execute_redir(shell, command, i);
	args = check_empty_args(command, shell);
	shell->exec = is_builtin(args, shell);
	execute_command(shell, args);
	cleanup(shell, 1);
	exit(shell->exit_code);
}

t_command	*parent_process(t_ms *shell, t_command *command, int *new_pipe)
{
	if ((shell->prev_pipe_in) != -1)
		close((shell->prev_pipe_in));
	if (!command->next)
		shell->last_pid = command->pid;
	if (command->next)
	{
		close(new_pipe[1]);
		(shell->prev_pipe_in) = new_pipe[0];
	}
	command = command->next;
	return (command);
}

t_command	*check_for_exit(t_ms *shell, t_command *command, int *new_pipe)
{
	if (shell->child_count > 1)
		close(new_pipe[0]);
	ft_exit(command, shell);
	command = command->next;
	return (command);
}
