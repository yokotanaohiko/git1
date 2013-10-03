#include "MakeDecisionSetting.h"
/*
 *stdio.h , stdlib.h , string.h
 *�̓C���N���[�h�ς�
 */

#include <time.h>

info *random_table_make(info *infotable,int num){
	info *random_table;
	char ***table;
	int i,j;

	random_table=(info *)malloc( sizeof(info) );

	//�V�����쐬������\�̗̈���m��
	table = (char ***)malloc( sizeof(char**) * num );
	for(i=0;i<num;i++){
		table[i] = (char **)malloc( sizeof(char*) * infotable->clmsize );
		for(j=0;j<infotable->clmsize;j++){

			table[i][j] = (char *)malloc( sizeof(char) * STRMAX );
		}
	}

	srand( (unsigned)time(NULL) );

	//�����̏��\����A�����_���ɑΏۂ�I�ѐV�������\�ɉ�����B
	for(i=0;i<num;i++){
		for(j=0;j<infotable->clmsize;j++){
			strcpy(table[i][j],infotable->matrix[rand()%infotable->rowsize][j]);
		}
	}

	//�V�������\�̏���ǉ�
	random_table->matrix=table;
	random_table->clmsize=infotable->clmsize;
	random_table->rowsize=num;

	return random_table;
}