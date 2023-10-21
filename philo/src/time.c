/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:31:26 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/20 17:40:38 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Initializes the start time of the simulation
// and computes the boot time in milliseconds.
int	set_boot_time(t_rules *rules)
{
	if (gettimeofday(&rules->start, NULL) < 0)
	{
		ft_putstr_fd("could not set time at start\n", 2);
		return (1);
	}
	rules->boot_time = (rules->start.tv_sec * 1000)
		+ (rules->start.tv_usec / 1000);
	return (0);
}

// Returns the elapsed time in milliseconds since the simulation's boot time.
long	stamp(t_philo *philo)
{
	long			time_now;
	long			time_then;
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
	{
		ft_putstr_fd("could not get timestamp!\n", 2);
		return (0);
	}
	time_now = (time.tv_sec * 1000)
		+ (time.tv_usec / 1000);
	return (time_now - philo->boot_time);
}

// Sleeps the thread for a given time in ms,
// checking periodically if the philosopher died.
// The periodic checks occur every 120 us.
int	ft_usleep(t_philo *philo, long int time_to_do)
{
	long int const	start = stamp(philo);

	while (stamp(philo) < start + time_to_do)
	{
		if (im_dead(philo))
			return (1);
		usleep(950);
	}
	return (0);
}
