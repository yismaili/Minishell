/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:07 by souchen           #+#    #+#             */
/*   Updated: 2022/08/06 18:22:56 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_arg	*init_arg(void)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
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
