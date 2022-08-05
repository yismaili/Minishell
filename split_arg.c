/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:16 by souchen           #+#    #+#             */
/*   Updated: 2022/08/05 17:53:52 by yismaili         ###   ########.fr       */
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
