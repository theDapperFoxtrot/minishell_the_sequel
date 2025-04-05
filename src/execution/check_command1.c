/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:08:45 by smishos           #+#    #+#             */
/*   Updated: 2025/04/05 17:55:16 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_parent_builtin(char **cmd, t_ms *shell)
{
	if (ft_strncmp(cmd[0], "export", 6) == 0 && ft_strlen(cmd[0]) == 6)
	{
		if (cmd[1])
		{
			ft_export(cmd, shell);
			return (1);
		}
		else
			return (0);
	}
	if (ft_strncmp(cmd[0], "unset", 5) == 0 && ft_strlen(cmd[0]) == 5)
	{
		ft_unset(cmd, shell);
		return (1);
	}
	else if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
	{
		ft_cd(cmd, shell);
		return (1);
	}
	return (0);
}

int	is_builtin(char **command, t_ms *shell)
{
	if (!command)
		return (1);
	if (ft_strncmp(command[0], "export", 6) == 0 && \
		ft_strlen(command[0]) == 6)
		return (run_builtin(shell, command, ft_export));
	else if (ft_strncmp(command[0], "cd", 2) == 0 && \
			ft_strlen(command[0]) == 2)
		return (run_builtin(shell, command, ft_cd));
	else if (ft_strncmp(command[0], "pwd", 3) == 0 && \
		ft_strlen(command[0]) == 3)
		return (run_builtin(shell, command, ft_pwd));
	else if ((ft_strncmp(command[0], "echo", 4) == 0 && \
			ft_strlen(command[0]) == 4) || \
			(ft_strncmp(command[0], "/bin/echo", 9) == 0 && \
			ft_strlen(command[0]) == 9))
		return (run_builtin(shell, command, ft_echo));
	else if (ft_strncmp(command[0], "env", 3) == 0 && \
			ft_strlen(command[0]) == 3)
		return (run_builtin(shell, command, ft_env));
	return (0);
}

void	fork_error(int *new_pipe)
{
	ft_putendl_fd("minishell: Fork error: forking failed", 2);
	close(new_pipe[0]);
	close(new_pipe[1]);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	return (path);
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
