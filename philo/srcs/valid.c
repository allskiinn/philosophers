/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliberal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:30:55 by aliberal          #+#    #+#             */
/*   Updated: 2025/12/16 20:21:55 by aliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	valid_args(int n_args, char **args)
{
	int c;

	if (n_args != 5 && n_args != 6)
	{
		printf("\nNumber of invalid arguments\n");
		return (FAILURE);
	}
	c = 0;
	while (args[++c] && (ft_atoi(args[c]) > 0 || args[c][0] == '0'))
		;
	if (ft_atoi(args[1]) <= 0)
	{
		printf("There must be at least one philosopher.");
		return (FAILURE);
	}
	return (SUCCESS);
}

static	int	valid_died(t_p *philo)
{
	show_action(philo, DIE);
	philo->data->finish = 1;
	philo->die = 1;
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (1);
}

static	int	valid_death(t_p *p)
{
	long int	now;

	pthread_mutex_lock(p->data->block);
	now = get_time() - p->last_meal;
	if (now >= p->data->time_die)
	{
		pthread_mutex_unlock(p->data->block);
		return (valid_died(p));
	}
	pthread_mutex_unlock(p->data->block);
	return (0);
}

static	int	valid_meals(t_p p, int last)
{
	if (p.data->valid_meal
		&& last == p.data->philos - 1
		&& p.meals == p.data->meals_philo)
		return (ft_usleep(300));
	return (0);
}

void	valid_thread(t_p *p, t_data *d)
{
	int	c;

	while (!d->start)
		continue ;
	while (!d->finish)
	{
		c = -1;
		while (++c < d->philos)
			if (valid_death(&p[c]) || valid_meals(p[c], c))
				d->finish = 1;
	}
	if (d->valid_meal
		&& p[d->philos - 1].meals == d->meals_philo)
	{
		ft_usleep(5 * d->philos);
		printf("\n\n-----------------------\n\n");
		printf("-> Everyone ate %d time\n", d->meals_philo);
		printf("\n\n-----------------------");
	}
}
