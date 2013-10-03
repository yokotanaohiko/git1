/*
 *�ݒ�t�@�C����ǂݍ���ŁA�ǂݍ��񂾒ʂ�ɏ��\�̏C�����s���B
 *�ݒ�t�@�C���́Acsv�`��
 *�����̎�ނ́A���`�����Ə��������~���l�Ə��������~����
 *���`�����Ȃ�΁A�ݒ�t�@�C���ʂ�ɐ��l������U��
 *���������~���l�Ȃ�΁Again�̕��тɕ��ёւ���
 *���������~�����Ȃ�΁A�ݒ�t�@�C���̒ʂ�ɐ��l������U��
 *���`�����Fnominal
 *���������~���l�ForderNum
 *���������~�����ForderWord
 *���ꂼ��3�s���ǂݍ��ށB
 *��s�ڂ͑����̎�ނƍs���A��s�ڈȍ~�͏C���O�C����̕\
 *�����F�ݒ�t�@�C�����ƕύX������\�@�@�Ԓl�F�ύX��̏��\
 */
#include "MakeDecisionSetting.h"

//�\�̏C���̂��߂̎������X�g
struct list_for_refine{
	char before[STRMAX];	//STRMAX�́A���͂ł��镶����̍ő吔
	char after[STRMAX];
	struct list_for_refine *next;
};

typedef struct list_for_refine rlist;


//�����̒ǉ�
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

//�����̗v�f�����ׂď���
void delete_rlist(rlist *refine_list){
	if(refine_list->next != NULL)delete_rlist(refine_list->next);
	free(refine_list);
}

//������������
void init_rlist(rlist *refine_list){
	strcpy(refine_list->before,"\0");
	strcpy(refine_list->after,"\0");
	refine_list->next=NULL;
}


/*
 *�ݒ�t�@�C���Ɋ�Â��A�e�[�u���̏C�����s��
 */
info *refine_table(char filename[],info *infotable){
	int i,j;
	FILE *fp;
	char buf[STRMAX],tmp[STRMAX],command[STRMAX];
	char before[STRMAX],after[STRMAX];
	char *cp,*cpEnd;				//������ǂݍ��ޑO��̃|�C���^
	int strlength,clm_num;
	int modifyflag=0;				//1:�C�����@0:�C�����łȂ�
	rlist rlist_head;
	init_rlist(&rlist_head);		//�C�����X�g��������

	fp = fopen(filename,"r");
	if(fp == NULL){
		printf("�t�@�C�����J���܂���\n");
		exit(1);
	}


	while(1){
		if(fgets(buf,STRMAX,fp) == NULL)break;
		if(buf == "\n" || buf=="")continue;

		if(modifyflag==1){
			if(buf[0]=='+'){	//�C�����X�g�̏ꍇ�i�s�͂��߂��{�̏ꍇ�j
				
				//�C���O�̕�����bofore�Ɏ擾
				cp=&buf[1];
				cpEnd=strstr(cp,",");
				strlength=cpEnd-cp;
				strncpy(before,cp,strlength);
				before[strlength]='\0';

				//�C����̕�����after�Ɏ擾
				cp=cpEnd+1;
				cpEnd=strstr(cp,"\n");
				if(cpEnd == NULL)cpEnd=strstr(cp,"\0");
				strlength=cpEnd-cp;
				strncpy(after,cp,strlength);
				after[strlength]='\0';

				//�C�����X�g�ɒǉ�
				insert(&rlist_head,before,after);

				//���̍s��ǂݍ���
				continue;
			}else{	//�C�������łȂ��ꍇ�́A�������̏����̑O�ɏ��\�̏C�����s��

				//���\�̏C������
				for(i=0;i<infotable->rowsize;i++){
					rlist *rp;
					for(rp=rlist_head.next;rp!=NULL;rp=rp->next){
						if( strcmp( infotable->matrix[i][clm_num-1] , rp->before )==0 ){
							strcpy(infotable->matrix[i][clm_num-1],rp->after);
						}
					}
				}

				//�C�����X�g�̏�����
				delete_rlist(rlist_head.next);
				init_rlist(&rlist_head);
				
				//�C�������t���O
				modifyflag=0;
			}
		}
		
		cp=buf;
		//clm_num�ɏC������񐔂��擾
		cpEnd=strstr(cp,",");
		strlength=cpEnd-cp;
		strncpy(tmp,cp,strlength);
		tmp[strlength]='\0';
		clm_num = atoi(tmp);

		//command�ɏC�����@���擾
		cp=cpEnd+1;
		cpEnd=strstr(cp,"\n");
		if(cpEnd == NULL){			//�ݒ�t�@�C���̍ŏI�s�̏ꍇ
			strcpy(command,cp);
		}else{						//�ŏI�s�łȂ��ꍇ
			strlength=cpEnd-cp;
			strncpy(command,cp,strlength);
			command[strlength]='\0';
		};

		if(strcmp(command,"nominal")==0){
			modifyflag=1;
		}else if( strcmp(command,"reverse")==0 ){
			int max=0;
				
			//�ő�l���擾
			for(i=0;i<infotable->rowsize;i++){
				if( max < atoi(infotable->matrix[i][clm_num-1]) ){
					max = atoi(infotable->matrix[i][clm_num-1]);
				}
			}

			//���l���t�]������
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
			printf("�ǂݍ��߂Ȃ�������ł�");
			exit(1);
		}
		
	}

	//
	if(modifyflag == 1){
		//���\�̏C������
		for(i=0;i<infotable->rowsize;i++){
			rlist *rp;
			for(rp=rlist_head.next;rp!=NULL;rp=rp->next){
				if( strcmp( infotable->matrix[i][clm_num-1] , rp->before )==0 ){
					strcpy(infotable->matrix[i][clm_num-1],rp->after);
					printf("%s\n",infotable->matrix[i][clm_num-1]);
				}
			}
		}

		//�C�����X�g�̏�����
		delete_rlist(rlist_head.next);
		init_rlist(&rlist_head);

		//�C�������t���O
	}
	
	if(rlist_head.next != NULL)delete_rlist(rlist_head.next);
	fclose(fp);

	return infotable;
}