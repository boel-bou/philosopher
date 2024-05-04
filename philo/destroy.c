/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:54:11 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/22 22:04:37 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].mutex_last_eat);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->mutex_full);
	pthread_mutex_destroy(&data->is_dead);
	free(data->forks);
	free(data->philo);
}

void	print_message(t_philo *philo, int i)
{
	long long	time;

	if (verify_death(philo) == 0)
		return ;
	if (pthread_mutex_lock(&philo->data->print) != 0)
		printf("%d: error\n", __LINE__);
	time = get_current_time() - philo->data->start_time;
	if (i == 0 && verify_death(philo))
		printf("%s%lld Philosophre %d has taken right fork %s\n",
			"\x1B[36m", time, philo->id, "\e[0m");
	else if (i == 1 && verify_death(philo))
		printf("%s%lld Philosophre %d has taken left fork %s\n",
			"\x1B[36m", time, philo->id, "\e[0m");
	else if (i == 2 && verify_death(philo))
		printf("%s%lld Philosopher %d is eating %s\n", "\e[32m",
			time, philo->id, "\e[0m");
	else if (i == 3 && verify_death(philo))
		printf("%s%lld Philosopher %d is sleeping %s\n", "\e[1;33m",
			time, philo->id, "\e[0m");
	else if (i == 4 && verify_death(philo))
		printf("%s%lld Philosopher %d is thinking %s\n", "\e[0;35m",
			time, philo->id, "\e[0m");
	if (pthread_mutex_unlock(&philo->data->print) != 0)
		printf("%d: error\n", __LINE__);
}
