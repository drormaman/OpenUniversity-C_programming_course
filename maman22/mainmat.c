#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAT_SIZE 4
#define MAX_VALUES 16
#define MAT_NUM 6
#define CMD_NUM 2
#define MAX_LINE 200

typedef double mat[MAT_SIZE][MAT_SIZE];
typedef struct {
	char *name;
	mat *matrix;
} matItem;
typedef struct {
	mat *mat1;
	mat *mat2;
	mat *resmat;
} matColl;

char *trimWhiteSpace(char *str){
	char *end;
	while(isspace((unsigned char)*str)) str++;
	if(*str == 0)  return str;
	end = str + strlen(str) - 1;
	while(end > str && isspace((unsigned char)*end)) end--;
	end[1] = '\0';
	return str;
}

void initMat(mat matrix, int num){
	int i, j;
	for(i = 0; i < MAT_SIZE; i++) {
		for(j = 0; j < MAT_SIZE; j++) {
			*(*(matrix+i)+j) = num;
		}
	}
}

void printMat(mat matrix){
	int i, j;
	for(i = 0; i < MAT_SIZE; i++) {
		for(j = 0; j < MAT_SIZE; j++) {
			printf("%7.2f", *(*(matrix + i)+j));	
		}
		printf("\n");
	}
}

char *getCommandStr(char *line) {
	return strtok(line, " ");
}

mat *getMat(matItem mats[], char *name) {
	mat *pmat = NULL;
	int i;

	for (i=0;i<MAT_NUM;i++){
		if(strcmp(mats[i].name, name) == 0)
			pmat = mats[i].matrix;
	}
	if(*pmat == NULL)
		printf("Undefined matrix name");
	return pmat;
}


void insertValuesToMat(mat matrix, double values[]) {
	int i, j;
	for(i = 0; i < MAT_SIZE; i++) {
		for(j = 0; j < MAT_SIZE; j++) {
			*(*(matrix+i)+j) = values[i*MAT_SIZE+j];
		}
	}

}
void readMat(matItem mats[]) {
	int i = 0;
	char *args;
	double values[MAT_SIZE * MAT_SIZE] = {0};
	mat *matrix;
	
	args = strtok(NULL, ",");
	matrix = getMat(mats, args);

	while((args = strtok(NULL, ",") )!= NULL && i < MAT_SIZE*MAT_SIZE){
		values[i++] = atof(args);
	}
	insertValuesToMat(*matrix, values);
}

void addMat(matItem mats[]){
	mat *mat1, *mat2, *resmat;
	char *matName;
	int i,j;
	matName = trimWhiteSpace(strtok(NULL, ","));
	mat1 = getMat(mats, matName);
	matName = trimWhiteSpace(strtok(NULL, ","));
	mat2 = getMat(mats, matName);
	matName = trimWhiteSpace(strtok(NULL, ","));
	resmat = getMat(mats, matName);

	if (*mat1 != NULL && *mat2 != NULL && *resmat != NULL) {
		for(i=0; i<MAT_SIZE;i++){
			for(j=0;j<MAT_SIZE;j++){
				(*resmat)[i][j] = (*mat1)[i][j] + (*mat2)[i][j];
			}
		}
		printMat(*resmat);
	}
}

void subMat(matItem mats[]){
	mat *mat1, *mat2, *resmat;
	char *matName;
	int i,j;
	matName = trimWhiteSpace(strtok(NULL, ","));
	mat1 = getMat(mats, matName);
	matName = trimWhiteSpace(strtok(NULL, ","));
	mat2 = getMat(mats, matName);
	matName = trimWhiteSpace(strtok(NULL, ","));
	resmat = getMat(mats, matName);

	if (*mat1 != NULL && *mat2 != NULL && *resmat != NULL) {
		for(i=0; i<MAT_SIZE;i++){
			for(j=0;j<MAT_SIZE;j++){
				(*resmat)[i][j] = (*mat1)[i][j] - (*mat2)[i][j];
			}
		}
		printMat(*resmat);
	}
}

