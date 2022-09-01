/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:46:50 by souchen           #+#    #+#             */
/*   Updated: 2022/09/01 18:28:52 by souchen          ###   ########.fr       */
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
		if (splted[j] != NULL)
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

int	ft_skip_qote(char **splted, t_struct *shell, int *j)
{
	if (splted[*j])
	{
		if (splted[*j][0] != '\0')
		{
			if (splted[*j][(ft_strlen(splted[*j])) - 1] == '\"' || \
					(shell->quote == 2 && shell->double_quote == 0))
			{
				ft_putstr_fd("$", shell->output_fd);
				ft_putstr_fd(splted[*j], shell->output_fd);
				if (shell->count_dolr > 1 && (splted[*j + 1] != NULL))
					return (1);
				else if (*j > shell->count_dolr)
					return (0);
				else
					shell->dif_j = 1;
			}
		}
	}
	return (-1);
}
