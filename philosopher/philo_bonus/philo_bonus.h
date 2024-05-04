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

int			ft_atoi(char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		print_message(t_philo *philo, int i);
int			init_data(t_data *data, int ac, char **av);
int			init_philo(t_data *data);
void		start_simulation(t_philo *philo);
int			ft_usleep(size_t milliseconds);
long long	gtime(void);
int			check_argument(int ac, char **av);
void		eat(t_philo *philo);
void		take_forks(t_philo *philo);
void		put_forks(t_philo *philo);
void		sleep_action(t_philo *philo);
void		thinking(t_philo *philo);
void		clear_struct(t_data *data);

#endif
