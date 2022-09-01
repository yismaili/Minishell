/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/09/01 00:54:20 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_echo(t_struct *shell)
{
	int	j;

	j = 0;
	shell->q1 = 0;
	shell->q2 = 0;
	shell->i = 0;
	shell->f_pipe = 0;
	if (shell->arguments[0][0] == '|' && !shell->arguments[0][1])
		shell->f_pipe = 1;
	else if (shell->arguments[0][0] == '|' && shell->arguments[0][1])
		shell->arguments[0] = &shell->arguments[0][1];
	while (shell->variable == 1 && shell->arguments[j] != NULL \
	&& shell->f_pipe != 0)
	{
		shell->arguments[j] = shell->arguments[j + 1];
		j++;
	}
	if (shell->arguments[1] == NULL)
	{
		ft_putstr_fd("\n", shell->output_fd);
		return ;
	}
	ft_next_echo(shell);
}

void	ft_chekexit_status(t_struct *shell)
{
	char	*rm_es;
	char	*srch;
	char	*tmp;

	rm_es = ft_strtrim(shell->arguments[1], "$?");
	srch = find_env(shell, "?");
	tmp = shell->arguments[1];
	shell->arguments[1] = ft_strjoin(srch, rm_es);
	free(tmp);
}

int	ft_check_n(t_struct *shell)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (shell->arguments[i])
	{
		j = 1;
		while (j < (int)ft_strlen(shell->arguments[i]) - 1)
		{
			if (shell->arguments[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (2);
}

int	ft_next_echo(t_struct *shell)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (shell->arguments[1][0] == '-' && shell->arguments[1][1] == 'n')
	{
		i = ft_check_n(shell);
		if (i != 1)
			j = 1;
	}
	while (shell->arguments[i] && shell->qot % 2 == 0)
	{
		if (shell->arguments[i])
		{
			print_echo(shell, shell->arguments[i]);
			ft_putstr_fd(" ", shell->output_fd);
		}
		i++;
	}
	if (j == 0)
		ft_putstr_fd("\n", shell->output_fd);
	return (0);
}

void	print_echo(t_struct *shell, char *echo_print)
{
	size_t	i;

	i = 0;
	if (echo_print == NULL)
	{
		ft_putstr_fd(" ", shell->output_fd);
		return ;
	}
	while (echo_print[i] != '$' && echo_print[i] != '\0')
	{
		ft_putchar_fd(echo_print[i], shell->output_fd);
		i++;
	}
	if ((!ft_strncmp(&echo_print[i], "$", 1)) || \
			(!ft_strncmp(&echo_print[i], "$", 1) && \
			(shell->quote == 0 && shell->double_quote == 0)) || \
			(!ft_strncmp(&echo_print[i], "$", 1) && \
			(shell->quote > 0 && shell->double_quote > 0)))
	{
		echo_with_dollar(shell, (&echo_print[i]));
	}
}

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
