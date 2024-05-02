/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:59:40 by boel-bou          #+#    #+#             */
/*   Updated: 2024/05/02 03:32:30 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_data(t_data *data, int ac, char **av)
{
	if (check_argument(ac, av))
		return (1);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	gettimeofday(&data->last_eat, NULL);
	data->nb_must_eat = -1;
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	data->start_time = 0;
	sem_unlink("/forks");
	sem_unlink("/print");
	data->pids = malloc(sizeof(pid_t) * data->nb_philo);
	data->sem_forks = sem_open("/forks", O_CREAT, 0644, data->nb_philo);
	data->sem_print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->nb_philo < 1 ||  data->nb_philo > 200 || data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || (ac == 6 && data->nb_must_eat < 1) || !data->pids)
		return (1);
	if (data->sem_forks == SEM_FAILED || data->sem_print == SEM_FAILED)
		return (1);
	return (0);
}

void	*checker_routine(void *arg)
{
	t_philo		*philo;
	long long 	last_eat;
 
	philo = (t_philo *)arg;	

	while (1)
	{
		usleep(100);
		sem_wait(philo->done);
		last_eat = philo->data->last_eat.tv_sec * 1000 + philo->data->last_eat.tv_usec / 1000;
		sem_post(philo->done);
		if (get_current_time() - last_eat > philo->data->time_to_die)
		{
			print_message(philo, 5);
			sem_close(philo->done);
			sem_unlink("/done");
			exit (1);
		}
	}
	return (NULL);
}

void	routine_one_philo(t_philo *philo)
{
	long long	time;

	print_message(philo, 0);
	ft_usleep(philo->data->time_to_die);
	time = get_current_time() - philo->data->start_time;
	printf("%s%lld Philosopher %d died %s\n", "\e[0;31m",
		time, philo->id, "\e[0m");
	exit (0);
}

void	start_simulation(t_philo *philo)
{
	pthread_t	checker;

	sem_unlink("/done");
	philo->done = sem_open("/done", O_CREAT, 0644, 1);
	if (philo->done == SEM_FAILED || philo->count == SEM_FAILED)
		exit (1);
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
		if (philo->data->nb_must_eat != -1 && philo->data->nb_must_eat == philo->eat_count)
			exit (0);
		sleep_action(philo);
		thinking(philo);
	}
}

void	fork_function(t_data *data)
{
	int	i;
	pid_t	pid;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->nb_philo)
	{
		pid = fork();
		if (pid < 0)
			exit (1);
		if (pid == 0)
			start_simulation(&data->philos[i]);
		else if (pid != 0)
			data->pids[i] = pid;
		i++;
	}
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		data->pids[i] = 0;
		// data->philos[i].last_eat = -1;
		i++;
	}
	fork_function(data);
	return (0);
}

void	wait_philo(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < data->nb_philo)
			{
			kill(data->pids[i], SIGKILL);
			i++;
			}
			break ;
		}
		i++;
	}
	sem_unlink("/forks");
	sem_unlink("/print");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (1);
	}
	if (init_data(&data, ac, av))
	{
		ft_putstr_fd("Error: invalid arguments\n", 2);
		return (1);
	}
	if (init_philo(&data))
		return (1);
	wait_philo(&data);
	return (0);
}
