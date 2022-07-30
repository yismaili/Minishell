#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include "includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    char **arg = {"/bin/lsafs", "-la"};
     if( execve(*arg, arg, envp) < 0)
            perror("exec");
}

//hello everyone rgjhdrghdorh