/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divise_commandes_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:28:47 by souchen           #+#    #+#             */
/*   Updated: 2022/08/28 16:20:38 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_pipe(int i, t_struct *shell, char *commande_read)
{
	int	j;

	j = 0;
	while (i < (int)ft_strlen(commande_read) && (shell->quote_cmd % 2 == 0 \
				|| shell->dquote_cmd % 2 == 0) && (i > shell->end || i == 0))
	{
		if (commande_read[i] == '\"')
		{
			check_quote(i, shell, commande_read, '\"');
			break ;
		}
		else if (commande_read[i] == '\'')
		{
			check_quote(i, shell, commande_read, '\'');
			break ;
		}
		i++;
	}
}

void	check_quote(int i, t_struct *shell, char *commande_read, char character)
{
	int	j;

	j = 0;
	shell->start = i;
	while ((&commande_read[shell->start])[j] != '\0')
	{
		if ((&commande_read[shell->start + 1])[j] == character)
		{
			shell->end = i + 1;
			break ;
		}
		i++;
		j++;
	}
}

int	ft_else(t_struct *shell, int i)
{
	if (g_var.g_var == 0)
	{
		verify_if_env_exists(shell);
		free(shell->frst);
		free(shell->scnd);
		return (1);
	}
	if (shell->frst && shell->arguments[i] \
		[ft_strlen(shell->arguments[1]) - 1] != '=' && \
			shell->scnd != NULL)
		verify_if_env_exists(shell);
	else if (shell->frst && shell->scnd == NULL)
		verify_if_env_exists(shell);
	return (0);
}

int	ft_with_dlr(t_struct *shell)
{
	if (check_export_con(shell->frst) == 1)
	{
		ft_putstr_fd("Export: ", 2);
		ft_putstr_fd(shell->frst, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		free(shell->frst);
		free(shell->scnd);
		return (1);
	}
	else if (check_export_con(shell->frst) == 3)
	{
		sort_env(shell);
		free(shell->frst);
		free(shell->scnd);
		return (1);
	}
	return (0);
}
