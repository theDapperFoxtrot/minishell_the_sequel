/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:09:13 by smishos           #+#    #+#             */
/*   Updated: 2025/04/05 17:32:39 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_closing_quote(t_ms *shell, const char *str, char quote_type, int start)
{
	int	i;

	i = start + 1;
	while (str[i] && str[i] != quote_type)
		i++;
	if (str[i] == quote_type)
	{
		shell->processed_quotes = 1;
		return (i);
	}
	else
	{
		ft_putstr_fd(\
			"minishell: syntax error: Missing matching end quote symbol\n", 2);
		free(shell->exp.result);
		cleanup(shell, 1);
		exit(2);
	}
}

int	find_closing_brace(const char *str, int start)
{
	int	i;
	int	brace_count;

	i = start;
	brace_count = 1;
	while (str[i] && brace_count > 0)
	{
		i++;
		if (str[i] == '{')
			brace_count++;
		else if (str[i] == '}')
			brace_count--;
	}
	if (brace_count == 0)
		return (i);
	else
		return (-1);
}

char	*qmark_check(t_ms *shell, int with_braces)
{
	char	*temp_var;
	char	*temp;

	temp_var = shell->exp.var_name;
	if (temp_var[0] == '$')
		temp_var++;
	if (with_braces && temp_var[0] == '{')
		temp_var++;
	if (temp_var[0] == '?' && \
	(!with_braces || temp_var[1] == '}'))
	{
		shell->exp.value = ft_itoa(shell->exit_code);
		temp_var++;
		if (ft_isalnum(temp_var[0]))
		{
			temp = shell->exp.value;
			shell->exp.value = ft_strjoin(temp, temp_var);
			free(temp);
			if (!shell->exp.value)
				malloc_error(shell);
		}
	}
	return (shell->exp.value);
}

void	get_var_name_len(t_ms *shell, int with_braces)
{
	while (shell->exp.var_name[shell->exp_name_len] && \
	((!with_braces && \
	(ft_isalnum(shell->exp.var_name[shell->exp_name_len]) || \
	shell->exp.var_name[shell->exp_name_len] == '_')) || \
	(with_braces && \
	shell->exp.var_name[shell->exp_name_len] != '}')))
		shell->exp_name_len++;
}

void	get_var_value(t_ms *shell)
{
	char	*temp;
	char	*joined;

	temp = NULL;
	while (shell->env_list[shell->exp_i])
	{
		if (ft_strncmp(shell->env_list[shell->exp_i], shell->exp_temp_name, \
			ft_strlen(shell->exp_temp_name)) == 0 && \
		shell->env_list[shell->exp_i][ft_strlen(shell->exp_temp_name)] == '=')
		{
			temp = shell->exp.value;
			joined = ft_strjoin(temp, shell->env_list[shell->exp_i] + \
				ft_strlen(shell->exp_temp_name) + 1);
			free(temp);
			var_val_mal_check(shell, joined);
			free(joined);
			break ;
		}
		shell->exp_i++;
	}
	set_value_after_parse(shell, temp);
}
