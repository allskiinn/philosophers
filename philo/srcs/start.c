/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliberal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:49:55 by aliberal          #+#    #+#             */
/*   Updated: 2025/12/16 20:23:28 by aliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_data(int argc, char **argv, t_data *data)
{
	data->philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->meals_philo = -1;
	data->start = 0;
	data->start_time = 0;
	data->valid_meal = 0;
	if (argc == 6)
	{
		data->valid_meal = 1;
		data->meals_philo = ft_atoi(argv[5]);
	}
	data->finish = 0;
}



void	start_lock_and_forks(t_data *d)
{
	int	i;

	i = -1;
	d->block = malloc(sizeof(pthread_mutex_t));
	if (!d->block)
		failed("Error in mutex block", d, NULL, 1);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->philos);
	if (!d->forks)
		failed("Error in mutex forks", d, NULL, 1);
	if (pthread_mutex_init(d->block, NULL) == -1)
		failed("Error in mutex block", d, NULL, 1);
	while (++i < d->philos)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) == -1)
			failed("Error in mutex forks", d, NULL, 1);
	}
}

static	void	start_info_philo(t_p *p, t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philos)
	{
		p[i].idx = (i + 1);
		p[i].meals = 0;
		p[i].last_meal = 0;
		p[i].start_thread = 0;
		p[i].die = 0;
		p[i].data = d;
		p[i].fork_left = &d->forks[i];
		p[i].fork_right = 0;
	}
}

static	void	start_threads_philo(t_p *p, t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philos)
	{
		p[i].fork_right = p[(i + 1) % d->philos].fork_left;
		if (pthread_create(&p[i].thread, NULL, &actions, &p[i]) == -1)
			failed("Error creating the thread", d, p, 1);
	}
	d->start_time = get_time();
	i = -1;
	while (++i < d->philos)
	{
		p[i].start_thread = d->start_time;
		p[i].last_meal = d->start_time;
	}
	d->start = 1;
}

int	start_philo(t_data *d)
{
	t_p	*p;

	p = malloc(sizeof(t_p) * d->philos);
	if (!p)
	{
		failed("Error in struct philo", d, p, 1);
		return (1);
	}
	start_info_philo(p, d);
	start_threads_philo(p, d);
	valid_thread(p, d);
	finish_thread(p, d);
	return (0);
}
