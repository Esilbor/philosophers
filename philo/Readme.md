# Dining Philosophers Problem

## Header
- **Import** necessary libraries
- **Define** constants

## Structures

### s_rules
- `number of philosophers`
- `number of forks`
- `time to die`
- `time to eat`
- `time to sleep`
- `number of meals`
- `death flag`
- `timing variables` (start, end, boot time)
- `mutexes` for printing, death, and forks
- `fork status table`

### s_philo
- `reference to rules`
- `start time`
- `boot time`
- `last meal time`
- `meals eaten count`
- `philosopher ID`
- `group`
- `death status`
- `assigned fork`

## Functions

### stamp(t_philo *philo)
- **Get** the current time
- **Subtract** the boot time
- **Return** the elapsed time

### ft_usleep(t_philo *philo, time_to_sleep)
- **Sleep** in small increments while checking for philosopher's death
- **Return** if philosopher is dead

### im_dead(t_philo *philo)
- **Check** if philosopher died
- If died due to not eating, **print** and set death flag
- **Return** death status

### print_action(t_philo *philo, action)
- **Lock** the print mutex
- **Print** the relevant action based on the action code (e.g., EAT, THINK)
- **Unlock** the print mutex

### init_philosophers(t_rules *rules, t_philo *philo, index)
- **Initialize** the philosopher's properties

### unlock_even_forks(t_philo *philo)
- **Unlock** the forks for an even-indexed philosopher

### unlock_odd_forks(t_philo *philo)
- **Unlock** the forks for an odd-indexed philosopher

### ft_take_fork(t_philo *philo)
- If philosopher is even, **try** to take both forks in one order
- If philosopher is odd, **try** to take both forks in the opposite order
- If there's only one philosopher, handle special case

### ft_eat(t_philo *philo)
- **Attempt** to take forks
- **Update** last meal time
- **Print** eat action and sleep for eating duration
- **Unlock** forks based on philosopher's index
- **Increment** meals eaten count

### ft_sleep(t_philo *philo)
- **Print** sleep action and sleep for the given duration

### ft_think()
- **Print** think action

### routine(void *philo_void)
- **While** philosopher hasn't died:
    - Think
    - Try to eat
    - Sleep

## Main Thread Management

- **Initialize** philosophers and rules
- **Launch** threads for each philosopher to run the routine
- **Wait** for threads to finish
- **Clean up** resources
