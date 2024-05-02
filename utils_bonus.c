/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:47 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/26 14:44:01 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0 || !s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_message(t_philo *philo, int i)
{
	long long	time;

	sem_wait(philo->data->sem_print);
	time = get_current_time() - philo->data->start_time;
	if (i == 0)
		printf("%s%lld Philosophre %d has taken right fork %s\n",
			"\x1B[36m", time, philo->id, "\e[0m");
	else if (i == 1)
		printf("%s%lld Philosophre %d has taken left fork %s\n",
			"\x1B[36m", time, philo->id, "\e[0m");
	else if (i == 2)
		printf("%s%lld Philosopher %d is eating %s\n", "\e[32m",
			time, philo->id, "\e[0m");
	else if (i == 3)
		printf("%s%lld Philosopher %d is sleeping %s\n", "\e[1;33m",
			time, philo->id, "\e[0m");
	else if (i == 4)
		printf("%s%lld Philosopher %d is thinking %s\n", "\e[0;35m",
			time, philo->id, "\e[0m");
	else if (i == 5)
	{
		printf("%s%lld Philosopher %d died %s\n", "\e[0;31m",
			time, philo->id, "\e[0m");
		return ;
	}
	sem_post(philo->data->sem_print);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] <= 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (!(is_digit(str[i])))
			return (0);
		i++;
	}
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

