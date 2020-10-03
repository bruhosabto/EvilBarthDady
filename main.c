#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //conversao -n -N
#include "data.h"

#define clear system("clear");

void Usage(void)
{
	fprintf(stderr,"\t Autor : Bruno Santos\n");
	fprintf(stderr,"\tmodo normal\n");
	fprintf(stderr,"./evil <dia> <mes> <ano_inicial> <ano_final> <palavra> <saida.txt>\n");
	fprintf(stderr,"\tmodo apenas datas\n");
	fprintf(stderr,"./evil d <dia> <mes> <ano inicial> <ano_final> <saida.txt>\n");
	exit(0);
}
int progresso(int contador,int total)
{
	int progresso = (contador*100)/total;
	
	return progresso;
}
int datas_only(int diax, int mesx, int ano_inicial, int ano_final,char file_name[64])
{
	
	FILE *arquivo;
	
	arquivo = fopen(file_name,"a+");
	
	if(arquivo == NULL)
	{
		return 0;
	}else
	{
		init(diax,mesx,ano_inicial);
		diax = dia();
		mesx = mes();
		ano_inicial = ano();
		
		while (ano_inicial <= ano_final)
		{
			if( diax < 10 && mesx < 10 ) 
			{
				fprintf(arquivo,"0%d0%d%d\n",diax,mesx,ano_inicial);
				fprintf(arquivo,"0%d0%d%d\n",mesx,diax,ano_inicial);
				fprintf(arquivo,"0%d%d0%d\n",diax,ano_inicial,mesx);
				fprintf(arquivo,"0%d%d0%d\n",mesx,ano_inicial,diax);
				fprintf(arquivo,"%d0%d0%d\n",ano_inicial,diax,mesx);
				fprintf(arquivo,"%d0%d0%d\n",ano_inicial,mesx,diax);
			}
			
			if( diax < 10 && mesx >= 10 )
			{
				fprintf(arquivo,"0%d%d%d\n",diax,mesx,ano_inicial);
				fprintf(arquivo,"0%d%d%d\n",diax,ano_inicial,mesx);
				fprintf(arquivo,"%d0%d%d\n",mesx,diax,ano_inicial);
				fprintf(arquivo,"%d0%d%d\n",ano_inicial,diax,mesx);
				fprintf(arquivo,"%d%d0%d\n",mesx,ano_inicial,diax);
				fprintf(arquivo,"%d%d0%d\n",ano_inicial,mesx,diax);
				
			}
			
			if( diax >= 10 && mesx < 10 )
			{
				fprintf(arquivo,"0%d%d%d\n",mesx,diax,ano_inicial);
				fprintf(arquivo,"0%d%d%d\n",mesx,ano_inicial,diax);
				fprintf(arquivo,"%d0%d%d\n",diax,mesx,ano_inicial);
				fprintf(arquivo,"%d0%d%d\n",ano_inicial,mesx,diax);
				fprintf(arquivo,"%d%d0%d\n",diax,ano_inicial,mesx);
				fprintf(arquivo,"%d%d0%d\n",ano_inicial,diax,mesx);
				
			}
			
			if( diax >= 10 && mesx >= 10 )
			{
				fprintf(arquivo,"%d%d%d\n",diax,mesx,ano_inicial);
				fprintf(arquivo,"%d%d%d\n",diax,ano_inicial,mesx);
				fprintf(arquivo,"%d%d%d\n",mesx,diax,ano_inicial);
				fprintf(arquivo,"%d%d%d\n",mesx,ano_inicial,diax);
				fprintf(arquivo,"%d%d%d\n",ano_inicial,diax,mesx);
				fprintf(arquivo,"%d%d%d\n",ano_inicial,mesx,diax);
			}
			
			/*extra*/
			
			fprintf(arquivo,"%d%d\n",ano_inicial,ano_inicial);
			
			diax = dia();
			mesx = mes();
			ano_inicial = ano();
			
		}
		fclose(arquivo);
		
		return 1;
	}
	
	
	
	
	
}

