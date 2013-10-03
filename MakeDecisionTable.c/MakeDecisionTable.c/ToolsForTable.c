#include "MakeDecisionSetting.h"


//���\�̕\��
void print_table(info *table){
	int i,j;
	for(i=0;i<table->rowsize;i++){
		for(j=0;j<table->clmsize;j++){
			printf(table->matrix[i][j]);
			if(j < table->clmsize-1 )printf(",");
		}
		printf("\n");
	}
}

//���\�̊J��
void free_table(info *infotable){
	int i,j;

	for(i=0;i<infotable->rowsize;i++){
		for(j=0;j<infotable->clmsize;j++){
			free(infotable->matrix[i][j]);
		}
		free( infotable->matrix[i] );
	}
	free(infotable->matrix);


	free(infotable);

	infotable=NULL;
}