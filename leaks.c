/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:12 by souchen           #+#    #+#             */
/*   Updated: 2022/07/30 15:10:31 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
}
void	free_commande(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
}

void	free1(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free2(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}
