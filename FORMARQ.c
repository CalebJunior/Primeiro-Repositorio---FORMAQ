#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Caleb Rodrigues da Silva Júnior - 20200831 --- Gean Martins - 1900771*/

char nome[30],chave[30],tipo[1],texto_str[1000],ext[4],resultado[1000];


void arquivolin(){
	
	FILE *pont_arq;
  
  	pont_arq = fopen(nome, "r");
  	
    while(fgets(resultado,200,pont_arq)!=NULL){
  		strcat(texto_str,resultado);
	  }
    
    fclose(pont_arq);
    
	return;
}

void exten(int tp){
	
	int cont=0,i=0,cont2=0;
	
	while(nome[cont]!='.'){
		cont++;
	}
	cont++;
	 
	 
	while(i<3){
		ext[i] = nome[cont+i];
		nome[cont+i]=0x00;
		i++;
	}
	ext[i+1]="\0";
	
	if (tp==1){
	
		if(strcmp(ext,"inv")==0){
			strcat(nome,"dnv");
		}
		else{
			strcat(nome,"inv");
	
		}
	}
	else if(tp==2){
		
		if(strcmp(ext,"crp")==0){
			strcat(nome,"drp");
		}
		else{
			strcat(nome,"crp");
	
		}
	}
	else if(tp==3){
		strcat(nome,"unx");
	}
	else if (tp==4){
		strcat(nome,"dos");
	}
	return;
}

void invert(){
	char cv,cn;
	int cont=0,i=0,cont2=0,tp=1,r,tam;	
	
	tam=strlen(texto_str);
	
	for(i=0;i<tam;i++){
		cv = texto_str[i];
		cn = ~cv;
		texto_str[i]=cn;
	}
	exten(tp);
	FILE *pont_arq;
  
  	pont_arq = fopen(nome, "a");
  	
    r = fputs(texto_str, pont_arq);
   
   	
   	if( r == EOF)
   	{
    	printf("Erro ao tentar gravar os dados! \n");
   	}
   	else
    {
        printf("Dados gravados com sucesso. \n");
     }

    
    fclose(pont_arq);
    
    return;
}

void cript(){
	int maxChave=0,maxTX=0,contchave=0,contTX=0,tp=2,r=0;
	
	maxChave=strlen(chave);
	maxTX=strlen(texto_str);
	for(contTX=0;contTX<maxTX;contTX++){
		resultado[contTX]=texto_str[contTX]^chave[contchave];
		
		if(contchave>=maxChave-1){
			contchave=0;
		}
		else{
			contchave++;
		}	
		
	}
	printf("%s",resultado);
	exten(tp);
	
	FILE *pont_arq;
  
  	pont_arq = fopen(nome, "a");
  	
	r = fputs(resultado, pont_arq);
   
   	
   	if( r == EOF)
   	{
    	printf("Erro ao tentar gravar os dados! \n");
   	}
   	else
    {
        printf("Dados gravados com sucesso. \n");
     }

    
    fclose(pont_arq);
	
	
	
	
	
	
	return;
}


void DOSUNIX(){
	int tam,i,r,cont=0,tp=3;
	char c;
	FILE *pont_arq;
  	pont_arq = fopen(nome, "rb");
  	
  	while(fgets(resultado,200,pont_arq)!=NULL){
  		strcat(texto_str,resultado);
	  }
  	
  	fclose(pont_arq);
  	
  	
  	
  	tam = strlen(texto_str);
  	for(i=0;i<tam;i++){
  		if(texto_str[i]==0x0D){
  			for(cont=i;cont<tam;cont++){
  				texto_str[cont]=texto_str[cont+1];
			  }
  			
  		}
		  
	}
	
	
	
	exten(tp);
	
  	pont_arq = fopen(nome, "w+b");
  	
	r = fputs(texto_str, pont_arq);
   
   	
   	if( r == EOF)
   	{
    	printf("Erro ao tentar gravar os dados! \n");
   	}
   	else
    {
        printf("Dados gravados com sucesso. \n");
     }

    
    fclose(pont_arq);
	return;
}

void UNIXDOS(){
	int tam,i,r,cont=0,tp=4;
	char c;
	FILE *pont_arq;
  	pont_arq = fopen(nome, "rb");
  	
  	while(fgets(resultado,200,pont_arq)!=NULL){
  		strcat(texto_str,resultado);
	  }
  	
  	fclose(pont_arq);
  	
  	
  	
  	tam = strlen(texto_str);
  	for(i=tam-1;i>0;i--){
  		if(texto_str[i]==0x0A){
  			for(cont=tam-1;cont>=i;cont--){
  				texto_str[cont+1]=texto_str[cont];
			  }
  			texto_str[i]=0x0D;
  			tam++;
  		}
		  
	}
	
	
	
	exten(tp);
	
  	pont_arq = fopen(nome, "w+b");
  	
	r = fputs(texto_str, pont_arq);
   
   	
   	if( r == EOF)
   	{
    	printf("Erro ao tentar gravar os dados! \n");
   	}
   	else
    {
        printf("Dados gravados com sucesso. \n");
     }

    
    fclose(pont_arq);
	return;
}



int main(int argc, char *argv[]) {
	
	strcpy(nome, argv[1]);
	strcpy(tipo,argv[2]);
	if(argc>=4){
		strcpy(chave,argv[3]);
	}
	
    
    
    
    if (tipo[0]=='I'){
    	arquivolin();
    	invert();
	}
	else if(tipo[0]=='C'){
		arquivolin();
		if(argc>=4){
			strcpy(chave,argv[3]);
		}
		else{
		printf("A chave nao foi passada");
		exit(0);
		}
		cript();
	}
	else if(tipo[0]=='D'){
		DOSUNIX();
	}
	else if(tipo[0]=='U'){
		UNIXDOS();
	}
	else{
		printf("Uma operacao fora do esperado foi realizada");
	}
			
	
	return 0;
}
