#include "MakeDecisionSetting.h"

info *table_file_in(char filename[]){

	FILE *fp;
	char buf[STRMAX];	//STRMAX�́A���͂ł��镶����̍ő吔
	char ***table,*cp,*cpEnd;
	int rowsize=0,clmsize=0;
	int i,j;
	info *infotable;	//info�F���\�̃N���X�i�\���́j

	infotable=(info *)malloc( sizeof(info) );
	

	/*
	 *�s���𐔂���
	 */
	fp = fopen(filename,"r");
	if(fp == NULL){
		printf("%s�t�@�C�����J���܂���\n",filename);
		exit(1);
	}

	while(fgets(buf,STRMAX,fp) != NULL){
		rowsize++;
	}
	fclose(fp);



	/*
	 *�񐔂𐔂���
	 */
	fp = fopen(filename,"r");
	if( fp == NULL){
		printf("%s�t�@�C�����J���܂���",filename);
		exit(1);
	}
	fgets(buf,STRMAX,fp);
	for(i=0;buf[i]!='\n';i++){
		if(buf[i]==',')clmsize++;
	}
	clmsize++;
	fclose(fp);
	



	/*
	 *���\�쐬
	 */
	
	//���\�̗̈�m��
	table = (char ***)malloc( sizeof(char**) * rowsize );
	for(i=0;i<rowsize;i++){
		table[i] = (char **)malloc( sizeof(char*) * clmsize );
		for(j=0;j<clmsize;j++){

			table[i][j] = (char *)malloc( sizeof(char) * STRMAX );
		}
	}
	
	//���\�̓ǂݍ���
	fp = fopen(filename,"r");

	for(i=0;i<rowsize;i++){
		cpEnd =NULL;
		fgets(buf,STRMAX,fp);				//��s�ǂݍ���
		cp=buf;								//�����̓ǂݎn�߂̃|�C���^�̏�����
		for(j=0;j<clmsize;j++){
			int strlength=0;
			if(cpEnd != NULL)cp = ++cpEnd;	//�J���}�̎��̕�����ǂݎn�߂Ƃ���
			if( strstr(cp,",") != NULL){
				cpEnd = strstr(cp,",");		//�ǂݏI���̃|�C���^�Ƃ��āA�J���}�̈ʒu���擾
			}else if(strstr(cp,"\n") != NULL){
				cpEnd = strstr(cp,"\n");	//�Ȍ�̕����ɃJ���}���Ȃ���΁A���s�̈ʒu���擾
			}else{
				cpEnd = strstr(cp,"\0");
			}
			
			strlength = cpEnd - cp;			//���������v�Z
			strncpy(table[i][j],cp,strlength);
			table[i][j][strlength]='\0';	//�\�̗v�f�̍Ō�ɏI��������ǉ�
		}
	}
	fclose(fp);


	//���\�̃N���X������
	infotable->matrix=table;
	infotable->rowsize=rowsize;
	infotable->clmsize=clmsize;
	
	return infotable;
}