/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:54:48 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/22 22:09:46 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(data->nb_philo * sizeof(t_philo));
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].right_fork = i;
		data->philo[i].left_fork = (i + 1) % data->nb_philo;
		data->philo[i].count_eat = 0;
		data->philo[i].thread = 0;
		data->philo[i].last_eat = 0;
		data->philo[i].full = 0;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].mutex_last_eat, NULL);
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex_full, NULL);
	pthread_mutex_init(&data->is_dead, NULL);
	pthread_mutex_init(&data->check, NULL);
}

void	init_argument(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		data->nb_must_eat = -1;
	else
		data->nb_must_eat = ft_atoi(av[5]);
	data->death = 0;
	data->count_full = 0;
	init_mutex(data);
	init_philos(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_argument(ac, av))
		return (1);
	init_argument(ac, av, &data);
	thread_function(&data);
}
