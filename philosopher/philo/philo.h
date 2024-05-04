/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:54:35 by boel-bou          #+#    #+#             */
/*   Updated: 2024/04/23 15:06:42 by boel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_eat;
	int				count_eat;
	int				full;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	mutex_last_eat;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_must_eat;
	int				count_full;
	int				death;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_full;
	pthread_mutex_t	is_dead;
	pthread_mutex_t	check;
}	t_data;

int			check_argument(int ac, char **av);
void		thread_function(t_data *data);
long long	get_current_time(void);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_forks(t_philo *philo);
void		sleep_action(t_philo *philo);
void		thinking(t_philo *philo);
void		destroy_mutex(t_data *data);
void		print_message(t_philo *philo, int i);
int			verify_death(t_philo *philo);
int			ft_usleep(size_t milliseconds);
void		stop_philosophres(t_data *data);
void		ft_putstr_fd(char *s, int fd);
long		ft_atoi(char *str);

#endif
