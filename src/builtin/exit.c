/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:33:02 by saylital          #+#    #+#             */
/*   Updated: 2025/04/04 13:29:30 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    is_overflown(char *str)
{
    long long    nbr;
    size_t        len;

    if (ft_strncmp("-9223372036854775808", str, 20) == 0)
        return (1);
    nbr = msatol(str);
    len = ft_strlen(str);
    if (nbr == -1 && len != 2)
		return (-1);
	if (nbr == 0)
		return (0);
	return (1);
}

void	exit_error_check(t_ms *shell, char **cmd)
{
	if (cmd[1] != NULL)
	{
		if (validate_str(cmd[1], "-+0123456789") == -1 \
			|| is_overflown(cmd[1]) < 0)
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			shell->exit_code = 2;
			if (actually_exit(shell) == 1)
				return ;
		}
	}
}

void	it_was_alpha(t_command *command, t_ms *shell)
{
	shell->alpha_exit = 1;
    shell->exit_code = 2;
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(command->args[1], 2);
    ft_putstr_fd(": numeric argument required\n", 2);
    if (ft_strncmp(command->args[1], "false", 5) == 0)
        shell->exit_code = 1;
    if (ft_strncmp(command->args[1], "true", 4) == 0)
        shell->exit_code = 0;
    if (actually_exit(shell) == 1)
        return ;
}

void    check_numeric(t_command *command, t_ms *shell)
{
    int            i;

    i = 0;
	shell->alpha_exit = 0;
    if (!command->args[1])
        return ;
    if (command->args[1][i] == '#')
    {
        shell->exit_code = 0;
        ft_putstr_fd("exit\n", 2);
        if (actually_exit(shell) == 1)
            return ;
    }
    while (command->args[1][i])
    {
        if (ft_isalpha(command->args[1][i]) == 1)
            it_was_alpha(command, shell);
        i++;
    }
	if (shell->alpha_exit == 0)
		exit_error_check(shell, command->args);
}

void	ft_exit(t_command *command, t_ms *shell)
{
	if (!command->args[1] && !command->next)
	{
		ft_putstr_fd("exit\n", 2);
		if (actually_exit(shell) == 1)
			return ;
	}
	check_numeric(command, shell);
	if (shell->alpha_exit)
		return ;
	if (command->arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_code = 1;
			return ;
	}
	else if (command->args[1] && !command->next)
	{
		shell->exit_code = ft_atoi(command->args[1]);
		ft_putstr_fd("exit\n", 1);
		if (actually_exit(shell) == 1)
			return ;
	}
}
