/*
 *設定ファイルを読み込んで、読み込んだ通りに情報表の修正を行う。
 *設定ファイルは、csv形式
 *属性の種類は、名義属性と序数属性×数値と序数属性×文字
 *名義属性ならば、設定ファイル通りに数値を割り振る
 *序数属性×数値ならば、gainの並びに並び替える
 *序数属性×文字ならば、設定ファイルの通りに数値を割り振る
 *名義属性：nominal
 *序数属性×数値：orderNum
 *序数属性×文字：orderWord
 *それぞれ3行ずつ読み込む。
 *一行目は属性の種類と行数、二行目以降は修正前修正後の表
 *引数：設定ファイル名と変更する情報表　　返値：変更後の情報表
 */
#include "MakeDecisionSetting.h"

//表の修正のための辞書リスト
struct list_for_refine{
	char before[STRMAX];	//STRMAXは、入力できる文字列の最大数
	char after[STRMAX];
	struct list_for_refine *next;
};

typedef struct list_for_refine rlist;


//辞書の追加
void insert(rlist *refine_list,char before[],char after[]){
	rlist *lp,*newrlist;
	newrlist = (rlist *)malloc( sizeof(rlist) );
	
	lp = refine_list;
	while(lp->next != NULL)	lp = lp->next;

	strcpy(newrlist->before,before);
	strcpy(newrlist->after,after);
	newrlist->next = NULL;

	lp->next = newrlist;
}

//辞書の要素をすべて消去
void delete_rlist(rlist *refine_list){
	if(refine_list->next != NULL)delete_rlist(refine_list->next);
	free(refine_list);
}

//辞書を初期化
void init_rlist(rlist *refine_list){
	strcpy(refine_list->before,"\0");
	strcpy(refine_list->after,"\0");
	refine_list->next=NULL;
}


/*
 *設定ファイルに基づき、テーブルの修正を行う
 */
info *refine_table(char filename[],info *infotable){
	int i,j;
	FILE *fp;
	char buf[STRMAX],tmp[STRMAX],command[STRMAX];
	char before[STRMAX],after[STRMAX];
	char *cp,*cpEnd;				//文字を読み込む前後のポインタ
	int strlength,clm_num;
	int modifyflag=0;				//1:修正中　0:修正中でない
	rlist rlist_head;
	init_rlist(&rlist_head);		//修正リストを初期化

	fp = fopen(filename,"r");
	if(fp == NULL){
		printf("ファイルが開けません\n");
		exit(1);
	}


	while(1){
		if(fgets(buf,STRMAX,fp) == NULL)break;
		if(buf == "\n" || buf=="")continue;

		if(modifyflag==1){
			if(buf[0]=='+'){	//修正リストの場合（行はじめが＋の場合）
				
				//修正前の文字をboforeに取得
				cp=&buf[1];
				cpEnd=strstr(cp,",");
				strlength=cpEnd-cp;
				strncpy(before,cp,strlength);
				before[strlength]='\0';

				//修正後の文字をafterに取得
				cp=cpEnd+1;
				cpEnd=strstr(cp,"\n");
				if(cpEnd == NULL)cpEnd=strstr(cp,"\0");
				strlength=cpEnd-cp;
				strncpy(after,cp,strlength);
				after[strlength]='\0';

				//修正リストに追加
				insert(&rlist_head,before,after);

				//次の行を読み込む
				continue;
			}else{	//修正文字でない場合は、属性情報の処理の前に情報表の修正を行う

				//情報表の修正処理
				for(i=0;i<infotable->rowsize;i++){
					rlist *rp;
					for(rp=rlist_head.next;rp!=NULL;rp=rp->next){
						if( strcmp( infotable->matrix[i][clm_num-1] , rp->before )==0 ){
							strcpy(infotable->matrix[i][clm_num-1],rp->after);
						}
					}
				}

				//修正リストの初期化
				delete_rlist(rlist_head.next);
				init_rlist(&rlist_head);
				
				//修正完了フラグ
				modifyflag=0;
			}
		}
		
		cp=buf;
		//clm_numに修正する列数を取得
		cpEnd=strstr(cp,",");
		strlength=cpEnd-cp;
		strncpy(tmp,cp,strlength);
		tmp[strlength]='\0';
		clm_num = atoi(tmp);

		//commandに修正方法を取得
		cp=cpEnd+1;
		cpEnd=strstr(cp,"\n");
		if(cpEnd == NULL){			//設定ファイルの最終行の場合
			strcpy(command,cp);
		}else{						//最終行でない場合
			strlength=cpEnd-cp;
			strncpy(command,cp,strlength);
			command[strlength]='\0';
		};

		if(strcmp(command,"nominal")==0){
			modifyflag=1;
		}else if( strcmp(command,"reverse")==0 ){
			int max=0;
				
			//最大値を取得
			for(i=0;i<infotable->rowsize;i++){
				if( max < atoi(infotable->matrix[i][clm_num-1]) ){
					max = atoi(infotable->matrix[i][clm_num-1]);
				}
			}

			//数値を逆転させる
			for(i=0;i<infotable->rowsize;i++){
				itoa( max-atoi(infotable->matrix[i][clm_num-1]) , tmp ,10);
				strcpy(infotable->matrix[i][clm_num-1],tmp);
			}

		}else if( strcmp(command,"orderWord")==0 ){
			modifyflag=1;
		}else if( strcmp(command,"swap_to_decision")==0 ){
			for(i=0;i<infotable->rowsize;i++){
				strcpy(tmp,infotable->matrix[i][clm_num-1]);
				strcpy(infotable->matrix[i][clm_num-1],infotable->matrix[i][infotable->clmsize-1]);
				strcpy(infotable->matrix[i][infotable->clmsize-1],tmp);
				printf("%d,%d\n",i,infotable->rowsize);
			}
		}else{
			printf("読み込めない文字列です");
			exit(1);
		}
		
	}

	//
	if(modifyflag == 1){
		//情報表の修正処理
		for(i=0;i<infotable->rowsize;i++){
			rlist *rp;
			for(rp=rlist_head.next;rp!=NULL;rp=rp->next){
				if( strcmp( infotable->matrix[i][clm_num-1] , rp->before )==0 ){
					strcpy(infotable->matrix[i][clm_num-1],rp->after);
					printf("%s\n",infotable->matrix[i][clm_num-1]);
				}
			}
		}

		//修正リストの初期化
		delete_rlist(rlist_head.next);
		init_rlist(&rlist_head);

		//修正完了フラグ
	}
	
	if(rlist_head.next != NULL)delete_rlist(rlist_head.next);
	fclose(fp);

	return infotable;
}