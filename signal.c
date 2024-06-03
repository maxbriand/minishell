#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() 
{
    char test[] = "test1";
    char test2[] = "test";

    printf("if it's 0, there are no dif %d\n", strncmp(test, test2, 5));
    return (0);
}