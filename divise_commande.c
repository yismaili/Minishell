/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divise_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:25 by souchen           #+#    #+#             */
/*   Updated: 2022/08/24 23:06:18 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	initial_divise(t_struct *shell)
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
	shell->dup_red = 0;
	shell->var = 0;
	return 1;
}

int	command(t_struct *shell, char *commande_read)
{
	int j;
	j = 0;
	shell->var = 0;
	if (shell->i > 1)
	{
		shell->commands[shell->divise.number_command] = \
			ft_substr(commande_read, shell->divise.initial, shell->len);
		shell->divise.initial = shell->i;
		shell->len = 0;
		shell->divise.number_command++;
	}
		
	return 1;
}

int	divise_pipe_redir(t_struct *shell, char *commande_read)
{
	check_pipe(shell->j, shell, commande_read);
	if ((commande_read[shell->i] == '|' || \
				commande_read[shell->i] == '<' || \
				commande_read[shell->i] == '>') \
			&& (shell->i <= shell->start || shell->i >= shell->end))
	{
		if (commande_read[shell->i] == '|')
			shell->divise.pipe++;
		if (commande_read[shell->i] == '|' \
				&& commande_read[shell->i + 1] == '|')
				{
					shell->msg = PIPE_ERROR;
					return 0;
				}
		else if((commande_read[shell->i] == '<' || commande_read[shell->i] == '>') && \
		(commande_read[shell->i + 1] == '<' || commande_read[shell->i + 1] == '>') && \
		(commande_read[shell->i + 2] == '<' || commande_read[shell->i + 2] == '>'))
		{
			shell->msg = RED_ERROR;
			return 0;
		}
		else if(commande_read[shell->i] == '|' && (int)ft_strlen(commande_read) == shell->i + 1)
		{
			shell->msg = PIPE_ERROR;
			return 0;
		}
		else if((commande_read[shell->i] == '<' || commande_read[shell->i] == '>') && \
		(int)ft_strlen(commande_read) == shell->i + 1)
		{
			shell->msg = RED_ERROR;
			return 0;
		}
		if(command(shell, commande_read) == 0)
			return 0;
		if (commande_read[shell->i + 1] == commande_read[shell->i] && (int)ft_strlen(commande_read) != shell->i + 2)
		{
			shell->i++;
			shell->len = 1;
		}
	}
	shell->j++;
	shell->i++;
	shell->len++;
	return 1;
}

int	divise_commande(t_struct *shell, char *commande_read)
{
	int	i;
	i = 0;
	initial_divise(shell) ;
	while (shell->i <= (int)ft_strlen(commande_read))
		if (divise_pipe_redir(shell, commande_read) == 0)
		{
			return 0;
		}
	if(next (shell, commande_read)== 0)
		return 0;
	return 1;
}

int	next(t_struct *shell, char *commande_read)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	shell->var = 0;
	if (ft_strlen(commande_read) > 0)
	{
		shell->commands[shell->divise.number_command] = \
			ft_substr(commande_read, shell->divise.initial, shell->i);
		shell->divise.number_command++;
	}
	printf("cmd[0]=%s\n", shell->commands[0]);
	shell->commands[shell->divise.number_command] = NULL;
	/*while(shell->commands[shell->divise.number_command - 1][j] != '\0')
	{
		if(!ft_isalpha(shell->commands[shell->divise.number_command - 1][j]))
			shell->var++;
		j++;
	}
	if(shell->var == (int)ft_strlen(shell->commands[shell->divise.number_command - 1]))
	{
		return 0;
	}*/
	return 1;
} 
