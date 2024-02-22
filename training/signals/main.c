/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:26:03 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/16 13:15:00 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void hnld(int sig)
{
	printf("work ends.\n");
	exit(0);
}
int main(int ac, char **av)
{
	struct sigaction s;
	s.sa_handler = &hnld;
	s.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &s, NULL);
	int pid;

	scanf("%d", &pid);
	
	while(pid > 0)
	{
		printf("hello %d\n", pid);
		usleep(500000);
		pid--;
	}
}