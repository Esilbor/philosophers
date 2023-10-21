/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:56:51 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/21 10:23:11 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Prints the philosopher's action if they're not dead.
int	print_action(t_philo *philo, int action)
{
	if (!im_dead(philo))
	{
		pthread_mutex_lock(&philo->rules->mutex_printf);
		if (action == EAT)
			printf("%ld %ld is eating\n", stamp(philo), philo->id + 1);
		else if (action == THINK)
			printf("%ld %ld is thinking\n", stamp(philo), philo->id + 1);
		else if (action == FORK)
			printf("%ld %ld has taken a fork\n", stamp(philo), philo->id + 1);
		else if (action == SLEEP)
			printf("%ld %ld is sleeping\n", stamp(philo), philo->id + 1);
		else if (action == DIE)
			printf("%ld %ld died\n", stamp(philo), philo->id + 1);
		pthread_mutex_unlock(&philo->rules->mutex_printf);
		return (0);
	}
	else
		return (1);
}

// Makes the philosopher sleep and logs the action.
int	ft_sleep(t_philo *philo)
{
	if (print_action(philo, SLEEP))
		return (1);
	if (ft_usleep(philo, philo->rules->sleep_t))
		return (1);
	return (0);
}

// Makes the philosopher eat and manages the fork locks.
int	ft_eat(t_philo *philo)
{
	if (ft_take_fork(philo))
		return (1);
	philo->last_meal = stamp(philo);
	if (philo->id % 2 == 1)
	{
		if (print_action(philo, EAT))
			return (unlock_odd_forks(philo));
		if (ft_usleep(philo, philo->rules->eat_t))
			return (unlock_odd_forks(philo));
		if (unlock_odd_forks(philo))
			return (1);
	}
	else if (philo->id % 2 == 0)
	{
		if (print_action(philo, EAT))
			return (unlock_even_forks(philo));
		if (ft_usleep(philo, philo->rules->eat_t))
			return (unlock_even_forks(philo));
		if (unlock_even_forks(philo))
			return (1);
	}
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->rules->meal_nb)
		return (1);
	return (0);
}

// Handles a philosopher when dining alone.
int	single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->mutex_fork[philo->id]);
	if (print_action(philo, FORK))
		return (pthread_mutex_unlock(&philo->rules->mutex_fork[philo->id]), 1);
	while (1)
	{
		if (im_dead(philo))
		{
			pthread_mutex_unlock(&philo->rules->mutex_fork[philo->id]);
			return (1);
		}
		usleep(950);
	}
	return (0);
}

// Makes the philosopher think and adjusts sleep if needed.
int	ft_think(t_philo *philo)
{
	if (print_action(philo, THINK))
		return (1);
	if ((philo->rules->eat_t >= philo->rules->sleep_t * 3))
		ft_usleep(philo, philo->rules->eat_t - philo->rules->sleep_t + 950);
	else if (philo->rules->eat_t >= philo->rules->sleep_t)
		ft_usleep(philo, philo->rules->eat_t - philo->rules->sleep_t + 1);
	else
		usleep (1);
	return (0);
}
