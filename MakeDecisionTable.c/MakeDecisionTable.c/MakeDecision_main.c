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

	//�t�@�C�����̊g���q�ȑO�̕�����tmp�Ɏ��o��
	if(strstr(tmp,".")!=NULL){
		cp=strstr(tmp,".");
		cp[0]='\0';
	}else{
		sprintf(tmp,"error.data");
	}

	//�o�̓t�@�C������"���̓t�@�C����-�Ώې�-�e�[�u���ԍ�.data"�ɕύX(�w�K�p�f�[�^�̍쐬�j
	for(i=0;i<10;i++){
		//�Ώې�50�̃e�[�u�����쐬
		if( infotable->rowsize > 50 ){
			sprintf(filename,"%s-50-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,50);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//�Ώې�250�̃e�[�u�����쐬
		if( infotable->rowsize > 250){
			sprintf(filename,"%s-250-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,250);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//�Ώې�500�̃e�[�u�����쐬
		if( infotable->rowsize > 500){
			sprintf(filename,"%s-500-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,500);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}
	}

	//�o�̓t�@�C������"���̓t�@�C����-�Ώې�-�e�[�u���ԍ�.test"�ɕύX(�w�K�p�f�[�^�̍쐬�j
	for(i=0;i<10;i++){
		//�Ώې�50�̃e�[�u�����쐬
		if( infotable->rowsize > 50 ){
			sprintf(filename,"%s-50-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,50);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//�Ώې�250�̃e�[�u�����쐬
		if( infotable->rowsize > 250){
			sprintf(filename,"%s-250-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,250);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//�Ώې�500�̃e�[�u�����쐬
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

/*	�h���b�O&�h���b�v�ŁA�t�@�C���̏C�����s���v���O����
	strcpy(tmp,argv[1]);
	infotable=table_file_in(tmp);

	infotable=refine_table("test.csv",infotable);

	//�t�@�C�����̊g���q�ȑO�̕�����tmp�Ɏ��o��
	if(strstr(tmp,".")!=NULL){
		cp=strstr(tmp,".");
		cp[0]='\0';
	}else{
		sprintf(tmp,"error.data");
	}

	//�o�̓t�@�C������"���̓t�@�C����.out"�ɕύX
	sprintf(filename,"%s.da",tmp);
	print_table(infotable);
	table_file_out(infotable,filename);
	print_table(infotable);

*/



/*	�h���b�O&�h���b�v�ŁA�Ώې�50,250,500�̃e�[�u����20���쐬����v���O����
		info *tmp_table;

	strcpy(tmp,argv[1]);
	infotable=table_file_in(tmp);

	//�t�@�C�����̊g���q�ȑO�̕�����tmp�Ɏ��o��
	if(strstr(tmp,".")!=NULL){
		cp=strstr(tmp,".");
		cp[0]='\0';
	}else{
		sprintf(tmp,"error.data");
	}

	//�o�̓t�@�C������"���̓t�@�C����-�Ώې�-�e�[�u���ԍ�.data"�ɕύX(�w�K�p�f�[�^�̍쐬�j
	for(i=0;i<10;i++){
		//�Ώې�50�̃e�[�u�����쐬
		if( infotable->rowsize > 50 ){
			sprintf(filename,"%s-50-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,50);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//�Ώې�250�̃e�[�u�����쐬
		if( infotable->rowsize > 250){
			sprintf(filename,"%s-250-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,250);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//�Ώې�500�̃e�[�u�����쐬
		if( infotable->rowsize > 500){
			sprintf(filename,"%s-500-%d.data",tmp,i);
			tmp_table=random_table_make(infotable,500);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}
	}

	//�o�̓t�@�C������"���̓t�@�C����-�Ώې�-�e�[�u���ԍ�.test"�ɕύX(�w�K�p�f�[�^�̍쐬�j
	for(i=0;i<10;i++){
		//�Ώې�50�̃e�[�u�����쐬
		if( infotable->rowsize > 50 ){
			sprintf(filename,"%s-50-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,50);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//�Ώې�250�̃e�[�u�����쐬
		if( infotable->rowsize > 250){
			sprintf(filename,"%s-250-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,250);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}

		//�Ώې�500�̃e�[�u�����쐬
		if( infotable->rowsize > 500){
			sprintf(filename,"%s-500-%d.test",tmp,i);
			tmp_table=random_table_make(infotable,500);
			table_file_out(tmp_table,filename);
			free_table(tmp_table);
		}
	}

*/