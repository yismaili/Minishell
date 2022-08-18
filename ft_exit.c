/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:52 by souchen           #+#    #+#             */
/*   Updated: 2022/08/18 17:07:23 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_struct *shell)
{
	ft_putstr_fd("exit\n", shell->output_fd);
	exit(0);
}

char	*find_env(t_struct *shell, char *search)
{
	int	i;

	i = 0;
	shell->env.position = 0;
	if (g_var.g_var == 0)
		return (NULL);
	while (shell->env.tmp_var[i] && i <= shell->env.len)
	{
		if (!ft_strcmp(shell->env.tmp_var[i], search))
		{
			shell->env.position = i;
			return (shell->env.tmp_con[i]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_return_con(t_struct *shell, char **env_aux)
{
	char	*ptr;
	char	*rm;

	ptr = env_aux[0];
	rm = ft_strtrim(env_aux[0], "$");
	env_aux[0] = find_env(shell, rm);
	free(ptr);
	free(rm);
	return (env_aux[0]);
}
