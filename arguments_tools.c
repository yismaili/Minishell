/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 23:14:00 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/19 17:30:12 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	split_arg(t_struct *shell, char *cmd_joined)
{
	int	i;

	i = 0;
	if ((((&shell->line_commande[shell->pos])[0] == '\"') || \
		((&shell->line_commande[shell->pos])[0] == '\'')) || \
		(((&shell->line_commande[shell->pos])[shell->size - 1] == '\"') || \
		((&shell->line_commande[shell->pos])[shell->size - 1] == '\'')))
	{
		cmd_joined = ft_split_cmd(shell->line_commande, shell);
		shell->arguments = ft_split(cmd_joined, ' ');
		while (shell->arguments[i] != NULL \
				&& ft_strncmp(shell->arguments[i], "echo", 4))
		{
			shell->arguments[i] = ft_remove_quot
				(shell->arguments[i], '\"', shell);
			shell->arguments[i] = ft_remove_quot
				(shell->arguments[i], '\'', shell);
			i++;
		}
		free(cmd_joined);
	}
	else
		shell->arguments = ft_split(shell->line_commande, ' ');
}

void	arg_func(t_struct *shell)
{
	char	*cmd_joined;

	shell->indice = 0;
	shell->quote = 0;
	shell->double_quote = 0;
	cmd_joined = NULL;
	ft_check_quote(shell);
	shell->size = ft_strlen(&shell->line_commande[shell->pos]);
	ft_check_space(shell);
	ft_check_quote_pos(shell, cmd_joined);
}
