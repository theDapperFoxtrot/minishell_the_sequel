/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:09:29 by smishos           #+#    #+#             */
/*   Updated: 2025/04/03 18:27:02 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_value_after_parse(t_ms *shell, char *temp)
{
	temp = shell->exp.value;
	shell->exp.value = parse_quotes(temp);
	free(temp);
}

void	var_val_mal_check(t_ms *shell, char *joined)
{
	if (!joined)
		malloc_error(shell);
	shell->exp.value = ft_strdup(shell->env_list[shell->exp_i] + \
		ft_strlen(shell->exp_temp_name) + 1);
	if (!shell->exp.value)
		malloc_error(shell);
}

void	mhol_strjoin(t_command *cmd, char *line, int i)
{
	char	*temp;

	free(cmd->heredoc_lines[i]);
	temp = cmd->heredoc_line;
	cmd->heredoc_line = ft_strjoin(temp, line);
	free(temp);
}
