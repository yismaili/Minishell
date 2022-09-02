/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:46:50 by souchen           #+#    #+#             */
/*   Updated: 2022/09/02 16:27:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_print_env_var(t_struct *shell, char *splted)
{
	int		i;
	int		q;
	char	*ptr;

	i = 0;
	q = 0;
	if (ft_strchr(splted, '\'') || ft_strchr(splted, '\"'))
	{
		if (ft_strchr(splted, '\''))
		{
			ptr = ft_remove_quot(splted, '\'', shell);
			free(splted);
			splted = ft_strdup(ptr);
			free(ptr);
		}
		if (ft_strchr(splted, '\"'))
		{
			ptr = ft_remove_quot(splted, '\"', shell);
			free(splted);
			splted = ft_strdup(ptr);
			free(ptr);
		}
	}
	ft_print_env_var_next(shell, splted, i, q);
}

int	ft_next_echo_dlr(char **splted, t_struct *shell)
{
	int		j;
	char	*ptr;

	j = 0;
	while (splted[j] != NULL)
	{
		shell->dif_j = 0;
		if (print_echo_exit(shell, j, splted) == 0)
			break ;
		if (splted[j] != NULL)
		{
			ptr = splted[j];
			splted[j] = ft_strtrim(splted[j], "$");
			free(ptr);
		}
		if (splted[j] != NULL)
			shell->nb_qot = ft_skip_qote(splted, shell, &j);
		if (test_quotes(shell, &j) == 0)
			return (0);
		ft_print_env_var(shell, splted[j]);
		j++;
	}
	return (1);
}

int	test_quotes(t_struct *shell, int *j)
{
	if (shell->nb_qot == 1)
		*j = *j + 1;
	else if (shell->nb_qot == 0)
		return (0);
	return (1);
}

char	*ft_rm_doler(char **splted, int j)
{
	char	*ptr;

	ptr = splted[j];
	splted[j] = ft_strtrim(splted[j], "$");
	free(ptr);
	return (splted[j]);
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
