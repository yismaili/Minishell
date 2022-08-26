/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herDoc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:14:54 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/26 17:33:08 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_play_herdoc(t_struct *shell, char *fichier2, char *line)
{
	int		fd;
	int		i;
	int		j;
	char	*rm_dlr;

	shell->inc = 0;
	signals();
	fd = open(fichier2, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (ft_strcmp(line, fichier2))
	{
		free(line);
		line = readline("herDoc> ");
		if (!line)
			return (0);
		j = 0;
		shell->inc = 0;
		while (j < (int)ft_strlen(line))
		{
			if (line[j] == '$')
			{
				if (line[j - 1] == '\"')
					shell->inc++;
				break ;
			}
			j++;
		}
		if (line[ft_strlen(&line[j])] == '\"')
		{
			shell->inc++;
			line = ft_remove_quot(&line[j], '\"', shell);
		}
		i = 0;
		rm_dlr = ft_strtrim(&line[j], "$");
		while (shell->env.tmp_var[i])
		{
			if (!ft_strcmp(shell->env.tmp_var[i], rm_dlr))
			{
				line = ft_strdup(shell->env.tmp_con[i]);
				break ;
			}
				i++;
		}
		if (ft_strlen(line) != ft_strlen(fichier2) && shell->inc <= 1)
			ft_putendl_fd(line, fd);
		else if (shell->inc == 2)
		{
			ft_putchar_fd('\"', fd);
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\"', fd);
			ft_putstr_fd("\n", fd);
		}
	}
	close(fd);
	free(line);
	return (1);
}

int	ft_check_file(t_struct *shell, char	*fichier1)
{
	if (!fichier1)
		return (0);
	if (shell->qot % 2 != 0 || shell->qot_tow == 1)
		return (free(fichier1), 0);
	return (1);
}
