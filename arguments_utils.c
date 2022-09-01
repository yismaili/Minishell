/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:07 by souchen           #+#    #+#             */
/*   Updated: 2022/08/28 12:41:46 by souchen          ###   ########.fr       */
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

char	*ft_remove_quot(char *s1, char c, t_struct *shell)
{
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	if (!s1 || !c)
		return (NULL);
	while (s1[i])
	{
		if (s1[i] != c)
			len++;
		i++;
	}
	return (remplir(s1, c, len, shell));
}

char	*remplir(char *s1, char c, int len, t_struct *shell)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	shell->qot = 0;
	dst = (char *) malloc((len + 1) * sizeof(char));
	while (s1[i])
	{
		if (s1[i] != c)
		{
			dst[j] = s1[i];
			j++;
		}
		else
			shell->qot++;
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

void	cmp_q(t_struct *shell)
{
	int	i;

	i = 0;
	shell->dquote_cmd = 0;
	shell->quote_cmd = 0;
	while (shell->commands[shell->cmp][i] != '\0')
	{
		if (shell->commands[shell->cmp][i] == '\"')
			shell->dquote_cmd++;
		else if (shell->commands[shell->cmp][i] == '\'')
			shell->quote_cmd++;
		if (!ft_isalpha(shell->commands[shell->cmp][i]))
			shell->not_alpha2++;
		i++;
	}
}
