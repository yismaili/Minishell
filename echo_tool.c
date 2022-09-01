/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:46:50 by souchen           #+#    #+#             */
/*   Updated: 2022/09/01 17:47:08 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_print_env_var(t_struct *shell, char *splted)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	splted = ft_remove_quot(splted, '\'', shell);
	splted = ft_remove_quot(splted, '\"', shell);
	ft_print_env_var_next(shell, splted, i, q);
}

int	ft_next_echo_dlr(char **splted, t_struct *shell)
{
	int	j;
	int	nb_qot;

	j = 0;
	while (splted[j] != NULL)
	{
		shell->dif_j = 0;
		if (shell->chek_test == 1)
		{
			print_echo(shell, splted[j + 1]);
			break ;
		}
		if (splted[j] != NULL)
			splted[j] = ft_strtrim(splted[j], "$");
		nb_qot = ft_skip_qote(splted, shell, &j);
		if (nb_qot == 1)
			j++;
		else if (nb_qot == 0)
			return (0);
		ft_print_env_var(shell, splted[j]);
		j++;
	}
	return (1);
}

void	ft_print_env_var_next(t_struct *shell, char *splted, int i, int q)
{
	while (shell->env.tmp_var[i])
	{
		if ((!ft_strcmp(shell->env.tmp_var[i], splted)) && shell->dif_j == 0)
		{
			if (shell->quote != 0)
			{
				ft_putstr_fd(shell->env.tmp_con[i], shell->output_fd);
				q = 0;
				while (shell->quote / 2 > q)
				{
					ft_putstr_fd("\'", shell->output_fd);
					q++;
				}
			}
			else
				ft_putstr_fd(shell->env.tmp_con[i], shell->output_fd);
			if (shell->chek_plc_ == 1)
				ft_putstr_fd("+", shell->output_fd);
			shell->chek_plc_ = 0;
		}
		i++;
	}
}
