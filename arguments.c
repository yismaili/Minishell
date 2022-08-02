/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/08/01 02:05:27 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	arguments_func(t_struct	*shell)
{
	char	*cmd_joined;
	char	**spled;
	t_arg	*arg;

	arg = init_arg();
	cmd_joined = NULL;
	spled = NULL;
	shell->arguments = NULL;
	if (shell->line_commande)
	{
		arg->position = find_char(shell->line_commande, ' ');
		spled = arg_func(shell, cmd_joined, arg);
		cmd_splited(spled, shell);
	}
}

char	**arg_func(t_struct *shell, char *cmd_joined, t_arg *arg)
{
	char	**spled;
	char	**spl;
	int		size;

	spled = NULL;
	spl = NULL;
	size = ft_strlen(shell->line_commande);
	shell->arg.all_cmd = ft_strtrim(&(shell->line_commande) \
			[arg->position], " ");
	shell->arg.txt_toprint = ft_strtrim(&(shell->line_commande) \
			[arg->position], " ");
	if (((shell->line_commande[0] == '\"') && \
				(shell->line_commande[size - 1] == '\"')) \
			|| ((shell->line_commande[0] == '\'') && \
				(shell->line_commande[size - 1] == '\'')))
		spled = arg_with_quote(cmd_joined, shell);
	else
		spled = split_arg(spl, cmd_joined, shell);
	free_arg(arg);
	return (spled);
}

char	**arg_with_quote(char *cmd_joined, t_struct *shell)
{
	char	**spled;

	spled = NULL;
	cmd_joined = ft_split_cmd(shell->line_commande);
	shell->arguments = ft_split(cmd_joined, ' ');
	spled = ft_split(cmd_joined, '|');
	free(cmd_joined);
	return (spled);
}
