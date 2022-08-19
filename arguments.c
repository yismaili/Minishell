/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/08/19 15:01:47 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	arguments_func(t_struct	*shell)
{
	t_arg	*arg;

	arg = init_arg();
	shell->arguments = NULL;
	if (shell->line_commande)
		arg_func(shell);
	free(shell->line_commande);
	free(arg);
}

int	ft_check_quote(t_struct *shell)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(shell->line_commande))
	{
		if (shell->line_commande[i] == QUOTE)
			shell->quote++;
		else if (shell->line_commande[i] == DOUBLE_QUOTE)
			shell->double_quote++;
		i++;
	}
	shell->pos = 0;
	while (shell->line_commande[shell->pos] != '\0')
	{
		if (shell->line_commande[shell->pos] == '\"' || \
		shell->line_commande[shell->pos] == '\'')
			return (shell->pos);
		shell->pos++;
	}
	return (0);
}

void	ft_check_space(t_struct *shell)
{
	int		i;

	i = 1;
	shell->space = 0;
	while (i < shell->size - 1 && \
			(&shell->line_commande[shell->pos])[i] != '\"' \
			&& (shell->size >= 2))
	{
		if ((&shell->line_commande[shell->pos])[i] == ' ')
		{
			shell->space = 1;
			break ;
		}
		i++;
	}
}

void	ft_check_quote_pos(t_struct *shell, char *cmd_joined)
{
	if ((((&shell->line_commande[shell->pos])[0] == '\"' \
					&& (&shell->line_commande[shell->pos])[shell->size - 2] \
					== '\"') \
				|| ((&shell->line_commande[shell->pos])[0] == '\'' && \
					(&shell->line_commande[shell->pos])[shell->size - 2] \
					== '\'')) \
			&& (shell->size > 2))
	{
		shell->indice++;
	}
	if ((((&shell->line_commande[shell->pos])[0] == '\"' \
					&& (&shell->line_commande[shell->pos])[shell->size - 1] \
					== '\"') \
				|| ((&shell->line_commande[shell->pos])[0] == '\'' \
					&& (&shell->line_commande[shell->pos])[shell->size - 1] == \
					'\'')) && (shell->size > 2))
	{
		shell->indice++;
	}
	if (ft_strchr(shell->line_commande, '\''))
		shell->check = 1;
	split_arg(shell, cmd_joined);
	if (check_quotes_next(shell) == 0)
		return ;
}

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
			if (!ft_strncmp(shell->arguments[i], "echo", 4))
				return (0);
			i++;
		}
		shell->right = 1;
	}
	return (1);
}
