#include "MakeDecisionSetting.h"
/*
 *stdio.h , stdlib.h , string.h
 *はインクルード済み
 */

#include <time.h>

info *random_table_make(info *infotable,int num){
	info *random_table;
	char ***table;
	int i,j;

	random_table=(info *)malloc( sizeof(info) );

	//新しく作成する情報表の領域を確保
	table = (char ***)malloc( sizeof(char**) * num );
	for(i=0;i<num;i++){
		table[i] = (char **)malloc( sizeof(char*) * infotable->clmsize );
		for(j=0;j<infotable->clmsize;j++){

			table[i][j] = (char *)malloc( sizeof(char) * STRMAX );
		}
	}

	srand( (unsigned)time(NULL) );

	//引数の情報表から、ランダムに対象を選び新しい情報表に加える。
	for(i=0;i<num;i++){
		for(j=0;j<infotable->clmsize;j++){
			strcpy(table[i][j],infotable->matrix[rand()%infotable->rowsize][j]);
		}
	}

	//新しい情報表の情報を追加
	random_table->matrix=table;
	random_table->clmsize=infotable->clmsize;
	random_table->rowsize=num;

	return random_table;
}