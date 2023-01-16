/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:42:55 by amugnier          #+#    #+#             */
/*   Updated: 2023/01/16 17:46:42 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

long int	g_addr = 0;
//t_serv_data g_data;
// t_serv g_data;

// void	confirmation_buffer(int signal, int buffer[1000])
// {
// 	static int	bit;
// 	static int	i;
// 	static char	buffer[1000];
// 	static int	index;

// 	if (signal == SIGUSR1)
// 		i |= (0x01 << bit);
// 	bit++;
// 	if (bit == 8)
// 	{
// 		buffer[index] = i;
// 		index++;
// 		bit = 0;
// 		i = 0;
// 	}
// 	if (buffer[index - 1] == '\0')
// 	{
// 		printf("%s", buffer);
// 		index = 0;
// 	}
// }

/*
*/

void	confirmation(int signal)
{
	static int	bit = 0;//[0-7]
	static unsigned int	i = 0;
	char	*tmp;
	t_serv	*ptr;

	ptr = ((t_serv *)g_addr);
	if (signal == SIGUSR1)
		i |= (1u << bit);
	bit++;
	if (bit == 8)
	{
		if (i == 0){
			ptr->finished = true;
			return ;
		}
/*		if (data->i % BUFF_SIZE == 0)
		{
			tmp = malloc(BUFF_SIZE + 1 + ft_strlen(data->str))
			data->str = malloc(sizeof(char) * (BUFFSIZE + 1));
		}*/
		write(1, &i, 1);
		bit = 0;
		i = 0;
		if (signal == SIGUSR1)
			i = 1;
		kill(ptr->pid, SIGUSR2);
		return ;
	}
	kill(ptr->pid, SIGUSR1);
}

void	get_message()
{
	t_serv	*data;

	data = ((t_serv *)g_addr);
	data->str = malloc(BUFF_SIZE);


	signal(SIGUSR1, confirmation);
	signal(SIGUSR2, confirmation);
	kill(SIGUSR1, data->pid);
	while (!data->finished);
}

void confirm_pid(int signal)
{
	static int bit = 0;
	t_serv *ptr;

	ptr = ((t_serv *)g_addr);
	if (bit == 0)
	{
		ptr->pid = 0;
		ptr->has_pid = false;
	}
	if (signal == SIGUSR1)
		ptr->pid |= (0x01 << bit);
	bit++;
	if (bit == 32)
	{
		printf("%d\n", ptr->pid);
		bit = 0;
		ptr->has_pid = true;
	}
}

int	get_client_pid(void)//int signal
{
	int pid = 0;
	t_serv	*ptr;
	// static int	bit = 0;
	// static int	i = 0;
	signal(SIGUSR1, confirm_pid);
	signal(SIGUSR2, confirm_pid);

	ptr = ((t_serv *)g_addr);
	while (!ptr->has_pid);
	// if (signal == SIGUSR1)
	// 	i |= (0x01 << bit);
	// bit++;
	// if (bit == 32)
	// {
	// 	printf("%d", i);
	// 	return (i);
	// 	bit = 0;
	// 	i = 0;
	// }
	return (pid);
}

void ft_ceciestuntest(int signal)
{
	t_serv	*data;

	data = (t_serv*)g_addr;
	free(data->str);
	exit (0);
}

int main(int argc, char **argv)
{
	int	pid;
	t_serv data;
	//int	i;
	// static int buffer[1000];
	(void)argv;

	g_addr = (long int)&data;
	signal(SIGINT, ft_ceciestuntest);
	//i = 0;
	//signal(SIGUSR1, get_client_pid);
	// while (i < 32)
	// {
	// 	client_pid = get_client_pid();
	// 	i++;
	// }
	// printf("%d\n", client_pid);
	if (argc != 1)
		return (1);
	pid = getpid();
	printf("PID: %d \n", pid);
	// signal(SIGUSR1, confirmation);
	// signal(SIGUSR2, confirmation);
	while (1)
	{
		get_client_pid();
		get_message();//faut le coder maintenant
	}
	return (0);
}
