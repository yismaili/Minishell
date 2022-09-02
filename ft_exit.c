/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:52 by souchen           #+#    #+#             */
/*   Updated: 2022/09/01 22:01:12 by yismaili         ###   ########.fr       */
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

char	*ft_return_con(t_struct *shell)
{
	char	*ptr;
	char	*rm;

	ptr = shell->frst;
	rm = ft_strtrim(shell->frst, "$");
	shell->frst = find_env(shell, rm);
	free(ptr);
	free(rm);
	return (shell->frst);
}

void	check_char(t_struct *shell, char *commande_line)
{
	int	i;

	i = 0;
	shell->not_alpha = 0;
	shell->failed = 0;
	while (commande_line[i] != '\0' && !is_empty(shell->commande_tape))
	{
		if (!ft_isalpha(commande_line[i]) && \
				!ft_isdigit(commande_line[i]) && commande_line[i] != '$')
		{
			shell->not_alpha++;
		}
		i++;
	}
	if (shell->not_alpha == (int)ft_strlen(commande_line) \
			&& shell->not_alpha != 0)
	{
		shell->failed = 1;
	}
}
