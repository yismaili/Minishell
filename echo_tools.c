/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:33:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/01 17:34:17 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	echo_with_dollar(t_struct *shell, char *echo_print)
{
	char	**splted;
	char	num;

	shell->chek_plc = 0;
	shell->chek_dlr = 0;
	shell->chek_test = 0;
	shell->var2 = 0;
	shell->dif_j = 0;
	shell->chek_num = 0;
	shell->count_dolr = 0;
	if (!shell->path)
		return ;
	num = ft_chek_isdigit(echo_print, shell);
	splted = ft_split_num_dlr(shell, echo_print, num);
	if (ft_next_echo_dlr(splted, shell) == 0)
		return ;
	ft_free_cmd(splted);
	return ;
}

int	ft_chek_isdigit(char *echo_print, t_struct	*shell)
{
	int	i;

	i = 0;
	while (echo_print[i])
	{
		if (ft_isdigit(echo_print[i]))
		{
			shell->chek_num = 1;
			return (echo_print[i]);
		}
		i++;
	}
	return (0);
}

char	**ft_split_num_dlr(t_struct *shell, char *echo_print, char num)
{
	char	**splted;

	splted = NULL;
	if (ft_strchr(echo_print, '+'))
	{
		splted = ft_split(echo_print, '+');
		shell->chek_plc_ = 1;
	}
	else if (shell->chek_num != 0)
	{
		splted = ft_split(echo_print, num);
		shell->chek_test = 1;
	}
	else
	{
		splted = ft_split(echo_print, '$');
		shell->chek_dlr = 1;
	}
	ft_count_doler(echo_print, shell);
	return (splted);
}

void	ft_count_doler(char *echo_print, t_struct *shell)
{
	int	g;

	g = 0;
	while (echo_print[g])
	{
		if (echo_print[g] == '$')
			shell->count_dolr++;
		g++;
	}
	return ;
}

int	ft_skip_qote(char **splted, t_struct *shell, int *j)
{
	if (splted[*j][ft_strlen(splted[*j]) - 1] == '\"' || \
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
	return (-1);
}

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
