/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:35:55 by jhauvill          #+#    #+#             */
/*   Updated: 2025/11/27 12:57:22 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_putnbr(int n);
int	ft_putstr(char *s);
int	ft_len_nbr( long int n);
int	ft_strlen_printf(char *str);
int	ft_putchar(char c);
int	ft_puthexlow(unsigned int n);
int	ft_puthexupp(unsigned int n);
int	ft_putunbr(unsigned int n);
int	ft_printadress(unsigned long address);
int	ft_printhex(unsigned long address, char *base);
int	ft_printf(const char *format, ...);
int	ft_format(va_list ap, char c);

#endif