/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herDoc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:14:54 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/19 17:32:52 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_check_quotes_frst(t_struct *shell)
{
	char	*fichier1;

	fichier1 = ft_strtrim(&shell->commands[shell->cmp][2], " ");
	if ((((fichier1[0] == '\"' || fichier1[0] == '\'') || \
		(fichier1[ft_strlen(fichier1) - 1] == '\"' || \
		fichier1[ft_strlen(fichier1) - 1] == '\'')) && \
		((ft_strlen(fichier1) == 2) || ft_strlen(fichier1) == 0)) || \
		(ft_strlen(fichier1) == 0))
	{
		printf("fichier1 = %s\n", fichier1);
		ft_putstr_fd("Minishell: : No such file or directory\n", 2);
		return (NULL);
	}
	else if (((fichier1[0] == '\"' || fichier1[0] == '\'') || \
		(fichier1[ft_strlen(fichier1) - 1] == '\"' || \
		fichier1[ft_strlen(fichier1) - 1] == '\'')) && \
		(ft_strlen(fichier1) > 2))
	{
		return (ft_split_cmd2(fichier1, shell));
	}
	return (fichier1);
}

char	*ft_check_quotes_scnd(t_struct *shell)
{
	char	*fichier1;

	fichier1 = ft_strtrim(&shell->commands[shell->cmp][1], " ");
	if ((((fichier1[0] == '\"' || fichier1[0] == '\'') || \
	(fichier1[ft_strlen(fichier1) - 1] == '\"' || \
	fichier1[ft_strlen(fichier1) - 1] == '\'')) && \
	((ft_strlen(fichier1) == 2) || ft_strlen(fichier1) == 0)) || \
	(ft_strlen(fichier1) == 0))
	{
		ft_putstr_fd("Minishell: : No such file or directory\n", 2);
		return (0);
	}
	else if (((fichier1[0] == '\"' || fichier1[0] == '\'') || \
		(fichier1[ft_strlen(fichier1) - 1] == '\"' || \
		fichier1[ft_strlen(fichier1) - 1] == '\'')) && \
		(ft_strlen(fichier1) > 2))
	{
		return (ft_split_cmd2(fichier1, shell));
	}
	return (fichier1);
}

int	ft_play_herdoc(t_struct *shell, char *fichier2, char *line)
{
	(void) shell;
	while (ft_strcmp(line, fichier2))
	{
		free(line);
		line = readline("herDoc> ");
	}
	free(line);
	return (1);
}
