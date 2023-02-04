/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:19:32 by amugnier          #+#    #+#             */
/*   Updated: 2023/02/04 11:30:14 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_str;

void	ft_get_pid(void)
{
	ft_printf("PID: %d\n", getpid());
}

char	*ft_print_first(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_join_char(char *str, char c)
{
	char				*new;
	unsigned long long	i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_print_first(c));
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}

void	ft_print_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned int	bits = 0x80;
	static char			symbol = 0;

	(void)context;
	if (sig == SIGUSR1)
		symbol += bits;
	bits >>= 1;
	if (!bits)
	{
		if (!symbol)
		{
			ft_printf("%s\n", g_str);
			kill(info->si_pid, SIGUSR2);
			free(g_str);
			g_str = 0;
		}
		else
			g_str = ft_join_char(g_str, symbol);
		bits = 0x80;
		symbol = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &ft_print_signal;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_get_pid();
	while (1)
		continue ;
}
