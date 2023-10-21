/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:14:22 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/20 13:03:21 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Unlocks the forks for an even-indexed philosopher.
int	unlock_even_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->mutex_fork[(philo->id + 1)
		% (philo->rules->nb_philo)]);
	pthread_mutex_unlock(&philo->rules->mutex_fork[philo->id]);
	return (0);
}

// Unlocks the forks for an odd-indexed philosopher.
int	unlock_odd_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->mutex_fork[philo->id]);
	pthread_mutex_unlock(&philo->rules->mutex_fork[(philo->id + 1)
		% (philo->rules->nb_philo)]);
	return (0);
}

// Even-indexed philosopher attempts to take both forks.
int	even_takes_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->mutex_fork[philo->id]);
	if (print_action(philo, FORK))
		return (pthread_mutex_unlock
			(&philo->rules->mutex_fork[philo->id]), 1);
	pthread_mutex_lock(&philo->rules->mutex_fork
	[(philo->id + 1) % (philo->rules->nb_philo)]);
	if (print_action(philo, FORK))
		return (unlock_even_forks(philo), 1);
	return (0);
}

// Odd-indexed philosopher attempts to take both forks.
int	odd_takes_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->mutex_fork
	[(philo->id + 1) % (philo->rules->nb_philo)]);
	if (print_action(philo, FORK))
		return (pthread_mutex_unlock(&philo->rules->mutex_fork
				[(philo->id + 1) % (philo->rules->nb_philo)]), 1);
	pthread_mutex_lock(&philo->rules->mutex_fork[philo->id]);
	if (print_action(philo, FORK))
		return (unlock_odd_forks(philo), 1);
	return (0);
}

// Handles fork-taking logic based on philosopher's index.
int	ft_take_fork(t_philo *philo)
{
	if (philo->rules->nb_philo != 1)
	{
		if (philo->id % 2 == 0)
			return (even_takes_forks(philo));
		else if (philo->id % 2 == 1)
			return (odd_takes_forks(philo));
	}
	else
		return (single_philosopher(philo));
	return (0);
}
