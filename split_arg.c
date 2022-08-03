/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/08/03 16:28:42 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_split_cmd(char	*cmd)
{
	char	*join;

	join = NULL;
	if (ft_strchr(cmd, '\"'))
		join = ft_remove_quot(cmd, '\"');
	else if (ft_strchr(cmd, '\''))
		join = ft_remove_quot(cmd, '\'');
	return (join);
}

void	cmd_splited(char **spled, t_struct *shell)
{
	int		i;
	int		j;
	int		size;
	char	*apt;

	apt = NULL;
	i = 0;
	j = 0;
	shell->cmd_splited = (char **)malloc(sizeof(char *) * 1000000);
	while (spled[i])
	{
		shell->cmd_splited[i] = ft_strdup(spled[i]);
		size = (int)ft_strlen(shell->cmd_splited[0]);
		if (shell->cmd_splited[0][size] == ' ')
		{
			while (j < (int)ft_strlen(shell->cmd_splited[0]) - 1)
			{
				apt[j] = shell->cmd_splited[0][j];
				j++;
			}
			shell->cmd_splited[i] = ft_strdup(apt);
		}
		i++;
	}
}
