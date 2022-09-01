/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:12 by souchen           #+#    #+#             */
/*   Updated: 2022/08/29 13:50:57 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**get_path(t_struct *ptr)
{
	int		i;
	char	**path;

	i = 0;
	if (g_var.g_var == 0)
		return (NULL);
	while (ptr->env.tmp_var[i])
	{
		if (!ft_strcmp(ptr->env.tmp_var[i], "PATH"))
		{
			path = ft_split(ptr->env.tmp_con[i], ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	start_create_env(t_struct *shell)
{
	extern char	**environ;

	shell->cmp = 0;
	ft_check_env(environ);
	if (g_var.g_var != 0)
		if (!create_env_tmp(shell, environ))
			return (0);
	return (1);
}

void	print_cmd_not_f(t_struct *shell)
{
	ft_putstr_fd("Minishell :", 2);
	ft_putstr_fd(shell->arguments[0], 2);
	ft_putstr_fd(" : command not found\n", 2);
}

int	in_check(char **fichier, char *fichier1)
{
	(void) fichier1;
	if (!fichier)
		return (0);
	return (1);
}
