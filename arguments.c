/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/08/03 16:35:58 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	arguments_func(t_struct	*shell)
{
	char	*cmd_joined;
	t_arg	*arg;

	arg = init_arg();
	cmd_joined = NULL;
	shell->arguments = NULL;
	if (shell->line_commande)
	{
		arg->position = find_char(shell->line_commande, ' ');
		arg_func(shell, cmd_joined, arg);
	}	
}

void	arg_func(t_struct *shell, char *cmd_joined, t_arg *arg)
{
	int	size;
	int	i;
	int	j;
	int	pos;

	i = 0;
	j = 0;
	pos = 0;
	shell->space = 0;
	shell->quote = 0;
	shell->indice = 0;
	shell->double_quote = 0;
	size = ft_strlen(shell->line_commande);
	shell->arg.all_cmd = ft_strtrim(&(shell->line_commande) \
			[arg->position], " ");
	shell->arg.txt_toprint = ft_strtrim(&(shell->line_commande) \
			[arg->position], " ");
	while (i < (int)ft_strlen(shell->line_commande))
	{
		if (shell->line_commande[i] == QUOTE)
			shell->quote++;
		else if (shell->line_commande[i] == DOUBLE_QUOTE)
			shell->double_quote++;
		i++;
	}
	if ((shell->line_commande[0] == '\"' && \
		shell->line_commande[size - 2] == '\"') || \
		(shell->line_commande[0] == '\'' \
		&& shell->line_commande[size - 2] == '\''))
		shell->indice++;
	if ((shell->line_commande[0] == '\"' && \
		shell->line_commande[size - 1] == '\"') \
		|| (shell->line_commande[0] == '\'' \
		&& shell->line_commande[size - 1] == '\''))
		shell->indice++;
	while (shell->line_commande[j] != '\0')
	{
		if (shell->line_commande[j] >= 'a' && shell->line_commande[j] <= 'z')
		{
			pos = j;
			break ;
		}
		j++;
	}
	i = 0;
	while (i < (int)ft_strlen(&shell->line_commande[pos]))
	{
		if ((&shell->line_commande[pos])[i] == ' ')
			shell->space = 1;
		i++;
	}
	if (shell->space == 1 && shell->indice == 1)
		shell->right = 1;
	if ((shell->line_commande[0] == '\"') || \
		(shell->line_commande[0] == '\'') || \
		(shell->line_commande[size -1] == '\"') \
		|| (shell->line_commande[size -1] == '\''))
	{
		cmd_joined = ft_split_cmd(shell->line_commande);
		shell->arguments = ft_split(cmd_joined, ' ');
	}
	else
		shell->arguments = ft_split(shell->line_commande, ' ');
}
