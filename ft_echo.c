/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/09/02 14:36:39 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_echo(t_struct *shell)
{
	int		j;
	char	*ptr;

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
		ptr = shell->arguments[j];
		shell->arguments[j] = shell->arguments[j + 1];
		free(ptr);
		j++;
	}
	if (shell->arguments[1] == NULL)
	{
		ft_putstr_fd("\n", shell->output_fd);
		return ;
	}
	ft_next_echo(shell);
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
