/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:10:31 by amugnier          #+#    #+#             */
/*   Updated: 2023/01/16 17:33:19 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include "libft/libft.h"
# include <stdbool.h>

# define BUFF_SIZE 1000

/*
	buffer[BUFFSIZE];
	buffer[i] = c

	ft_join()

	||||||||||||||||
	char *str;

	str = malloc(sizeof(char) * BUFFSIZE)
	str[i] = c

	if (i == BUFFSIZE){
		char *tmp = ft_join(data->str, malloc(BUFF_SIZE));
		free(data->str);
		data->str = tmp;
	}
*/


typedef struct s_serv
{
	char	*str; //Chaine finale de caracter;
	bool	has_pid;
	bool	finished;
	int		pid;
}	t_serv;

typedef struct s_client
{
	char	*str;
	int		i;
	int		pid;
	bool	has_finished;
}	t_client;

#endif
