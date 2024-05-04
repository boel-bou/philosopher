/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:54:24 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/23 15:15:04 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	long long	start;

	start = get_current_time();
	while ((size_t)(get_current_time() - start) < milliseconds)
		usleep(10);
	return (0);
}

int	verify_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	pthread_mutex_lock(&philo->data->is_dead);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->is_dead);
		pthread_mutex_unlock(&philo->data->check);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->is_dead);
	pthread_mutex_unlock(&philo->data->check);
	return (1);
}

int	check_argument(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd(
			"Usage: ./philo [num_philosophers]"
			"[time_to_die] [time_to_eat]"
			"[time_to_sleep] [numbrer_of_time_to_eat (optional)]\n", 2);
		return (0);
	}
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		return (ft_putstr_fd("Error: Invalid number of philosophers\n", 2), 0);
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (ft_putstr_fd("Error: Invalid time\n", 2), 0);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0)
			return (ft_putstr_fd(
					"Error: Invalid number of time to eat\n", 2), 0);
	}
	return (1);
}
