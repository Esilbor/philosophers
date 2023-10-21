/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:48:52 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/20 14:30:30 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Ensures command-line arguments don't exceed INT_MAX.
int	ft_is_int(int argc, char **argv)
{
	int			i;
	long int	j;

	i = 1;
	while (i < argc && argv[i])
	{
		j = ft_atol(&j, argv[i]);
		if (j > INT_MAX)
		{
			printf("values cannot exceed INT_MAX\n");
			return (4);
		}
		i++;
	}
	return (0);
}

// Validates command-line arguments are purely digits.
int	ft_args_not_digit(int argc, char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 0;
	flag = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') || !argv[i][j])
			{
				printf("arg %d is invalid : only digits allowed\n", i);
				flag++;
				break ;
			}
			else
				j++;
		}
		i++;
		j = 0;
	}
	return (flag);
}
