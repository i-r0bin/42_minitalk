/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:17:56 by rilliano          #+#    #+#             */
/*   Updated: 2023/09/01 15:10:43 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./libft/libft.h"

void	ft_handler(int sig, siginfo_t *info, void *s)
{
	static int				bit = 0;
	static unsigned char	i = 0;

	(void)s;
	i |= (sig == SIGUSR2);
	if (++bit == 8)
	{
		bit = 0;
		if (!i)
		{
			ft_putchar_fd('\n', 1);
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		ft_putchar_fd(i, 1);
		i = 0;
		kill(info->si_pid, SIGUSR1);
	}
	else
		i <<= 1;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error Sigaction.\n", 1);
		return (1);
	}
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
