/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:34:26 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/20 17:48:59 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_philo		philo;
	pthread_t	*thread;
	int			i;

	i = 0;
	if (!init_rules(&rules, argc, argv))
	{
		thread = malloc(sizeof(pthread_t) * rules.nb_philo);
		if (!thread)
			return (1);
		init_mutexes(&rules);
		if (set_boot_time(&rules))
		{
			ft_putstr_fd("failed to set_boot_time\n", 2);
			return (1);
		}
		if (launch_threads(thread, &rules, &philo))
		{
			free (thread);
			ft_putstr_fd("failed to launch_threads\n", 2);
		}
		destroy_mutexes(&rules, thread);
	}
	return (0);
}
