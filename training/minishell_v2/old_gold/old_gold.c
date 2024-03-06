// this function ask user to enter prompt
// and if prompt not NULL it add it to history

//char	*ft_get_prompt()
//{
//	char	*prompt;

//	prompt = readline("🍪🍪🍪\033[0;32m>$ \033[0m");
//	if (prompt && prompt[0])
//		add_history(prompt);
//	return (prompt);
//}




//int	main(int ac, char **av, char **ev)
//{
//	char	*prompt;
//	//t_env	*env;

//	(void)(ac);
//	(void)(av);
//	(void)(ev);
//	//env = ft_env_create(ev);
//	while (1)
//	{
//		prompt = ft_get_prompt();
//		if (prompt == NULL)
//		{
//			printf("exit\n");
//			exit(0);
//		}
//		//ft_parse(prompt);
//		//ft_execute(prompt, &env);
//	}
//	return (0);
//}

//void	ft_execute(t_node *root, t_env **env, int fd[2])
//{
//	int	pid;

//	if (!root)
//		return ;
//	if (root->type == PIPE)
//	{
//		if (pipe(fd) == -1)
//		{
//			perror("Pipe Error");
//			return ;
//		}
//		pid = fork();
//		if (pid < 0) {
//			perror("fork Error");
//			return ;
//		} else if (pid == 0) {
//			close(fd[0]);
//			dup2(fd[1], 1);
//			close(fd[1]);
//			ft_cmd_execute(root->left->data, env);
//			exit(FAILED);
//		} else {
//			wait(NULL);
//			close(fd[1]);
//			dup2(fd[0], 0);
//			close(fd[0]);
//			ft_cmd_execute(root->right->data, env);
//			exit(FAILED);
//		}
//	}
//}


//void	ft_cmd_execute(char *cmd, t_env **env)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	else
//	{
//		wait(NULL);
//		exit(SUCCESS);
//	}
//}


//void	ft_cmd_execute(char *cmd, t_env **env, t_node **root)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	pipe((*root)->fd);
//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		close((*root)->fd[0]);
//		dup2((*root)->fd[1], STDOUT_FILENO);
//		close((*root)->fd[1]);
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	wait(NULL);
//}

//void	ft_cmd_execute1(char *cmd, t_env **env, t_node **root, t_node *save)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	pipe((*root)->fd);
//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		close(save->fd[1]);
//		dup2(save->fd[0], STDIN_FILENO);
//		close(save->fd[0]);
//		close((*root)->fd[0]);
//		dup2((*root)->fd[1], STDOUT_FILENO);
//		close((*root)->fd[1]);
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	close(save->fd[0]);
//	close(save->fd[1]);
//	wait(NULL);
//}

//void	ft_cmd_execute2(char *cmd, t_env **env, t_node *save)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		close(save->fd[1]);
//		dup2(save->fd[0], STDIN_FILENO);
//		close(save->fd[0]);
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	close(save->fd[0]);
//	close(save->fd[1]);
//	wait(NULL);
//}

//void	ft_execute_pipe(t_node *root, t_env **env, t_node *save)
//{
//	if (root && root->type == PIPE)
//	{
//		ft_cmd_execute1(root->left->data, env, &root->left, save);
//		save = root->left;
//		if (root->right->type == PIPE)
//			ft_execute_pipe(root->right, env, save);
//		else
//		{
//			ft_cmd_execute2(root->right->data, env, save);
//		}
//	}
//	else
//	{
//		ft_cmd_execute2(root->data, env, save);
//	}
//}

//void	ft_execute_redirection_output(t_node *root, t_env **env, int *exit_status, int outfd)
//{
//	int	fd;
//	pid_t	pid;
//	if (!root)
//		return ;
	
//	if (root->type == REDIRECT_OUTPUT || root->type == REDIRECT_OUTPUT_APPEND)
//	{
//		fd = ft_open_file(root->right->data, root->type);
//		if (fd == -1)
//		{
//			perror("open Error");
//			exit(FAILED);
//		}
//		close(fd);
//		ft_execute_redirection_output(root->left, env, exit_status, outfd);
//	}
//	else
//	{
//		pid = fork();
//		if (pid == 0)
//		{
//			dup2(outfd, 1);
//			ft_cmd_execute(root->data, env, exit_status);
//			exit(SUCCESS);
//		}
//		wait(exit_status);
//		close(outfd);
//	}
//}

//void	ft_execute_and()



//void	ft_execute(t_node *root, t_env **env, int *exit_status)
//{
//	//pid_t	pid;
//	static int	i;
//	int			fd;

