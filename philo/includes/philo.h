/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliberal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:15:44 by aliberal          #+#    #+#             */
/*   Updated: 2025/12/16 22:02:28 by aliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

# define FAILURE 1
# define SUCCESS 0

# define EAT "eating"
# define SLEEP "sleeping"
# define THINK "thinking"
# define CATCH_LEFT "took the left fork"
# define CATCH_RIGHT "took the right fork"
# define DIE "died"
# define DROP_LEFT "dropped the left fork"
# define DROP_RIGHT "dropped the right fork"

struct s_data
{
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_philo;

	int				start;
	int				finish;
	int				valid_meal;
	long int		start_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	*block;
};

typedef struct s_data	t_data;

struct s_philo
{
	int				idx;

	int				meals;
	long int		last_meal;
	int				die;
	pthread_t		thread;
	long int		start_thread;

	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_data			*data;
};

typedef struct s_philo	t_p;

/* valid */
int			valid_args(int n_args, char **args);
void		valid_thread(t_p *p, t_data *d);

/* begin */
void		start_data(int argc, char **argv, t_data *data);
void		start_lock_and_forks(t_data *d);
int			start_philo(t_data *d);

/* finish threads */
void		finish_thread(t_p *p, t_data *d);
void		failed(char *info, t_data *d, t_p *p, int status);

/* philosophers actions */
void		show_action(t_p *p, char *info);
void		*actions(void *arg);

/* utils */
int			ft_atoi(const char *str);
int			ft_usleep(long int time);
long int	get_time(void);

#endif