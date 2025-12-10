/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:52:06 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/27 09:31:24 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(va_list ap, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		return ((ft_putchar(va_arg(ap, int))));
	if (c == 's')
		return ((ft_putstr(va_arg(ap, char *))));
	if (c == 'p')
		return (ft_printadress((unsigned long)va_arg(ap, void *)));
	if (c == 'd')
		return (ft_putnbr(va_arg(ap, int)));
	if (c == 'i')
		return ((ft_putnbr(va_arg(ap, int))));
	if (c == 'u')
		return (ft_putunbr(va_arg(ap, unsigned int)));
	if (c == 'x')
		return (ft_puthexlow(va_arg(ap, int)));
	if (c == 'X')
		return (ft_puthexupp(va_arg(ap, int)));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_format(ap, format[i + 1]);
			i += 2;
		}
		else
		{
			count += ft_putchar(format[i]);
			i++;
		}
	}
	va_end(ap);
	return (count);
}

//int main(void)
//{
//	char *str = "abcde";
//	int n = 65;
//	char c = 36;
//	int hex = 632435;
//	unsigned int nb = 730;
//	void *ptr;
//	ptr = malloc(1);
//	char p = 'e';
//	ptr = &p;
//	printf("Test %%p : \n");
//	printf("\n%d\n\n", ft_printf("%p", ptr));
//	printf("\n%d\n\n", printf("%p", ptr));
//	printf("Fin du test");
//	printf("\nTest %%s : \n");
//	printf("\n%d\n\n", ft_printf("%s", str));
//	printf("\n%d\n\n", printf("%s", str));
//	printf("Fin du test");
//	printf("\nTest %%d : \n");
//	printf("\n%d\n\n", ft_printf("%s", str));
//	printf("\n%d\n\n", printf("%s", str));
//	printf("Fin du test");
//	printf("\nTest %%d : \n\n");
//	printf("\n%d\n\n", ft_printf("%d", n));
//	printf("\n%d\n\n", printf("%d", n));
//	printf("Fin du test");
//	printf("\nTest %%c : \n");
//	printf("\n%d\n\n", ft_printf("%c", c));
//	printf("\n%d\n\n", printf("%c", c));
//	printf("Fin du test");
//	printf("\nTest %%x : \n");
//	printf("\n%d\n\n", ft_printf("%x", hex));
//	printf("\n%d\n\n", printf("%x", hex));
//	printf("Fin du test");
//	printf("\nTest %%X : \n");
//	printf("\n%d\n\n", ft_printf("%X", hex));
//	printf("\n%d\n\n", printf("%X", hex));
//	printf("Fin du test");
//	printf("\nTest %%u : \n");
//	printf("\n%d\n\n", ft_printf("%u", nb));
//	printf("\n%d\n\n", printf("%u", nb));
//	printf("Fin du test");	
//	printf("\nTest pour tout : \n");
//	printf("\n%d\n\n", ft_printf("%p, %s, %d, %c, %x, %X, %u",
// ptr, str, n, c, hex, hex, nb));
//	printf("\n%d\n\n", printf("%p, %s, %d, %c, %x, %X, %u",
// ptr, str, n, c, hex, hex, nb));
//	printf("Fin du test\n");
//	return (0);
//}
