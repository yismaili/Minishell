/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:05 by souchen           #+#    #+#             */
/*   Updated: 2022/07/04 17:33:05 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void	ft_unset(t_struct *shell)
{
	int i;
	i = 1;
	while (shell->arguments[i])
	{
		if (find_envernement(shell, shell->arguments[i]))
		{
			rm_envernement(shell);

			if (!ft_strncmp(shell->arguments[i], "PATH", 4))
			{
				free1(shell->path);
				shell->path = NULL;
			}
		}
		i++;
	}
}

void	rm_envernement(t_struct *shell)
{
	int	i;
	int	j;
	shell->env.len--;
	Malloc_env_aux(shell);
	i = 0;
	j = 0;
	while (i < shell->env.len)
	{
		if (i != shell->env.position)
		{
			shell->env_aux.tab1[j] = ft_strdup(shell->env.tab1[i]);
			shell->env_aux.tab2[j] = ft_strdup(shell->env.tab2[i]);
			j++;
		}
		i++;
	}
	shell->env_aux.tab1[j] = NULL;
	shell->env_aux.tab2[j] = NULL;
	free1(shell->env.tab1);
	free1(shell->env.tab2);
	shell->env.tab1 = shell->env_aux.tab1;
	shell->env.tab2 = shell->env_aux.tab2;
}

void	Malloc_env_aux(t_struct *shell)
{
	shell->env_aux.tab1 = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env_aux.tab1)
		exit(0);
	shell->env_aux.tab2 = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env_aux.tab2)
		exit(0);
}
