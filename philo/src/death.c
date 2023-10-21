/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:11:42 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/20 17:14:54 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Logs the death of a philosopher.
int	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->mutex_printf);
	printf("%ld %ld died\n", stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->rules->mutex_printf);
	return (0);
}

// Checks if the philosopher has exceeded their time to eat and died.
bool	im_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->mutex_death);
	if (philo->rules->has_died)
	{
		pthread_mutex_unlock(&philo->rules->mutex_death);
		return (true);
	}
	if (stamp(philo) >= philo->last_meal + philo->rules->die_t)
	{
		philo->rules->has_died = true;
		usleep(120);
		print_death(philo);
		pthread_mutex_unlock(&philo->rules->mutex_death);
		return (true);
	}
	pthread_mutex_unlock(&philo->rules->mutex_death);
	return (false);
}