int main(int argc,char*argv[])
{
	static int d = 0,m = 0, a = 0,a_f = 0;//variavel a_f recebe o ano final, tipo, a, recebe 2002 e a_f recebe 2020, será gerada uma lista de
	//datas partindo de inicial até ano final
	//variaveis para dia, mes e ano
	FILE *arq;
	char nome[64];
	char nome_aux[64];//recebe a string passada em capital-latter
	static int total = 0;
	static int contador = 0;
	static int aux_ano = 0;
	static int tmp_ano = 0;
	static int length = 0;
	/*
	 0 - progname
	 1 - dia
	 2 - mes
	 3 - ano
	 4 - ano final
	 5 - string
	 6 - saida.txt
	*/
	
	
	//fprintf(stderr,"%d\n",argc);
	if(argc < 7 || argc == *argv[1] == 'h') 
	{
		
		fprintf(stderr,"Faltando argumentos\n");
		Usage();
		
	}else
	{
	
		if(*argv[1] == 'd')
		{
			char file[64];
			int retorno = 0;
			d = atoi(argv[2]); //dia
			m = atoi(argv[3]); //mes
			a = atoi(argv[4]); //ano inicial
			a_f = atoi(argv[5]);
			strcpy(file,argv[6]);
			
			retorno = datas_only(d,m,a,a_f,file);
			 
			if(retorno == 1) //retorno igual a 1, tudo ocorreu bem, caso seja 0, houve algum erro
			{
				clear //limpa a tela
				fprintf(stderr,"concluido!\n");
				exit(0);
						
			}else if(retorno == 0)
			{
				clear
				fprintf(stderr,"Um erro ocorreu!\n");
				exit(0);
			}
		}else{
		
			d = atoi(argv[1]); // dia
			m = atoi(argv[2]); //mes
			a = atoi(argv[3]); // ano inicial
			a_f = atoi(argv[4]);	//ano final
			strcpy(nome,argv[5]);
			strcpy(nome_aux,nome); // string
			length = strlen(nome);
			for(int i =0 ; i < length; i++ ) nome_aux[i] = toupper(nome_aux[i]);
			//strcpy(nome,nome_aux);
			init(d,m,a);
		}
	}
	
	
	//inicializando as variaveis
	
	//limpando a tela
	clear
	total = a_f - a; //total de anos, ano final menos o ano inicial
	arq = fopen(argv[6],"a+");
	if(arq == NULL)
	{
		fprintf(stderr,"Erro ao tentar criar ou abrir o arquivo '%s' \n",argv[5]);
		fclose(arq);
		exit(0);
	}else{
	
		aux_ano = ano();
		tmp_ano = aux_ano;
		//fprintf(stderr,"%s\n",nome);
		//fprintf(stderr,"%s\n",nome_aux);
		while(a <= a_f)
		{
			d = dia();
			a = ano();
			m = mes();
			fprintf(arq,"%s%d%d%d\n",nome,d,m,a);
			fprintf(arq,"%s%d%d%d\n",nome_aux,d,m,a);
			fprintf(arq,"%s%d\n",nome,a);
			fprintf(arq,"%s%d\n",nome_aux,a);
			fprintf(arq,"%s%d\n",nome,d);
			fprintf(arq,"%s%d\n",nome_aux,d);
			fprintf(arq,"%s%d\n",nome,m);
			fprintf(arq,"%s%d\n",nome_aux,m);
			if(d < 10)
			{
				fprintf(arq,"%s0%d\n",nome,d);	
			}else
			{
				fprintf(arq,"%s%d\n",nome,d);
			}

			if(d < 10)
			{
				fprintf(arq,"%s0%d\n",nome,d);
				fprintf(arq,"%s0%d\n",nome_aux,d);
			}
			if(m < 10 )
			{
				fprintf(arq,"%s0%d\n",nome,m);
				fprintf(arq,"%s0%d\n",nome_aux,m);
			}
			if(d < 10 && m < 10)
			{
				fprintf(arq,"%s0%d0%d\n",nome,d,m);
				fprintf(arq,"%s0%d0%d\n",nome,m,d);
			}
			if(d< 10 && m >= 10)
			{
				fprintf(arq,"%s0%d%d\n",nome,d,m);
				fprintf(arq,"%s%d0%d\n",nome,m,d);
			}
			if(d >= 10 && m < 10)
			{
				fprintf(arq,"%s%d0%d\n",nome,d,m);
				fprintf(arq,"%s0%d%d\n",nome,m,d);
			}
			if(d >= 10 && m >= 10)
			{
				fprintf(arq,"%s%d%d\n",nome,d,m);
				fprintf(arq,"%s%d%d\n",nome,m,d);
			}
			
			fprintf(stderr,"\33[7HProgresso %d%%",progresso(contador, total));
		
			if(aux_ano < ano())
			{
				contador++;
				aux_ano = ano();
			}
			
		}//fim while08740w
	
		fprintf(stderr,"\33[8HConcluido");
		fprintf(stderr,"\33[9HAno inicial %d",tmp_ano);
		fprintf(stderr,"\33[10HAno final  %d\n",ano());
		fprintf(stderr,"\33[11HArquivo de saída %s\n",argv[6]);
		fclose(arq);
	}
	
	
	
	
return 0;
}

