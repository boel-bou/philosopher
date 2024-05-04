/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:16:28 by boel-bou          #+#    #+#             */
/*   Updated: 2024/05/02 23:16:31 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clear_struct(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	free(data->philos);
	free(data->pids);
}

void	ft_exit(int i, t_data *data)
{
	clear_struct(data);
	if (i == 0)
		exit (0);
	else
		exit (1);
}

void	*checker_routine(void *arg)
{
	t_philo		*philo;
	long long	last_eat;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(100);
		sem_wait(philo->done);
		last_eat = philo->data->last_eat.tv_sec * 1000
			+ philo->data->last_eat.tv_usec / 1000;
		sem_post(philo->done);
		if (gtime() - last_eat > philo->data->time_to_die)
		{
			print_message(philo, 5);
			sem_close(philo->done);
			sem_unlink("/done");
			ft_exit(1, philo->data);
		}
	}
	return (NULL);
}

void	routine_one_philo(t_philo *philo)
{
	long long	time;

	print_message(philo, 0);
	ft_usleep(philo->data->time_to_die);
	time = gtime() - philo->data->start_time;
	printf("%s%lld Philosopher %d died %s\n", "\e[0;31m",
		time, philo->id, "\e[0m");
	ft_exit(0, philo->data);
}

void	start_simulation(t_philo *philo)
{
	pthread_t	checker;

	sem_unlink("/done");
	philo->done = sem_open("/done", O_CREAT, 0644, 1);
	if (philo->done == SEM_FAILED || philo->count == SEM_FAILED)
		ft_exit(1, philo->data);
	if (philo->data->nb_philo == 1)
		routine_one_philo(philo);
	if (philo->id % 2 == 0)
		usleep(100);
	gettimeofday(&philo->data->last_eat, NULL);
	pthread_create(&checker, NULL, &checker_routine, philo);
	pthread_detach(checker);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		if (philo->data->nb_must_eat == philo->eat_count)
			ft_exit(0, philo->data);
		sleep_action(philo);
		thinking(philo);
	}
}
