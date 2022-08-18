/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divise_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:25 by souchen           #+#    #+#             */
/*   Updated: 2022/08/18 00:28:28 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	initial_divise(t_struct *shell, char *commande_read)
{
	int	i;

	i = 0;
	shell->divise.number_command = 0;
	shell->divise.initial = 0;
	shell->divise.quote = 0;
	shell->divise.pipe = 0;
	shell->cmp = 0;
	shell->i = 0;
	shell->j = 0;
	shell->len = 0;
	shell->dup_pipe = 0;
	while (commande_read[i] != '\0')
	{
		if (commande_read[i] == QUOTE)
			shell->quote_cmd++;
		else if (commande_read[i] == DOUBLE_QUOTE)
			shell->dquote_cmd++;
		i++;
	}
}

void	command(t_struct *shell, char *commande_read)
{
	if (shell->i > 1)
	{
		shell->commands[shell->divise.number_command] = \
			ft_substr(commande_read, shell->divise.initial, shell->len);
		shell->divise.initial = shell->i;
		shell->len = 0;
		shell->divise.number_command++;
	}
}

void	divise_pipe_redir(t_struct *shell, char *commande_read)
{
	check_pipe(shell->j, shell, commande_read);
	if ((commande_read[shell->i] == '|' || \
				commande_read[shell->i] == '<' || \
				commande_read[shell->i] == '>') \
			&& (shell->i < shell->start || shell->i > shell->end))
	{
		if (commande_read[shell->i] == '|')
			shell->divise.pipe++;
		if (commande_read[shell->i] == '|' \
				&& commande_read[shell->i + 1] == '|')
			shell->dup_pipe = 1;
		command(shell, commande_read);
		if (commande_read[shell->i + 1] == commande_read[shell->i])
		{
			shell->i++;
			shell->len = 1;
		}
	}
	shell->j++;
	shell->i++;
	shell->len++;
}

void	divise_commande(t_struct *shell, char *commande_read)
{
	int	i;

	initial_divise(shell, commande_read);
	i = 0;
	while (shell->i < (int)ft_strlen(commande_read))
		divise_pipe_redir(shell, commande_read);
	next (shell, commande_read);
}

void	next(t_struct *shell, char *commande_read)
{
	int	i;

	i = 0;
	if (ft_strlen(commande_read) > 0)
	{
		shell->commands[shell->divise.number_command] = \
			ft_substr(commande_read, shell->divise.initial, shell->i);
		shell->divise.number_command++;
	}
	shell->commands[shell->divise.number_command] = NULL;
}