//	if (!root)
//		return ;
//	else if (root->type == REDIRECT_OUTPUT || root->type == REDIRECT_OUTPUT_APPEND)
//	{
//		if (fork() == 0)
//		{
//			fd = ft_open_file(root->right->data, root->type);
//			if (i == 0)
//			{
//				dup2(fd, STDOUT_FILENO);
//				i++;
//			}
//			close(fd);
//			if (root->left)
//				ft_execute(root->left, env, exit_status);
//			exit(*exit_status);
//		}
//		else 
//			wait(exit_status);
//	}
//	else if (root->type == AND)
//	{
//		ft_execute(root->left, env, exit_status);
//		if ((*exit_status) == 0)
//			ft_execute(root->right, env, exit_status);
//	}
//	else if (root->type == OR)
//	{
//		ft_execute(root->left, env, exit_status);
//		if ((*exit_status) != 0)
//			ft_execute(root->right, env, exit_status);
//	}
//	else
//		ft_cmd_execute(root->data, env, exit_status);
//	//if (root->type == PIPE)
//	//{
//	//	t_node *save;
//	//	ft_cmd_execute(root->left->data, env, &root->left);
//	//	save = root->left;
//	//	ft_execute_pipe(root->right, env, save);
//	//}
	
//}

//void	ft_execute_redirection_output(t_node *root, t_env **env, int *exit_status, int outfd)
//{
//	int	fd;
//	pid_t	pid;
//	if (!root)
//		return ;
	
//	if (root->type == REDIRECT_OUTPUT || root->type == REDIRECT_OUTPUT_APPEND)
//	{
//		fd = ft_open_file(root->right->data, root->type);
//		if (fd == -1)
//		{
//			perror("open Error");
//			exit(FAILED);
//		}
//		close(fd);
//		ft_execute_redirection_output(root->left, env, exit_status, outfd);
//	}
//	else
//	{
//		pid = fork();
//		if (pid == 0)
//		{
//			dup2(outfd, 1);
//			ft_cmd_execute(root->data, env, exit_status);
//			exit(SUCCESS);
//		}
//		wait(exit_status);
//		close(outfd);
//	}
//}

//void	ft_cmd_execute(char *cmd, t_env **env, int *exit_status)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	else
//	{
//		wait(exit_status);
//	}
//}

//void	ft_execute_pipe(t_node *root, t_env **env, int *exit_status, int prevfd[2])
//{
//	int			curfd[2];

//	if (!root)
//		return ;
//	else if (root->type == PIPE)
//	{
//		pipe(curfd);
//		if (fork() == 0)
//		{
//			close(prevfd[1]);
//			dup2(prevfd[0], 0);
//			close(prevfd[0]);
//			close(curfd[0]);
//			dup2(curfd[1], 1);
//			close(curfd[1]);
//			ft_cmd_execute(root->left->data, env);
//			exit(FAILED);
//		}
//		else
//		{
//			if (root->right->type == PIPE)
//				ft_execute_pipe(root->right, env, exit_status, curfd);
//			else
//			{
//				if (fork() == 0)
//				{
//					close(prevfd[1]);
//					close(prevfd[0]);
//					close(curfd[1]);
//					dup2(curfd[0], 0);
//					close(curfd[0]);
//					ft_cmd_execute(root->left->data, env);
//					exit(FAILED);
//				}
//				else
//					wait(exit_status);
//			}
//			close(prevfd[1]);
//			close(prevfd[0]);
//			wait(exit_status);
//		}
//	}
//}

//void	ft_save_fds(t_list **fds, int *fd)
//{
//	ft_lstadd_back(fds, ft_lstnew(fd));
//}

//void	ft_close_all_pipes(t_list **fds)
//{
//	t_list	*fd;

//	fd = *fds;
//	while (fd)
//	{
//		close(((int *)fd->content)[0]);
//		close(((int *)fd->content)[1]);
//		fd = fd->next;
//	}
//}

//void	ft_execute_pipe(t_node *root, t_env **env, int *exit_status)
//{
//	t_list	*fdshead;
//	int	fd[2];

//	ft_save_fds(&fdshead, (int *)fd);
//	if (fork() == 0)
//	{
//		dup2(fd[1], 1);
//		close(fd[0]);
//		ft_execute(root->left, env, exit_status);
//		ft_close_all_pipes(&fdshead);
//		exit(*exit_status);
//	}
//	else
//	{
//		if (fork() == 0)
//		{
//			dup2(fd[0], 0);
//			close(fd[1]);
//			ft_execute(root->right, env, exit_status);
//			ft_close_all_pipes(&fdshead);
//			exit(*exit_status);
//		}
//		else
//			while (wait(exit_status) != -1);
//	}
//}

// "$;!?*%#"
//int	ft_is_char_in_str(char c, char *set)
//{
//	int	i;

