/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:47:57 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/25 20:12:52 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	print_message(philo, 0);
	sem_wait(philo->data->sem_forks);
	print_message(philo, 1);
}

void	eat(t_philo *philo)
{
	print_message(philo, 2);
	sem_wait(philo->done);
	gettimeofday(&philo->data->last_eat, NULL);
	philo->eat_count++;
	sem_post(philo->done);
	ft_usleep(philo->data->time_to_eat);
}

void	put_forks(t_philo *philo)
{
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
}

void	sleep_action(t_philo *philo)
{
	print_message(philo, 3);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_message(philo, 4);
}
