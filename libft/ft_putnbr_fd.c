/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:59:17 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/11 12:33:38 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_putnbr_fd(long n, int fd)
{
	if (n < 10)
		ft_putchar_fd('0' + n, fd);
	else
	{
		recursive_putnbr_fd(n / 10, fd);
		ft_putchar_fd('0' + n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		recursive_putnbr_fd(-num, fd);
	}
	else
		recursive_putnbr_fd(num, fd);
}

/*#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int fd = open("./test.txt", O_WRONLY);
	ft_putnbr_fd(2147483647, fd);
	close(fd);
} */