//	i = 0;
//	while (set[i])
//	{
//		if (set[i] == c)
//			return (1);
//		i++;
//	}
//	return (0);
//}

//char	*ft_char_to_str(char c)
//{
//	char	str[2];

//	str[0] = c;
//	str[1] = 0;
//	return (ft_strdup(str));
//}

//void	ft_print_lst(t_list *node)
//{
//	while (node)
//	{
//		printf("{%s}\n", node->content);
//		node = node->next;
//	}
//}

//char	**ft_expand(char *prompt)
//{
//	t_list	*expanded_prompt;	// store expanded prompt
//	int		open;	//store " or ' or space 
//	int		i;	// index in prompt
//	char	*cur;	// store small part part of prompt
//	char	env_var;	// store if found $ to look in env after

//	if (!prompt)
//		return (0);
//	open = 0;
//	i = -1;
//	cur = NULL;
//	expanded_prompt = NULL;
//	while (prompt[++i])
//	{
//		if (prompt[i] == ' ' && open == 0)
//		{
//			if (cur)
//			{
//				ft_lstadd_back(&expanded_prompt, ft_lstnew(cur));
//				cur = NULL; // I must call free
//			}
//		}
//		else if (prompt[i] == '"' || prompt[i] == '\'')
//		{
//			if (open == 0)
//				open = prompt[i];
//			else if (open == prompt[i])
//				open = 0;
//			else
//				cur = ft_strjoin(cur, ft_char_to_str(prompt[i]));
//		}
//		else
//			cur = ft_strjoin(cur, ft_char_to_str(prompt[i]));
//	}
//	if (cur)
//		ft_lstadd_back(&expanded_prompt, ft_lstnew(cur));
//	ft_print_lst(expanded_prompt);
//	return (NULL);
//}


//void	ft_execute_pipe(t_node *root, t_env **env, int *exit_status, int prevfd[2])
//{
//	int			curfd[2];

//	if (!root)
//		return ;
//	else if (root->type == PIPE)
//	{
//		pipe(curfd);
//		if (fork() == 0)
//		{
//			close(prevfd[1]);
//			dup2(prevfd[0], 0);
//			close(prevfd[0]);
//			close(curfd[0]);
//			dup2(curfd[1], 1);
//			close(curfd[1]);
//			ft_cmd_execute(root->left->data, env);
//			exit(FAILED);
//		}
//		else
//		{
//			if (root->right->type == PIPE)
//				ft_execute_pipe(root->right, env, exit_status, curfd);
//			else
//			{
//				if (fork() == 0)
//				{
//					close(prevfd[1]);
//					close(prevfd[0]);
//					close(curfd[1]);
//					dup2(curfd[0], 0);
//					close(curfd[0]);
//					ft_cmd_execute(root->left->data, env);
//					exit(FAILED);
//				}
//				else
//					wait(exit_status);
//			}
//			close(prevfd[1]);
//			close(prevfd[0]);
//			wait(exit_status);
//		}
//	}
//}


//void	ft_execute(t_node *root, t_env **env, int *exit_status)
//{
//	//pid_t	pid;
//	//static int	i;
//	////static int	j;
//	//int			fd;
//	int			curfd[2];

//	if (!root)
//		return ;
//	else if (root->type == PIPE)
//	{
//		pipe(curfd);
//		if (fork() == 0)
//		{
//			close(curfd[0]);
//			dup2(curfd[1], 1);
//			close(curfd[1]);
//			ft_cmd_execute(root->left->data, env);
//			exit(FAILED);
//		}
//		else
//		{
//			ft_execute_pipe(root->right, env, exit_status, curfd);
//			wait(exit_status);
//		}
//	}
//	//else if (root->type == REDIRECT_OUTPUT || root->type == REDIRECT_OUTPUT_APPEND)
//	//{
//	//	if (fork() == 0)
//	//	{
//	//		fd = ft_open_file(root->right->data, root->type);
//	//		if (i == 0)
//	//		{
//	//			dup2(fd, STDOUT_FILENO);
//	//			i++;
//	//		}
//	//		close(fd);
//	//		if (root->left)
//	//			ft_execute(root->left, env, exit_status);
//	//		exit(*exit_status);
//	//	}
//	//	else 
//	//		wait(exit_status);
//	//}
//	//else if (root->type == AND)
//	//{
//	//	ft_execute(root->left, env, exit_status);
//	//	if ((*exit_status) == 0)
//	//		ft_execute(root->right, env, exit_status);
//	//}
//	//else if (root->type == OR)
//	//{
//	//	ft_execute(root->left, env, exit_status);
//	//	if ((*exit_status) != 0)
//	//		ft_execute(root->right, env, exit_status);
//	//}
//	//else
//	//	ft_cmd_execute(root->data, env, exit_status);
//}