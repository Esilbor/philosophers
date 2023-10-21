/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:08:56 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/20 17:55:46 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Cleans up and destroys allocated mutexes and threads.
void	destroy_mutexes(t_rules *rules, pthread_t *thread)
{
	long int	i;

	i = -1;
	while (++i < rules->nb_forks)
		pthread_mutex_destroy(&rules->mutex_fork[i]);
	pthread_mutex_destroy(&rules->mutex_printf);
	pthread_mutex_destroy(&rules->mutex_start);
	pthread_mutex_destroy(&rules->mutex_death);
	free (rules->mutex_fork);
	free (thread);
}

// Validates input arguments to ensure correct format and count.
int	parsing(int argc, char **argv)
{
	(void)argv;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("invalid arg nb\n", 2);
		return (1);
	}
	if (ft_args_not_digit(argc, argv))
		return (2);
	return (0);
}

// Represents the main behavior cycle of a philosopher thread.
void	*routine(void *philo_void)
{
	t_philo		*philosopher;

	philosopher = (t_philo *)philo_void;
	pthread_mutex_lock(&philosopher->rules->mutex_start);
	pthread_mutex_unlock(&philosopher->rules->mutex_start);
	if (philosopher->id & 1)
		usleep (120);
	while (1)
	{
		if (ft_eat(philosopher))
			break ;
		if (ft_sleep(philosopher))
			break ;
		if (ft_think(philosopher))
			break ;
		usleep(120);
	}
	return (NULL);
}

// Joins philosopher threads, ensuring they complete execution.
int	join_threads(pthread_t *thread, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_join(thread[i], NULL))
		{
			ft_putstr_fd("failed to join thread\n", 2);
			return (3);
		}
		i++;
	}
	return (0);
}

// Initializes and starts philosopher threads, then joins them.
int	launch_threads(pthread_t *thread, t_rules *rules, t_philo *philo)
{
	long int	i;

	philo = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!philo)
	{
		ft_putstr_fd("failed to malloc philosophers\n", 2);
		return (1);
	}
	i = -1;
	while (++i < rules->nb_philo)
		init_philosophers(rules, &philo[i], i);
	i = -1;
	pthread_mutex_lock(&rules->mutex_start);
	while (++i < rules->nb_philo)
	{
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]))
		{
			ft_putstr_fd("failed to create thread\n", 2);
			return (2);
		}
	}
	pthread_mutex_unlock(&rules->mutex_start);
	join_threads(thread, rules);
	free(philo);
	return (0);
}
