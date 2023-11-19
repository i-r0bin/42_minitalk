/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:54:17 by rilliano          #+#    #+#             */
/*   Updated: 2023/09/01 15:09:44 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./libft/libft.h"

void	ft_send_bit(int pid, unsigned int bit)
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
	int	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Error.\nTry:\t./client <PID> \"MESSAGE\"\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_putstr_fd("Sending: ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_send(pid, argv[2]);
	return (0);
}