void multiplyMat(matItem mats[]){
	mat *mat1, *mat2, *resmat;
	char *matName;
	int i,j,k;
	double rproduct;
	matName = trimWhiteSpace(strtok(NULL, ","));
	mat1 = getMat(mats, matName);
	matName = trimWhiteSpace(strtok(NULL, ","));
	mat2 = getMat(mats, matName);
	matName = trimWhiteSpace(strtok(NULL, ","));
	resmat = getMat(mats, matName);

	if (*mat1 != NULL && *mat2 != NULL && *resmat != NULL) {
		for(i=0; i<MAT_SIZE;i++){
			for(j=0;j<MAT_SIZE;j++){
				rproduct = 0;
				for(k=0;k<MAT_SIZE;k++){
					rproduct += (*mat1)[i][k] * (*mat2)[k][j];
				}
				(*resmat)[i][j] = rproduct;
			}
		}
		printMat(*resmat);
	}
}

void multiplyScalar(matItem mats[]){
	mat *mat1, *resmat;
	char *matName;
	int i,j;
	double scalar;
	matName = trimWhiteSpace(strtok(NULL, ","));
	mat1 = getMat(mats, matName);
	scalar = atof(strtok(NULL, ","));
	matName = trimWhiteSpace(strtok(NULL, ","));
	resmat = getMat(mats, matName);

	if (*mat1 != NULL && *mat2 != NULL && *resmat != NULL) {
		for(i=0; i<MAT_SIZE;i++){
			for(j=0;j<MAT_SIZE;j++){
				(*resmat)[i][j] = (*mat1)[i][j] * scalar;
			}
		}
		printMat(*resmat);
}

void transposeMat(matItem mats[]){
	mat *mat1, *resmat;
	char *matName;
	int i,j;
	matName = trimWhiteSpace(strtok(NULL, ","));
	mat1 = getMat(mats, matName);
	matName = trimWhiteSpace(strtok(NULL, ","));
	resmat = getMat(mats, matName);

	for(i=0; i<MAT_SIZE;i++){
		for(j=0;j<MAT_SIZE;j++){
			(*resmat)[i][j] = (*mat1)[j][i];
		}
	}
	printMat(*resmat);
}

int main()
{
	mat MAT_A = {0}, MAT_B = {0}, MAT_C = {0}, MAT_D = {0}, MAT_E = {0}, MAT_F = {0};
	char line[MAX_LINE];
	int stop = 0;
	char *command;
	matItem mats[MAT_NUM];
	mats[0].name = "MAT_A";
	mats[0].matrix = &MAT_A;
	mats[1].name = "MAT_B";
	mats[1].matrix = &MAT_B;
	mats[2].name = "MAT_C";
	mats[2].matrix = &MAT_C;
	mats[3].name = "MAT_D";
	mats[3].matrix = &MAT_D;
	mats[4].name = "MAT_E";
	mats[4].matrix = &MAT_E;
	mats[5].name = "MAT_F";
	mats[5].matrix = &MAT_F;

	initMat(MAT_A, 1);
	initMat(MAT_B, 3);

	printf("\nplease enter commands:");
	fgets(line, MAX_LINE, stdin);
	while(!stop && line != NULL) {
		line[strlen(line)-1] = '\0';
		command = getCommandStr(line);
		if(strcmp("read_mat", command) == 0) {
			readMat(mats);
		} else if (strcmp("print_mat", command) == 0) {
			printMat(*(getMat(mats, strtok(NULL, " "))));
		} else if (strcmp("add_mat", command) == 0) {
			addMat(mats);
		} else if (strcmp("sub_mat", command) == 0) {
			subMat(mats);
		} else if (strcmp("mul_mat", command) == 0) {
			multiplyMat(mats);
		} else if (strcmp("mul_scalar", command) == 0) {
			multiplyScalar(mats);
		} else if (strcmp("trans_mat", command) == 0) {
			transposeMat(mats);
		} else if (strcmp("stop", command) == 0) {
			stop = 1;
		}
		
		if (!stop) {
			printf("\nplease enter commands:");
			fgets(line, MAX_LINE, stdin);
		} else {
			printf("\nprogram stopped");
		}
	}


	return 1;
}

/*


init mat function (init all values to 0)


readMat(){}
printMat(){}
addMat(){}
subMat(){}
mulMat(){}
mulScalar(){}
transMat(){}



*/

/*
struct {
	char *name;
	void (*func)(matItem *);
} cmd[CMD_NUM] = {
	{"read_mat", &readMat}
};

void *((*)(matItem *))getCommandFunc(char *cmdstr){
	int i;
	void (*func)(matItem *);
	for (i=0; i<CMD_NUM;i++){
		if (strcmp(cmd[i].name, cmdstr));
			func = cmd[i].func;
	}
	return func;
}

*/