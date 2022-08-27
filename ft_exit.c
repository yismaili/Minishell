/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:52 by souchen           #+#    #+#             */
/*   Updated: 2022/08/27 19:37:15 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_struct *shell)
{
	int	i;
	int	chek_digt;
	int	chek_alph;

	i = 1;
	chek_digt = 0;
	chek_alph = 0;
	if (shell->arguments[i] == NULL)
	{
		ft_putstr_fd("exit\n", shell->output_fd);
		exit(0);
	}
	while (shell->arguments[i])
	{
		if (ft_isdigit(shell->arguments[i][0]))
			chek_digt++;
		if (!ft_isdigit(shell->arguments[i][0]))
			chek_alph++;
		i++;
	}
	ft_eles_exit(shell, chek_alph, chek_digt);
}

void	ft_eles_exit(t_struct *shell, int chek_alph, int chek_digt)
{
	if (chek_digt == 1 && chek_alph == 0)
	{
		ft_putstr_fd("exit\n", shell->output_fd);
		exit(0);
	}
	if (chek_digt == 0 && chek_alph == 1)
	{
		ft_putstr_fd("Minishell: exit: numeric argument required\n", \
			shell->output_fd);
		exit(0);
	}
	if (chek_digt != 0 || chek_alph != 0)
		ft_putstr_fd("Minishell: exit: too many arguments\n", shell->output_fd);
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
	while (commande_line[i] != '\0')
	{
		if (!ft_isalpha(commande_line[i]) && commande_line[i] != '$' \
		&& commande_line[i + 1] != '?')
		{
			shell->not_alpha++;
		}
		i++;
	}
	if (shell->not_alpha == (int)ft_strlen(commande_line))
	{
		shell->failed = 1;
	}
}
