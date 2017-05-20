/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:55:34 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:55:38 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
** Uses EXIT will check and print if an error was reported. 
** Uses THROW(err) will report an error and returns FAIL.
** Uses PERROR(msg) will report an error and write directly on stderr.
** Uses PUTERROR(msg) will write directly on stderr without report.
** Uses CATCH(dic) will handle the error dictonary.
** Uses ERROR will check if an error was report.
** WARNING : a dictionary should finish with SUCCESS key value.
*/

# include "ft_printf.h"

# define ERROR			error_check()
# define EXIT			error_catch(0)
# define THROW(err)		error_throw(err)
# define PERROR(msg) 	error_print(msg)
# define CATCH(dic)		error_catch(dic)
# define PUTERROR(a)	ft_fprintf(2, "{r:1:%s} {w:1:%s}\n", "Error:", a)

/*
** Enum
*/

typedef enum			e_enum_ret
{
	FAIL = -1,
	SUCCESS = 0
}						t_enum_ret;

/*
** Struct
*/

typedef struct			s_error
{
	t_enum_ret			num;
	char				msg[128];
}						t_error;

/*
** Dictionary
*/

typedef struct			s_dict_error
{
	int					key;
	char				*value;
}						t_dict_error;

int						error_check(void);
int						error_throw(int num);
int						error_catch(t_dict_error *dic);
int						error_print(char *msg);

#endif
