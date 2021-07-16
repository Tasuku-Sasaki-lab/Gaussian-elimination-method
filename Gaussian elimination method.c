#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 0.00005
#define BUF_SIZE 100

void pivot(double **a,double b[],int where,int n){
	int fabs_max=where+1;
	double num;

	//絶対値が一番大きいいところを探す
	for(int i=where+2;i<n;i++){
		if(fabs(a[i][where])>fabs(a[fabs_max][where])){
			fabs_max=i;
		}
	}

	//whereの行とfabs_maxの行を入れ替え
	for(int i=0;i<n;i++){
		num=a[where][i];
		a[where][i]=a[fabs_max][i];
		a[fabs_max][i]=num;
	}

	num=b[where];
	b[where]=b[fabs_max];
	b[fabs_max]=num;
}

int main(void){
	system("chcp 65001");

	double **a;
	double *b;
	double c;
	double *x;

	
	FILE *fp;
	char buf[BUF_SIZE];
	int line = 0;
	char FILE_NAME[]="gauss_data.txt";
	char FILE_NAME_DEBUG[]="test.txt";

	if((fp=fopen(FILE_NAME,"r"))==NULL){
		printf("%sを開けませんでした",FILE_NAME_DEBUG);
		return 1;
	}

	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		line++;
	}

	printf("現在のファイルの行数は「%d」です。\n",line);
	//ファイルポインタを先頭まで戻す
	
	rewind(fp);

	a=(double **)malloc(sizeof(double * )*line);

	for(int i=0;i<line;i++)
	  a[i]=(double *)malloc(sizeof(double)*line);
	
	b=(double *)malloc(sizeof(double));

	x=(double *)malloc(sizeof(double));



	for(int i=0;i<line;i++){
		for(int j=0;j<line;j++){
			fscanf(fp,"%lf",&a[i][j]);
		}
		fscanf(fp,"%lf",&b[i]);
	}


/*
	for(int i=0;i<line;i++){
		for(int j=0;j<line;j++){
			printf("%f ",a[i][j]);
		}
		printf("\n");
	}
*/

//前進消去
for(int k=0;k<line-1;k++){
	if(a[k][k]==0||a[k][k]<e){//丸め誤差
		pivot(a,b,k,line);
	}
	for(int i=k;i<line-1;i++){
		c=a[i+1][k]/a[k][k];
		//printf("%f l \t",c);
		for(int j=k;j<line-1;j++){
			a[i+1][j+1]=a[i+1][j+1]-c*a[k][j+1];
			//printf("a[%d][%d]=%f\t",i+1,j+1,a[i+1][j+1]);
		}
		b[i+1]=b[i+1]-c*b[k];
		//printf("b[%d]=%f\n",i+1,b[i+1]);
	}
}
//後進代入
for(int i=line-1;i>=0;i--){
	c=0;
	for(int j=line-1;j>i;j--){
		c+=a[i][j]*x[j];
	}
	x[i]=(b[i]-c)/a[i][i];
}

for(int i=0;i<line;i++){
		printf("x[%d]=%f\n",i+1,x[i]);
}

for(int i=0;i<line;i++)
	free(a[i]);

free(a);
free(b);
free(x);


return 0;
}

/*PIVOTデバック用
int main(void){	
	double a[3][3];
	double b[3];

	a[0][0]=0,a[0][1]=2,a[0][2]=1;
	a[1][0]=4,a[1][1]=4,a[1][2]=1;
	a[2][0]=-2,a[2][1]=1,a[2][2]=-2;

	b[0]=-1,b[1]=-1,b[2]=10;

	pivot(a,b,0,3);
	
	
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%f ",a[i][j]);
		}
		printf("\n");
	}
	for(int i=0;i<3;i++){
		printf("%f ",b[i]);
}
	return 0;
}
*/

