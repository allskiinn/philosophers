/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliberal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:35:25 by aliberal          #+#    #+#             */
/*   Updated: 2025/12/16 20:33:22 by aliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	void	show_header(void)
{
	printf("\n--------------------------------------");
	printf("\n TIME");
	printf(" IDX");
	printf(" ROTINA");
	printf("\n--------------------------------------");
	printf("\n\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!valid_args(ac, av))
	{
		start_data(ac, av, &data);
		start_lock_and_forks(&data);
		show_header();
		if (start_philo(&data) == 1)
			return (1);
	}
	return (0);
}

void	failed(char *info, t_data *d, t_p *p, int status)
{
	if (status)
	{
		if (d->block)
			free(d->block);
		if (d->block)
			free(d->forks);
		if (p)
			free(p);
	}
	printf("%s\n", info);
	exit(1);
}

void	finish_thread(t_p *p, t_data *d)
{
	int	c;

	c = -1;
	while (++c < d->philos)
		pthread_join(p[c].thread, (void *)&p[c]);
	pthread_mutex_destroy(d->block);
	pthread_mutex_destroy(d->forks);
	free(d->block);
	free(d->forks);
	free(p);
}
