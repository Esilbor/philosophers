/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:50:53 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/20 16:40:12 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Initializes simulation rules from cmd arguments.
int	init_rules(t_rules *rules, int argc, char **argv)
{
	if (!parsing(argc, argv) && !ft_is_int(argc, argv))
	{
		if (!ft_atol(&rules->nb_philo, argv[1]) || rules->nb_philo <= 0)
			return (ft_putstr_fd("invalid nb of philosophers\n", 2), 5);
		if (!ft_atol(&rules->nb_forks, argv[1]) || rules->nb_forks == 0)
			return (ft_putstr_fd("null arg invalid\n", 2), 5);
		if (!ft_atol(&rules->die_t, argv[2]) || rules->die_t == 0)
			return (ft_putstr_fd("null time to die invalid\n", 2), 5);
		if (!ft_atol(&rules->eat_t, argv[3]) || rules->eat_t == 0)
			return (ft_putstr_fd("null time to eat invalid\n", 2), 5);
		if (!ft_atol(&rules->sleep_t, argv[4]) || rules->sleep_t == 0)
			return (ft_putstr_fd("null time to sleep invalid\n", 2), 5);
		rules->has_died = 0;
		if (argc == 6)
		{
			if (!ft_atol(&rules->meal_nb, argv[5]) || rules->meal_nb == 0)
				return (ft_putstr_fd("null arg invalid\n", 2), 5);
		}
		else
			rules->meal_nb = -1;
		return (0);
	}
	return (5);
}

// Allocates and initializes mutexes based on rule settings.
int	init_mutexes(t_rules *rules)
{
	long int	i;

	i = 0;
	rules->mutex_fork = malloc(sizeof(pthread_mutex_t) * rules->nb_forks);
	if (!rules->mutex_fork)
		return (2);
	while (i < rules->nb_forks)
	{
		pthread_mutex_init(&rules->mutex_fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->mutex_printf, NULL);
	pthread_mutex_init(&rules->mutex_start, NULL);
	pthread_mutex_init(&rules->mutex_death, NULL);
	return (0);
}

// Initializes philosopher's properties and state.
void	init_philosophers(t_rules *rules, t_philo *philo, int i)
{
	philo->rules = rules;
	philo->start = rules->start;
	philo->boot_time = rules->boot_time;
	philo->id = i;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	philo->my_fork = 0;
	if (rules->nb_philo % 2 && (philo->id + 1) == rules->nb_philo)
		philo->group = 2;
	else
		philo->group = ((philo->id + 1) % 2);
}
