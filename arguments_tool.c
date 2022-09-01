/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:39:17 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/28 23:06:59 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_quotes_next(t_struct	*shell)
{
	int	i;

	i = 0;
	if (shell->space == 1 && shell->indice == 1 && ((shell->quote == 2 && \
					shell->double_quote != 2) || \
				(shell->quote != 2 && shell->double_quote == 2)))
	{
		while (shell->arguments[i] != NULL)
		{
			if (!ft_strncmp(shell->arguments[i], "echo", 4) || \
				!ft_strncmp(&shell->arguments[i][1], "echo", 4) || \
				!ft_strncmp(shell->arguments[i], "export", 6) || \
				!ft_strncmp(&shell->arguments[i][1], "export", 6))
				return (0);
			i++;
		}
		shell->right = 1;
	}
	return (1);
}

int	next(t_struct *shell, char *commande_read)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	shell->var = 0;
	if (ft_strlen(commande_read) > 0)
	{
		shell->commands[shell->divise.number_command] = \
		ft_substr(commande_read, shell->divise.initial, shell->i);
		shell->divise.number_command++;
	}
	shell->commands[shell->divise.number_command] = NULL;
	return (1);
}

void	ft_identifier_export(t_struct *shell)
{
	ft_putstr_fd("Export: ", 2);
	ft_putstr_fd(shell->arguments[shell->i_for_chek], 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return ;
}

void	cmp_spaces(t_struct *shell)
{
	int	i;

	i = 0;
	while (shell->line_commande[i] != '\0')
	{
		if (shell->line_commande[i] == ' ')
			shell->cmp_space++;
		i++;
	}
}

void	cas_failed(t_struct *shell)
{
	check_char(shell, shell->commande_tape);
	if (shell->failed == 1)
	{
		ft_putstr_fd("Minishell: No such file or directory", 2);
		ft_putstr_fd(shell->commande_tape, 2);
		ft_putstr_fd("\n", 2);
	}
}
