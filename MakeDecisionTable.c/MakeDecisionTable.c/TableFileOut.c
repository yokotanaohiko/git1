#include "MakeDecisionSetting.h"

void table_file_out(info *infotable,char filename[]){
	FILE *fp;
	int i,j;

	fp = fopen(filename,"w");
	if(fp==NULL){
		printf("ファイルは開けません");
		exit(1);
	}
	fprintf(fp,"a\nb\nc\n");
	for(i=0;i<infotable->rowsize;i++){
		for(j=0;j<infotable->clmsize;j++){
			fprintf(fp,infotable->matrix[i][j]);
			if(j < infotable->clmsize-1 )fprintf(fp,",");
		}
		fprintf(fp,"\n");
	}

	fclose(fp);
}