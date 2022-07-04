/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:20:07 by souchen           #+#    #+#             */
/*   Updated: 2022/06/22 11:20:56 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"


t_arg	*initial_arg(void)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	arg->first = NULL;
	arg->Lechemin = NULL;
	arg->txt_toprint = NULL;
	arg->i = 0;
	arg->init = 0;
	arg->len = 1;
	arg->position = 0;
	return (arg);
}

void	free_arg(t_arg *arg)
{
	if (arg->first != NULL)
	{
		free(arg->first);
		arg->first = NULL;
	}
	if (arg-> Lechemin != NULL)
	{
		free(arg->Lechemin);
		arg->Lechemin = NULL;
	}
	if(arg-> txt_toprint != NULL)
	{
		free(arg->txt_toprint);
		arg->txt_toprint= NULL;
	}
	free(arg);
}

