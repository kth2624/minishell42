#include "minishell.h"

int *handle_pipe(int fd)
{
	if (pipe == )
}
/*
int size = ft_lstsize(cmd_line);
int fd[size][2];
int idx = -1;

while (++idx < size)
{
	// 자식과 부모가 파이프를 공유할 수 있도록? fork 하기전에 pipe
	// 명령어들 사이에는 각기 다른 파이프가 있음
	pipe(fd[idx]);

	if (next_flag == 리다이렉션)
	{

	}
	else if (pre_flag == 파이프 || next_flag == 파이프)
	{
		fork();
		if (pid == 0)
		{
			if (pre_flag == 파이프)
				dup2(fd[idx - 1][0], 0);	// 이전이 파이프 플래그면 fd[idx - 1][0]로부터 입력을 읽어옴
			if (next_flag == 파이프)
				dup2(fd[idx][1], 1);		// 다음이 파이프 플래그면 명령 수행결과를 fd[idx][1]에 출력
			interpret();
		}
		else
		{
			// 자식에서 연 파이프 부모에서 닫아주기
			close(fd[idx - 1][0]);
			close(fd[idx][1]);
			wait(&status);
		}
	}
	else if (pre_flag == none)
	{
		fork();
		if (pid == 0)
			interpret();
		else
			wait(&status);
	}
}
*/