/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:07:27 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/23 15:21:11 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	manipulate_action(t_philo *philos)
{
	int		dead;

	pthread_mutex_lock(&philos->data->is_dead);
	dead = philos->data->death;
	pthread_mutex_unlock(&philos->data->is_dead);
	while (dead == 0)
	{
		if (!verify_death(philos))
			break ;
		take_forks(philos);
		eat(philos);
		put_forks(philos);
		if (philos->count_eat == philos->data->nb_must_eat)
		{
			philos->full = 1;
			pthread_mutex_lock(&philos->data->mutex_full);
			philos->data->count_full++;
			pthread_mutex_unlock(&philos->data->mutex_full);
			break ;
		}
		sleep_action(philos);
		thinking(philos);
	}
}

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	pthread_mutex_lock(&philos->mutex_last_eat);
	philos->last_eat = get_current_time();
	pthread_mutex_unlock(&philos->mutex_last_eat);
	if (philos->data->nb_philo == 1)
	{
		print_message(philos, 0);
		usleep(philos->data->time_to_die * 1000);
		return (NULL);
	}
	if (philos->id % 2 == 0)
	{
		usleep(100);
		thinking(philos);
	}
	manipulate_action(philos);
	return (NULL);
}

int	protocol_dying(t_data *data, int i)
{
	pthread_mutex_lock(&data->philo[i].mutex_last_eat);
	if ((get_current_time() - data->philo[i].last_eat)
		> (long long)data->time_to_die)
	{
		pthread_mutex_unlock(&data->philo[i].mutex_last_eat);
		pthread_mutex_lock(&data->is_dead);
		data->death = 1;
		pthread_mutex_unlock(&data->is_dead);
		pthread_mutex_lock(&data->print);
		printf("%s%lld Philosopher %d died%s\n", "\e[31m",
			get_current_time() - data->start_time,
			data->philo[i].id, "\e[0m");
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	else
		return (0);
}

void	*controle(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_full);
		if (data->count_full == data->nb_philo)
		{
			pthread_mutex_unlock(&data->mutex_full);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_full);
		if (i == data->nb_philo)
			i = 0;
		usleep(100);
		if (!protocol_dying(data, i))
			pthread_mutex_unlock(&data->philo[i].mutex_last_eat);
		else
			break ;
		i++;
	}
	return (NULL);
}

void	thread_function(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]);
		i++;
	}
	controle(data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	destroy_mutex(data);
}
