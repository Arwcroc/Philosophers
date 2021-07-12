/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:42:51 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/09 14:00:23 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
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

typedef struct s_philo
{
	int				index;
	int				fork_take;
	int				time_limit[6];
	int				many_eat;
	t_bool			*alive;
	struct timeval	begin_eat;
	t_state			status;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*lock_output;
	pthread_t		threads;
	t_args			*args;
}					t_philo;

typedef struct s_table
{
	t_args			args;
	t_bool			alive;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock_output;
	t_philo			*philo;
}					t_table;

typedef void	(*t_actions)(t_philo *philo);

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

void	table_init(int ac, char **av, t_table *table);
void	go_phiphi(t_philo *philo);
void	philo_do_something(t_philo *philo, void (*ph_action)(t_philo *));
void	philo_pass_away(t_philo *philo, t_state status);

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
void	ft_get_fork(t_table *table);
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

void	its_the_end(t_table *table);
void	control_the_mind(t_table *table);
void	*create_phi_thread(void *philo);
void	launch_engine(t_table *table);

#endif