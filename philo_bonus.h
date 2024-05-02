/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:52 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/25 20:15:29 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <errno.h>

typedef struct s_philo
{
	int				id;
	long			eat_count;
	// long long		last_eat;
	sem_t			*done;
	sem_t			*count;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	struct timeval	last_eat;
	pid_t			*pids;
	long long		start_time;
	t_philo			*philos;
	sem_t			*sem_forks;
	sem_t			*sem_print;
}	t_data;

int		ft_atoi(char *str);
int		ft_isdigit(int c);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	print_message(t_philo *philo, int i);
void	*philo_routine(void *arg);
int		init_data(t_data *data, int ac, char **av);
int		init_philo(t_data *data);
int		init_mutex(t_data *data);
void	destroy_mutex(t_data *data);
void	destroy_data(t_data *data);
void	*monitor_routine(void *arg);
void	*full_routine(void *arg);
int		ft_usleep(size_t milliseconds);
long long	get_current_time(void);
int		check_argument(int ac, char **av);
void	eat(t_philo *philo);
void	take_forks(t_philo *philo);
void	put_forks(t_philo *philo);
void	sleep_action(t_philo *philo);
void	thinking(t_philo *philo);

#endif
