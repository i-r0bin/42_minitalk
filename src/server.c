/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:58:05 by rilliano          #+#    #+#             */
/*   Updated: 2023/09/01 13:36:58 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./libft/libft.h"

void	ft_handler(int sig)
{
	static int				bit = 0;
	static unsigned char	i = 0;

	i |= (sig == SIGUSR2);
	if (++bit == 8)
	{
		bit = 0;
		if (!i)
		{
			ft_putchar_fd('\n', 1);
			return ;
		}
		ft_putchar_fd(i, 1);
		i = 0;
	}
	else
		i <<= 1;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
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
