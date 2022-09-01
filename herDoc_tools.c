/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herDoc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:14:54 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/01 16:31:40 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_play_herdoc(t_struct *shell, char *fichier2, char *line)
{
	int		j;

	shell->fd = open(fichier2, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (ft_strcmp(line, fichier2))
	{
		j = 0;
		free(line);
		line = readline("herDoc> ");
		if (!line)
			return (0);
		line = herdoc_with_dolars(line, fichier2, shell);
		if (shell->inc1 == 2)
			ft_print_msg(shell, line);
		else if (shell->inc2 == 2)
			ft_print_msg(shell, line);
	}
	close(shell->fd);
	free(line);
	return (1);
}

void	ft_print_msg(t_struct *shell, char	*line)
{
	ft_putchar_fd('\"', shell->fd);
	ft_putstr_fd(line, shell->fd);
	ft_putchar_fd('\"', shell-> fd);
	ft_putstr_fd("\n", shell->fd);
	return ;
}

char	*herdoc_with_dolars(char *line, char *fic, t_struct *shell)
{
	int		j;
	char	*tmp;

	shell->inc1 = 0;
	shell->inc2 = 0;
	j = ft_count_len_ofqut(shell, line, fic);
	tmp = ft_hndl_qot(shell, fic, line, j);
	tmp = search_in_env(j, fic, line, shell);
	return (tmp);
}

char	*ft_hndl_qot(t_struct *shell, char *line, char *fic, int j)
{
	char	*tmp;

	tmp = NULL;
	if (line[ft_strlen(&line[j])] == '\"')
	{
		shell->inc1++;
		tmp = line;
		if (shell->inc1 == 2)
			line = ft_split_cmd2(&line[j], shell);
		if (!ft_strcmp(fic, line))
		{
			line = ft_strdup(tmp);
			shell->inc1 = 0;
		}
	}
	if (line[ft_strlen(&line[j])] == '\'')
		tmp = ft_hndl_qot_next(shell, fic, line, j);
	return (tmp);
}

char	*ft_hndl_qot_next(t_struct *shell, char *line, char *fic, int j)
{
	char	*tmp;

	tmp = NULL;
	if (line[ft_strlen(&line[j])] == '\'')
	{
		shell->inc2++;
		tmp = line;
		if (shell->inc2 == 2)
			line = ft_split_cmd2(&line[j], shell);
		if (!ft_strcmp(fic, line))
		{
			line = ft_strdup(tmp);
			shell->inc2 = 0;
		}
	}
	return (tmp);
}

int	ft_count_len_ofqut(t_struct	*shell, char *line, char *fic)
{
	int	j;

	j = 0;
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
			break ;
		}
		j = j + 1;
	}
	return (j);
}

char	*search_in_env(int j, char *fichier2, char *line, t_struct *shell)
{
	int			i;
	char		*rm_dlr;

	i = 0;
	rm_dlr = ft_strtrim(&line[j], "$");
	while (shell->env.tmp_var[i])
	{
		if (!ft_strcmp(shell->env.tmp_var[i], rm_dlr) && \
				ft_strcmp(shell->env.tmp_var[i], &fichier2[1]) && \
				shell->dquote_cmd == 0 && shell->quote_cmd == 0)
		{
			line = shell->env.tmp_con[i];
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
