#include "MakeDecisionSetting.h"

info *table_file_in(char filename[]){

	FILE *fp;
	char buf[STRMAX];	//STRMAXは、入力できる文字列の最大数
	char ***table,*cp,*cpEnd;
	int rowsize=0,clmsize=0;
	int i,j;
	info *infotable;	//info：情報表のクラス（構造体）

	infotable=(info *)malloc( sizeof(info) );
	

	/*
	 *行数を数える
	 */
	fp = fopen(filename,"r");
	if(fp == NULL){
		printf("%sファイルが開けません\n",filename);
		exit(1);
	}

	while(fgets(buf,STRMAX,fp) != NULL){
		rowsize++;
	}
	fclose(fp);



	/*
	 *列数を数える
	 */
	fp = fopen(filename,"r");
	if( fp == NULL){
		printf("%sファイルが開けません",filename);
		exit(1);
	}
	fgets(buf,STRMAX,fp);
	for(i=0;buf[i]!='\n';i++){
		if(buf[i]==',')clmsize++;
	}
	clmsize++;
	fclose(fp);
	



	/*
	 *情報表作成
	 */
	
	//情報表の領域確保
	table = (char ***)malloc( sizeof(char**) * rowsize );
	for(i=0;i<rowsize;i++){
		table[i] = (char **)malloc( sizeof(char*) * clmsize );
		for(j=0;j<clmsize;j++){

			table[i][j] = (char *)malloc( sizeof(char) * STRMAX );
		}
	}
	
	//情報表の読み込み
	fp = fopen(filename,"r");

	for(i=0;i<rowsize;i++){
		cpEnd =NULL;
		fgets(buf,STRMAX,fp);				//一行読み込み
		cp=buf;								//文字の読み始めのポインタの初期化
		for(j=0;j<clmsize;j++){
			int strlength=0;
			if(cpEnd != NULL)cp = ++cpEnd;	//カンマの次の文字を読み始めとする
			if( strstr(cp,",") != NULL){
				cpEnd = strstr(cp,",");		//読み終わりのポインタとして、カンマの位置を取得
			}else if(strstr(cp,"\n") != NULL){
				cpEnd = strstr(cp,"\n");	//以後の文字にカンマがなければ、改行の位置を取得
			}else{
				cpEnd = strstr(cp,"\0");
			}
			
			strlength = cpEnd - cp;			//文字数を計算
			strncpy(table[i][j],cp,strlength);
			table[i][j][strlength]='\0';	//表の要素の最後に終了文字を追加
		}
	}
	fclose(fp);


	//情報表のクラス情報入力
	infotable->matrix=table;
	infotable->rowsize=rowsize;
	infotable->clmsize=clmsize;
	
	return infotable;
}