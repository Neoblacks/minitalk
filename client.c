/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:19:59 by amugnier          #+#    #+#             */
/*   Updated: 2023/02/04 15:41:05 by amugnier         ###   ########.fr       */
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

void	ft_encode(char **str, unsigned long len, int pid)
{
	unsigned int	bits;

	while (len--)
	{
		bits = 0x80;
		while (bits)
		{
			if (*str[2] & bits)
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(EXIT_FAILURE);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
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

int	ft_parse_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	unsigned long long	len;
	int					pid;

	usleep(50);
	g_signal = 0;
	if (argc != 3)
	{
		ft_printf("Error: Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (ft_strstr(argv[1], "") == EXIT_SUCCESS)
	{
		ft_printf("Error: Wrong PID\n");
		return (EXIT_FAILURE);
	}
	if (argv[2] == NULL)
	{
		ft_printf("Error: Wrong string\n");
		return (EXIT_FAILURE);
	}
	len = ft_strlen(argv[2]) + 1;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = &ft_handler;
	sigaction(SIGUSR2, &act, 0);
	sigaction(SIGUSR1, &act, 0);
	if (ft_parse_arg(argv[1]) == EXIT_FAILURE)
	{
		ft_printf("Error: Wrong PID\n");
		return (EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	ft_encode(argv, len, pid);
	return (0);
}
