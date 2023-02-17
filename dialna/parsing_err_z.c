#include "../minishell.h"

void    pars_err1(int id)
{
    if (id == 1)
    {
      write(2, "syntax error near unexpected token `|'\n", 40);
	    exit(23);
    }
    if (id == 2)
    {
		  perror("syntax error");
		  exit(1);
  	}
    if (id == 3)
    {
	  	perror("missing file for redirection");
	  	exit(1);
	  }
    if (id == 4)
    {
      perror("Too many args");
		  exit(1);
    }
}

void    parsing_err(int id)
{
    if (id == 1 || id == 2 || id == 3)
        pars_err1(id);
}