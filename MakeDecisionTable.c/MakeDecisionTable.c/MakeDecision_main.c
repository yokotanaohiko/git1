#include "MakeDecisionSetting.h"

int main(int argc,char *argv[]){

	FILE *fp;
	info *infotable;
	int i,j;
	char filename[256],tmp[256];
	char *cp,*cpEnd;

	info *tmp_table;

	strcpy(tmp,argv[1]);
	infotable=table_file_in(tmp);

	//ファイル名の拡張子以前の部分をtmpに取り出す
	if(strstr(tmp,".")!=NULL){
		cp=strstr(tmp,".");
		cp[0]='\0';
	}else{
		sprintf(tmp,"error.data");
	}

	//出力ファイル名を"入力ファイル名-対象数-テーブル番号.data"に変更(学習用データの作成）
	for(i=0;i<10;i++){
		//対象数50のテーブルを作成
		if( infotable->rowsize > 50 ){
			sprintf(filename,"%s-50-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,50);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//対象数250のテーブルを作成
		if( infotable->rowsize > 250){
			sprintf(filename,"%s-250-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,250);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//対象数500のテーブルを作成
		if( infotable->rowsize > 500){
			sprintf(filename,"%s-500-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,500);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}
	}

	//出力ファイル名を"入力ファイル名-対象数-テーブル番号.test"に変更(学習用データの作成）
	for(i=0;i<10;i++){
		//対象数50のテーブルを作成
		if( infotable->rowsize > 50 ){
			sprintf(filename,"%s-50-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,50);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//対象数250のテーブルを作成
		if( infotable->rowsize > 250){
			sprintf(filename,"%s-250-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,250);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//対象数500のテーブルを作成
		if( infotable->rowsize > 500){
			sprintf(filename,"%s-500-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,500);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}
	}

	free_table(infotable);
	return 0;
}

/*	ドラッグ&ドロップで、ファイルの修正を行うプログラム
	strcpy(tmp,argv[1]);
	infotable=table_file_in(tmp);

	infotable=refine_table("test.csv",infotable);

	//ファイル名の拡張子以前の部分をtmpに取り出す
	if(strstr(tmp,".")!=NULL){
		cp=strstr(tmp,".");
		cp[0]='\0';
	}else{
		sprintf(tmp,"error.data");
	}

	//出力ファイル名を"入力ファイル名.out"に変更
	sprintf(filename,"%s.da",tmp);
	print_table(infotable);
	table_file_out(infotable,filename);
	print_table(infotable);

*/



/*	ドラッグ&ドロップで、対象数50,250,500のテーブルを20個ずつ作成するプログラム
		info *tmp_table;

	strcpy(tmp,argv[1]);
	infotable=table_file_in(tmp);

	//ファイル名の拡張子以前の部分をtmpに取り出す
	if(strstr(tmp,".")!=NULL){
		cp=strstr(tmp,".");
		cp[0]='\0';
	}else{
		sprintf(tmp,"error.data");
	}

	//出力ファイル名を"入力ファイル名-対象数-テーブル番号.data"に変更(学習用データの作成）
	for(i=0;i<10;i++){
		//対象数50のテーブルを作成
		if( infotable->rowsize > 50 ){
			sprintf(filename,"%s-50-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,50);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//対象数250のテーブルを作成
		if( infotable->rowsize > 250){
			sprintf(filename,"%s-250-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,250);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//対象数500のテーブルを作成
		if( infotable->rowsize > 500){
			sprintf(filename,"%s-500-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,500);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}
	}

	//出力ファイル名を"入力ファイル名-対象数-テーブル番号.test"に変更(学習用データの作成）
	for(i=0;i<10;i++){
		//対象数50のテーブルを作成
		if( infotable->rowsize > 50 ){
			sprintf(filename,"%s-50-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,50);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//対象数250のテーブルを作成
		if( infotable->rowsize > 250){
			sprintf(filename,"%s-250-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,250);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//対象数500のテーブルを作成
		if( infotable->rowsize > 500){
			sprintf(filename,"%s-500-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,500);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}
	}

*/