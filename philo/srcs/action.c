/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliberal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:32:55 by aliberal          #+#    #+#             */
/*   Updated: 2025/12/16 20:19:31 by aliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	void	eating(t_p *p)
{
	pthread_mutex_lock(p->fork_left);
	show_action(p, CATCH_LEFT);
	pthread_mutex_lock(p->fork_right);
	show_action(p, CATCH_RIGHT);
	ft_usleep(p->data->time_eat);
	show_action(p, EAT);
	pthread_mutex_unlock(p->fork_left);
	show_action(p, DROP_LEFT);
	pthread_mutex_unlock(p->fork_right);
	show_action(p, DROP_RIGHT);
	p->last_meal = get_time();
	p->meals++;
}

static	void	sleeping_and_thinking(t_p *p)
{
	ft_usleep(p->data->time_sleep);
	show_action(p, SLEEP);
	show_action(p, THINK);
}

void	*actions(void *arg)
{
	t_p	*p;

	p = (t_p *)arg;
	while (!p->data->start)
		continue ;
	if (!(p->idx & 1))
		ft_usleep(p->data->time_eat * 0.9 + 1);
	while (!p->data->finish)
	{
		eating(p);
		sleeping_and_thinking(p);
	}
	return (NULL);
}

void	show_action(t_p *p, char *info)
{
	pthread_mutex_lock(p->data->block);
	if (p->data->finish)
	{
		pthread_mutex_unlock(p->data->block);
		return ;
	}
	printf("%ldms", get_time() - p->start_thread);
	printf(" %d", p->idx);
	printf(" %c", '-');
	printf(" ( %s )\n", info);
	pthread_mutex_unlock(p->data->block);
}
