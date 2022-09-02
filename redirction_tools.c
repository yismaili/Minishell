/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirction_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:37:25 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/02 01:20:12 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_next_redirection(t_struct *shell, int size)
{
	char	*tmp;

	if (shell->not_alpha2 == (int)ft_strlen(shell->commands[shell->cmp]))
		return (ft_not_found(shell->commands[shell->cmp]), 0);
	if (cas_error_quote(shell, size) == 0)
		return (0);
	if (shell->quote_cmd != 0 || shell->dquote_cmd != 0)
	{
		tmp = shell->commands[shell->cmp];
		shell->commands[shell->cmp] = \
			ft_split_cmd3(shell->commands[shell->cmp], shell);
		free(tmp);
	}
	if (shell->commands[shell->cmp][0] == '>')
		if (outredirection(shell) == 0)
			return (0);
	if (shell->commands[shell->cmp][0] == '<')
		if (inredirection(shell) == 0)
			return (0);
	return (1);
}

int	ft_count_len_ofqut(t_struct	*shell, char *line, char *fic)
{
	int	j;

	j = 0;
	shell->inc1 = 0;
	shell->inc2 = 0;
	while (j < (int)ft_strlen(line) && ft_strcmp(line, fic))
	{
		if (line[j] == '$')
		{
			shell->inc1 = 0;
			shell->inc2 = 0;
			if (j >= 1)
			{
				if (line[j - 1] == '\"')
					shell->inc1++;
				if (line[j - 1] == '\'')
					shell->inc2++;
			}
			return j;
		}
		j = j + 1;
	}
	return (0);
}

char	*search_in_env(int j, char *fichier2, char *line, t_struct *shell)
{
	int			i;
	char		*rm_dlr;
	char	*tmp;

	i = 0;
	rm_dlr = ft_strtrim(&line[j], "$");
	while (shell->env.tmp_var[i])
	{
		if (!ft_strcmp(shell->env.tmp_var[i], rm_dlr) && \
				ft_strcmp(shell->env.tmp_var[i], &fichier2[1]) && \
				shell->dquote_cmd == 0 && shell->quote_cmd == 0)
		{
			tmp = line;
			line = ft_strdup(shell->env.tmp_con[i]);
			free(tmp);
			break ;
		}
		i++;
	}
	if (ft_strcmp(line, fichier2) && shell->inc1 <= 1 && shell->inc2 <= 1)
		ft_putendl_fd(line, shell->fd);
	free(rm_dlr);
	return (line);
}

int	ft_check_file(t_struct *shell, char	**fichier1)
{
	if (!fichier1)
		return (0);
	if (shell->qot % 2 != 0 || shell->qot_tow == 1)
		return (free(fichier1), 0);
	return (1);
}

int	red_with_dolar(char *fichier, t_struct *shell)
{
	int	i;

	i = 0;
	if (fichier[0] == '$')
	{
		while (shell->env.tmp_var[i])
		{
			if (!ft_strcmp(shell->env.tmp_var[i], &fichier[1]))
			{
				ft_putstr_fd("bash:", 2);
				ft_putstr_fd(shell->env.tmp_con[i], 2);
				ft_putstr_fd(" Is a directory\n", 2);
				return (0);
			}
			i++;
		}
		if (ft_strcmp(shell->env.tmp_var[i - 1], &fichier[1]))
		{
			ft_putstr_fd("bash:", 2);
			ft_putstr_fd(fichier, 2);
			ft_putstr_fd(" ambiguous redirect\n", 2);
			return (0);
		}
	}
	return (1);
}
