/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:00:34 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 18:00:36 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int			error_check(void)
{
	t_error		error;

	error = error_sglt(0, 0, 0);
	return (error.num);
}

int			error_throw(int domain)
{
	error_sglt(domain, 0, 1);
	return (FAIL);
}

int			error_catch(t_dic_error dic[])
{
	int			error;
	int			i;

	i = 0;
	error = error_exit();
	if (error <= SUCCESS)
		return (error);
	while (dic[i].key)
	{
		if (dic[i].key == error)
		{
			PUTERROR(dic[i].value);
			return (error);
		}
		i++;
	}
	return (error);
}

int			error_exit(void)
{
	t_error		error;

	error = error_sglt(0, 0, 0);
	if (error.num == SUCCESS)
		return (SUCCESS);
	else if (error.num == FAIL)
		ft_fprintf(2, "{r:1:%s} {w:1:%s}\n", "ERROR:", error.msg);
	return (error.num);
}

t_error		error_sglt(int num, char *msg, int action)
{
	static t_error	sglt = {0, 0};

	if (action == 1)
	{
		sglt.num = num;
		ft_strdel(&sglt.msg);
		sglt.msg = (!msg) ? msg : ft_strdup(msg);
	}
	return (sglt);
}
