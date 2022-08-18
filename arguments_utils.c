/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:07 by souchen           #+#    #+#             */
/*   Updated: 2022/08/18 15:30:06 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_arg	*init_arg(void)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	arg->first = NULL;
	arg->all_cmd = NULL;
	arg->txt_toprint = NULL;
	arg->i = 0;
	arg->init = 0;
	arg->len = 1;
	arg->position = 0;
	return (arg);
}

char	*ft_remove_quot(char *s1, char c)
{
	char	*dst;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dst = NULL;
	len = 0;
	if (!s1 || !c)
		return (NULL);
	while (s1[i])
	{
		if (s1[i] != c)
			len++;
		i++;
	}
	dst = remplir(s1, c, len);
	return (dst);
}

char	*remplir(char *s1, char c, int len)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	dst = (char *) malloc((len + 1) * sizeof(char));
	while (s1[i])
	{
		if (s1[i] != c)
		{
			dst[j] = s1[i];
			j++;
		}
		i++;
	}
	dst[j] = 0;
	return (dst);
}

int	find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle)
			return (i);
		i++;
	}
	return (i);
}

void	check_second_arg(t_struct	*shell)
{
	char	*aux;
	char	**test;
	int		k;

	aux = NULL;
	k = 0;
	if (shell->arguments[1] && (shell->arguments[1][0] == QUOTE \
				|| shell->arguments[1][0] == DOUBLE_QUOTE))
	{
		while (k < (int)ft_strlen(shell->arguments[1]))
		{
			if (shell->arguments[1][k] == '"' || \
					shell->arguments[1][k] == QUOTE)
				shell->arguments[1][k] = '<';
			aux = ft_strtrim(shell->arguments[1], "<");
			k++;
		}
		test = ft_split(aux, '<');
		shell->arguments[1] = test[0];
	}
}
