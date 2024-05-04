/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:53:58 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/25 18:18:08 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->right_fork]) != 0)
		printf("%d: error\n", __LINE__);
	print_message(philo, 0);
	if (pthread_mutex_lock(&philo->data->forks[philo->left_fork]) != 0)
		printf("%d: error\n", __LINE__);
	print_message(philo, 1);
}

void	eat(t_philo *philo)
{
	print_message(philo, 2);
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->mutex_last_eat);
	philo->count_eat++;
	ft_usleep(philo->data->time_to_eat);
}

void	put_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->data->forks[philo->left_fork]) != 0)
		printf("%d: error\n", __LINE__);
	if (pthread_mutex_unlock(&philo->data->forks[philo->right_fork]) != 0)
		printf("%d: error\n", __LINE__);
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
