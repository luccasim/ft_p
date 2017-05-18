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
** Uses EXIT in the main return and PERROR, for handle simple error
** Uses THROW, CATCH, and dictionary for handle details errors.
** Uses PERROR(msg) will set an error with a message
** Uses THROW(err) will set a e_error and return FAIL
** Uses CATCH(dic) will handle all e_error and return the error
** Uses ERROR will check if the singleton contain an error
** WARNING : a dictionary should finish with SUCCESS key value.
*/

# include "ft_printf.h"
# include "libft.h"

# define THROW(err)		error_throw(err)
# define PERROR(msg) 	error_sglt(FAIL, msg, 1)
# define CATCH(dic)		error_catch(dic)
# define ERROR			error_check()
# define EXIT			error_exit()

# define PUTERROR(a)	ft_fprintf(2, "{w:1:%s}\n", a)

typedef enum			e_error
{
	FAIL = -1,
	SUCCESS = 0
}						t_e_error;

typedef struct			s_error
{
	t_e_error			num;
	char				*msg;
}						t_error;

typedef struct			s_dic_error
{
	int					key;
	char				*value;
}						t_dic_error;

t_error					error_sglt(int num, char *msg, int action);
int						error_check(void);
int						error_throw(int num);
int						error_catch(t_dic_error *dic);
int						error_exit(void);

#endif
