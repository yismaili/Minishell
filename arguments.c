/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/07/24 01:04:10 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

int	find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle)
			return (i);
		i++;
	}
	return (i);
}

void	arguments_func(t_struct *shell)
{
	t_arg	*arg;
	char *cmd_joined;
	char **spl;

	arg = init_arg();
	shell->arguments = NULL;
	if (shell->line_commande)
	{
		arg->position = find_char(shell->line_commande, ' ');
		shell->arg.all_cmd = ft_strtrim(&(shell->line_commande)[arg->position], " ");
		shell->arg.txt_toprint = ft_strtrim(&(shell->line_commande)[arg->position], " ");
		shell->arguments = ft_split(shell->line_commande, ' ');
		spl = ft_split(shell->line_commande, '|');
		int i = 0;
		while (spl[i])
		{
			cmd_joined = ft_strjoin(spl[i], spl[i + 1]);
			i++;
		}
		shell->cmd_splited = ft_split(cmd_joined, ' ');
		free_arg(arg);
		free (shell->line_commande);

	}
}