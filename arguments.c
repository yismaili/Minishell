/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/07/04 17:33:23 by yismaili         ###   ########.fr       */
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

	arg = initial_arg();
	shell->arguments = NULL;
	if (shell->line_commande)
	{
		arg->position = find_char(shell->line_commande, ' ');
		shell->arg.Lechemin = ft_strtrim(&(shell->line_commande)[arg->position], " ");
		shell->arg.txt_toprint = ft_strtrim(&(shell->line_commande)[arg->position], " ");
		shell->arguments = ft_split(shell->line_commande, ' ');
		free_arg(arg);
		free (shell->line_commande);

	}
}
    
