/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:25:42 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/15 11:33:30 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <signal.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/errno.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_args
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
}					t_args;

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef enum e_state
{
	THINK,
	EAT,
	FORK,
	SLEEP,
	DIED,
	STOP
}					t_state;

struct				s_table;
typedef struct s_philo
{
	int				index;
	int				fork_take;
	int				time_limit[6];
	int				many_eat;
	t_bool			*alive;
	struct timeval	begin_eat;
	t_state			status;
	sem_t			*fork;
	sem_t			*lock_output;
	pthread_t		threads;
	t_args			*args;
	struct s_table	*table;
	pid_t			fork_philo;
}					t_philo;

typedef struct s_table
{
	t_args			args;
	t_bool			alive;
	sem_t			*fork;
	sem_t			*lock_output;
	t_philo			*philo;
	int				sema_init;
}					t_table;

typedef void		(*t_actions)(t_philo *philo);

////////////////////////////////
//   ____            _        //
//  | __ )  __ _ ___(_) ___   //
//  |  _ \ / _` / __| |/ __|  //
//  | |_) | (_| \__ \ | (__   //
//  |____/ \__,_|___/_|\___|  //
//                            //
////////////////////////////////

int		ft_args(int ac, char **av);
int		ft_atoi(char *str);
int		ft_cinset(char c, char *set);
int		ft_isdigit(int c);
int		ft_isnumber(char *str);
int		ft_isspace(char c);

//////////////////////////////
//   __  __       _         //
//  |  \/  | __ _(_)_ __    //
//  | |\/| |/ _` | | '_ \   //
//  | |  | | (_| | | | | |  //
//  |_|  |_|\__,_|_|_| |_|  //
//                          //
//////////////////////////////

void	go_phiphi(t_philo *philo);
void	table_init(int ac, char **av, t_table *table);
void	philo_do_something(t_philo *philo, void (*ph_action)(t_philo *));

////////////////////////////////////////////////
//   ____  _     _ _                    _     //
//  |  _ \| |__ (_) | ___     __ _  ___| |_   //
//  | |_) | '_ \| | |/ _ \   / _` |/ __| __|  //
//  |  __/| | | | | | (_) | | (_| | (__| |_   //
//  |_|   |_| |_|_|_|\___/   \__,_|\___|\__|  //
//                                            //
////////////////////////////////////////////////

void	scream_what_u_do(t_philo *philo, char *str);
void	ph_think(t_philo *philo);
void	ph_eat(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	*wait_irt(void *philo);

//////////////////////////////////////////////////////////////////////
//   ____  _     _ _                    _      __            _      //
//  |  _ \| |__ (_) | ___     __ _  ___| |_   / _| ___  _ __| | __  //
//  | |_) | '_ \| | |/ _ \   / _` |/ __| __| | |_ / _ \| '__| |/ /  //
//  |  __/| | | | | | (_) | | (_| | (__| |_  |  _| (_) | |  |   <   //
//  |_|   |_| |_|_|_|\___/   \__,_|\___|\__| |_|  \___/|_|  |_|\_\  //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void	take_fork(t_philo *philo);
void	ph_take_fork(t_philo *philo);

/////////////////////////////////////////////////////
//   _____ _                _                _     //
//  |  ___| |_    __ _  ___| |_    __ _  ___| |_   //
//  | |_  | __|  / _` |/ _ \ __|  / _` |/ _ \ __|  //
//  |  _| | |_  | (_| |  __/ |_  | (_| |  __/ |_   //
//  |_|    \__|  \__, |\___|\__|  \__, |\___|\__|  //
//               |___/            |___/            //
//                                                 //
/////////////////////////////////////////////////////

void	ft_init_time_philo(t_philo *philo, t_args *args);
void	ft_philo_init(int i, t_args *args, t_philo *philo, t_table *table);
void	ft_get_arg(int ac, char **av, t_table *table);
void	ft_get_philo(t_table *table);

//////////////////////////////////////////////////////
//   ____  _     _ _         _   _                  //
//  |  _ \| |__ (_) | ___   | |_(_)_ __ ___   ___   //
//  | |_) | '_ \| | |/ _ \  | __| | '_ ` _ \ / _ \  //
//  |  __/| | | | | | (_) | | |_| | | | | | |  __/  //
//  |_|   |_| |_|_|_|\___/   \__|_|_| |_| |_|\___|  //
//                                                  //
//////////////////////////////////////////////////////

void	philo_tempo(int time_limit);
long	get_actual_time(void);
long	get_timestamp(t_philo *philo);
long	transform_timeval_ms(struct timeval *time);

////////////////////////////////////////////////////////////////////
//    _____ _        _           _                        _       //
//   / ____| |      | |         | |                      | |      //
//  | |    | |_ _ __| |  _ __   | | __ _ _   _ _ __   ___| |__    //
//  | |    | __| '__| | | '_ \  | |/ _` | | | | '_ \ / __| '_ \   //
//  | |____| |_| |  | | | | | | | | (_| | |_| | | | | (__| | | |  //
//   \_____|\__|_|  |_| |_| |_| |_|\__,_|\__,_|_| |_|\___|_| |_|  //
//                                                                //
////////////////////////////////////////////////////////////////////

void	control_the_mind(t_table *table);
void	*create_phi_thread(void *philo);
void	launch_engine(t_table *table);

////////////////////////////////////////
//   ______                     _ _   //
//  |  ____|                   | | |  //
//  | |__ _ __ ___  ___    __ _| | |  //
//  |  __| '__/ _ \/ _ \  / _` | | |  //
//  | |  | | |  __/  __/ | (_| | | |  //
//  |_|  |_|  \___|\___|  \__,_|_|_|  //
//                                    //
////////////////////////////////////////

void	its_the_end(t_table *table);
void	clean_semaphore(t_philo *philo);
void	clean_table(t_table	*table);
void	philo_pass_away(t_philo *philo, t_state status);

#endif