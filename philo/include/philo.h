/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:32:47 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/21 10:32:54 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define THINK 0
# define FORK 1
# define FORK_2 2
# define EAT 3
# define SLEEP 4
# define DIE 5

typedef struct s_rules
{
	long int		nb_philo;
	long int		nb_forks;
	long int		die_t;
	long int		eat_t;
	long int		sleep_t;
	long int		meal_nb;
	bool			has_died;

	struct timeval	start;
	struct timeval	end;
	long int		boot_time;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_start;
	long int		*fork_tab;

}	t_rules;

typedef struct s_philo
{
	t_rules			*rules;
	struct timeval	start;
	long int		boot_time;
	long int		last_meal;
	long int		meals_eaten;
	long int		id;
	int				group;
	int				death;
	int				my_fork;

}	t_philo;

/*UTILS*/

int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
long	ft_atol(long int *result, char *nptr);

/*UTILS_2*/

int		ft_is_int(int argc, char **argv);
int		ft_args_not_digit(int argc, char **argv);

/*TIME & RULES*/

long	stamp(t_philo *philo);
int		set_boot_time(t_rules *rules);
int		ft_usleep(t_philo *philo, long int time_to_do);

/*INIT*/

int		init_rules(t_rules *rules, int argc, char **argv);
int		init_mutexes(t_rules *rules);
void	init_philosophers(t_rules *rules, t_philo *philo, int i);

/*DEATH*/

bool	im_dead(t_philo *philo);
int		print_death(t_philo *philo);

/*ACTIONS*/

int		print_action(t_philo *philo, int action);
int		ft_sleep(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_think(t_philo *philo);
int		single_philosopher(t_philo *philo);

/*FORKS*/

int		ft_take_fork(t_philo *philo);
int		unlock_even_forks(t_philo *philo);
int		unlock_odd_forks(t_philo *philo);

/*PHILO*/

void	destroy_mutexes(t_rules *rules, pthread_t *thread);
int		parsing(int argc, char **argv);
void	*routine(void *philo_void);
int		join_threads(pthread_t *thread, t_rules *rules);
int		launch_threads(pthread_t *thread, t_rules *rules, t_philo *philo);

#endif
