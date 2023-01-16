/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:42:57 by amugnier          #+#    #+#             */
/*   Updated: 2023/01/16 17:50:20 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

long int g_addr;

void send_pid(int pid, int value)
{
	int	bit;

	printf("%d\n", value);
	bit = 0;
	while (bit < 32)
	{
		if ((value >> bit) & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		usleep(100);
	}
}

void send_bits(signal)
{
	static int	bit = 0;
	t_client	*data;
	char		c;

	data = (t_client*)(g_addr);
	if (signal == SIGUSR2){
		data->i++;
		c = data->str[data->i];
		if (c == 0)
		{
			data->has_finished = true;
			return ;
		}
		bit = 0;
	}
	if ((c >> bit) & 0x01)
		kill(data->pid, SIGUSR1);
	else
		kill(data->pid, SIGUSR2);
	bit++;
}

/*
void send_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		usleep(100);
	}
}
*/

int stop_all(int signal)
{

}

int	main(int argc, char **argv)
{
	t_client data;

	g_addr = (long int)(&data);
	if (argc == 3)
	{
		data.pid = ft_atoi(argv[1]);
		send_pid(data.pid, getpid());
		signal(SIGUSR1, send_bits);
		signal(SIGUSR2, send_bits);
		data.str = argv[2];
		data.i = 0;
		printf("str:\"%s\"\n", data.str);
//		send_bits(SIGUSR1);
		while (!data.has_finished);
	}
	else
	{
		return (1);
	}
	return (0);
}

/*
regarde
*/
