/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:12:29 by rilliano          #+#    #+#             */
/*   Updated: 2023/09/01 15:10:02 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./libft/libft.h"

static void	ft_act(int sig)
{
	static int	rec = 0;

	if (sig == SIGUSR1)
		++rec;
	else
	{
		ft_putnbr_fd(rec, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

void	ft_send_bit(int pid, unsigned char bit)
{
	if (bit)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	usleep(500);
}

void	ft_send(int pid, const char *str)
{
	int	bit;
	int	i;

	i = 0;
	while (str[i])
	{
		bit = 8;
		while (bit--)
			ft_send_bit(pid, ((unsigned char)str[i] >> bit) & 1);
		i++;
	}
	bit = 8;
	while (bit--)
		ft_send_bit(pid, 0);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_putstr_fd("Error.\nTry:\t./client_bonus <PID> \"MESSAGE\"\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_putstr_fd("Sending: \t", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putstr_fd("\nReceived:\t", 1);
	sa.sa_handler = &ft_act;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error Sigaction.\n", 1);
		return (1);
	}
	ft_send(pid, argv[2]);
	return (0);
}
