#include <stdio.h>
#include "data.h"

static int dia_zero;
static int mes_zero;
static int ano_zero;


//inicializa as variaveis
void init(int dia, int mes, int ano)
{
	dia_zero = dia;
	mes_zero = mes;
	ano_zero = ano;

}
//controla o dia
int dia()
{
	
	if(dia_zero == 31)
	{
		//mes_zero++;
		dia_zero = 1;
	}else if(dia_zero < 31)
	{
		dia_zero++;
	}
	return dia_zero;
}

/*


if(dia_zero < 31)
			{
				dia_zero++;
			}else if(dia_zero == 31)
			{
				mes_zero++;
				dia_zero=1;
			}
			if(mes_zero == 12 && dia_zero == 31)
			{
				ano_zero++;
				dia_zero=1;
				mes_zero=1;
			}


*/
//controla o mes
int mes()
{
	static int mes;
	
	if(dia_zero == 31)
	{
		mes_zero++;
		
	}
	
	return mes_zero;
}

//controla o ano
int ano()
{
	if(mes_zero == 12 && dia_zero == 31)
	{
		ano_zero++;
		dia_zero = 1;
		mes_zero=1;
	}
	return ano_zero;
}



