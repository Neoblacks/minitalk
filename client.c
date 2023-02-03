/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:19:59 by amugnier          #+#    #+#             */
/*   Updated: 2023/02/03 17:17:21 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_signal;

int	ft_strstr(const char *str, char *comp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '\0' && comp[j] == '\0')
		return (EXIT_SUCCESS);
	while (str[i] != '\0')
	{
		while (str[i + j] == comp[j] && str[i + j] != '\0' && comp[j] != '\0')
			j++;
		if (comp[j] == '\0' && str[i + j] == '\0')
			return (EXIT_SUCCESS);
		else
			j = 0;
		i++;
	}
	return (EXIT_FAILURE);
}

void	ft_handler(int signum)
{
	if (signum == SIGUSR2)
		ft_printf("Signal received\n");
	else
		g_signal = 1;
}

void	ft_encode(char **str, unsigned long len)
{
	unsigned int	bits;

	while (len--)
	{
		bits = 0x80;
		while (bits)
		{
			if (*str[2] & bits)
			{
				if (kill(ft_atoi(str[1]), SIGUSR1) == -1)
					exit(EXIT_FAILURE);
			}
			else
			{
				if (kill(ft_atoi(str[1]), SIGUSR2) == -1)
					exit(EXIT_FAILURE);
			}
			while (g_signal == 0)
				pause();
			g_signal = 0;
			bits >>= 1;
		}
		str[2]++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	unsigned long long	len;

	usleep(50);
	g_signal = 0;
	if (argc != 3)
	{
		ft_printf("Error: Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	if ((ft_strstr(argv[1], "-1")) == EXIT_SUCCESS)
	{
		ft_printf("Error: Wrong PID\n");
		return (EXIT_FAILURE);
	}
	len = ft_strlen(argv[2]) + 1;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = &ft_handler;
	sigaction(SIGUSR2, &act, 0);
	sigaction(SIGUSR1, &act, 0);
	ft_encode(argv, len);
	return (0);
}
