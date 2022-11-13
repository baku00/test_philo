#ifndef PHILOS_H
# define PHILOS_H
# include "../main.h"

typedef struct s_config
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_eat;
	int	total_time;
}	t_config;

typedef struct s_table
{
	int			have_to_stop;
	long int	start_time;
	void		*philo;
}	t_table;

typedef struct s_philo
{
	int				n;
	long int		last_eat;
	long int		current_time;
	int				number_of_eat;
	t_config		config;
	t_table			*table;
	int				thread_id;
	int				fork_number;
	int				state;
	pthread_mutex_t	fork;
	pthread_t		thread;
	void			*next;
	void			*prev;
}   t_philo;

t_philo		*init_philos(int argc, char **argv);
void		*routine();
long int	get_actual_time(void);
void		milliseconde_sleep(long int milliseconde);
long int	seconde_to_milliseconde(long int seconde);
long int	microseconde_to_milliseconde(long int microseconde);
long int	get_time_pass(long int start, long int end);
void		supervisor(t_philo *philos);
long int	get_current_time(long int start_time);
int			have_to_stop(t_philo *philo);
#endif