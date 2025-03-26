/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xviladri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:20:30 by xviladri          #+#    #+#             */
/*   Updated: 2025/03/26 19:21:13 by xviladri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_putstr(char *str)
{
	int	written;
	int	i;
	written = 0;
	i = 0;
	if (!str)
	{
		written += write(1, "(null)", 6);
		return (written);
	}
	while (str[i])
		written += write(1, &str[i++], 1);
	return (written);
}

int	ft_putnbr_base(int number, char *base, int size)
{
	unsigned int	num;
	int	written;
	written = 0;
	if (number == -2147483648 && size == 10)
		return (write(1, "-2147483648", 11));
	if (number < 0 && size == 10)
	{
		num = number * -1;
		written++;
		write(1, "-", 1);
	}
	else
		num = number;
	if (num > (unsigned int)size)
		written += ft_putnbr_base(num / size, base, size);
	write(1, &base[num % size], 1);
	return (written + 1);
}

int	ft_printf(const char *str, ...)
{
	int	written;
	int	i;
	va_list	args;
	written = 0;
	i = 0;
	if (!str || !*str)
		return (0);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[++i])
		{
			if (str[i] == '%')
				written += write(1, "%", 1);
			if (str[i] == 's')
				written += ft_putstr(va_arg(args, char *));
			if (str[i] == 'd')
				written += ft_putnbr_base(va_arg(args, unsigned int), "0123456789", 10);
			if (str[i] == 'x')
				written += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", 16);
		}
		else
			written += write(1, &str[i], 1);
		i++;
	}
	return (va_end(args), written);
}
