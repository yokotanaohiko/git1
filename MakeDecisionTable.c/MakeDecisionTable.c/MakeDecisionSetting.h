#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRMAX 256


struct infomation_table{
	char ***matrix;
	int rowsize;
	int clmsize;
};

typedef struct infomation_table info;


info *table_file_in(char filename[]);
void print_table(info * );
void table_file_out(info * ,char []);
info *refine_table(char *,info *);
info *random_table_make(info *,int );
void free_table(info *);