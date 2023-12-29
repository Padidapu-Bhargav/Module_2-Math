#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libs/matfun.h"
#define TOLERANCE 1e-6

int  main()
{

FILE *fp; //file pointer
double **A,**B,**C,**D,**M,**E,**vertices; //declaring matrices names
double AB,AC,AD,AE,BC,BD,BE,CD,CE,DE; //side lengths
int m =2, n=1; // (mxn) matrix
double l = 6; //length of a side 
double CMA,BMD,DBC,BCA;
double theta,Alpha,Beta,Beta1;

vertices = createMat(m,3);
vertices = loadMat("Vec.dat",m, 3);
printf("\n vertices\n");
printMat(vertices,2,3);

//creating Matrix B and loading the first column of the vertivces data file
B = createMat(m,n);
B = Matcol(vertices,2,0);
//printf("\nB\n");
//printMat(B,2,1);

//creating Matrix D and loading the second column of the vertices data file
D = createMat(m,n);
D = Matcol(vertices,2,1);
//printf("\nD\n");
//printMat(D,2,1);

//creating Matrix A and loading the third column of the vertices data file
C =createMat(m,n);
C = Matcol(vertices,2,2);
//printf("\nC\n");
//printMat(C,2,1);

//lengths of All sides 
BD = Matnorm(Matsub(B,D,m,n),m);
CD = Matnorm(Matsub(C,D,m,n),m);

//printf("\nBD = %lf \n",BD);
//printf("\nCD = %lf \n",CD);

theta =60;
Alpha = (180 - theta)/2;

AB = BD * (sin(Alpha*(M_PI/180)) / sin(theta*(M_PI/180)));
//printf("AB = %lf \n",AB);

//finding point A using Alpha , AB and B
A = Mat_1(B, AB, Alpha*(M_PI/180),1);

printf("\nA\n");
printMat(A,2,1);

AD= Matnorm(Matsub(A,D,m,n),m);
AC= Matnorm(Matsub(A,C,m,n),m);

//printf("\nAD = %lf \n",AD);
//printf("\nAC = %lf \n",AC);

Beta1=(180/M_PI)*acos((AC*AC+CD*CD-AD*AD)/(2*AC*CD));
//printf("Beta1 : %lf",Beta1);

CE = AC * (sin(theta*(M_PI/180)) / sin(Alpha*(M_PI/180)));
//printf("\nCE = %lf \n",CE);

Beta = Alpha + Beta1;
//printf("\nBeta = %lf ", Beta);

E = Mat_1(C,CE,Beta*(M_PI/180),-1);
printf("\nE\n");
printMat(E,2,1);

AE= Matnorm(Matsub(A,E,m,n),m);
BC= Matnorm(Matsub(B,C,m,n),m);
DE= Matnorm(Matsub(D,E,m,n),m);

//printf("\nBC = %lf \n",BC);
//printf("\nDE = %lf \n",DE);
//printf("\nAE = %lf \n",AE);


if( round(AB) == round(AD) ){
	printf("\nAD equals to AB\n");}
else{
	printf("\nAD not equals to AB\n");}

if( round(AC) == round(AE) ){
	printf("\nAC equals to AE\n");}
else{
	printf("\nAC not equals to AE\n");}

if( round(BC) == round(DE) ){
	printf("\nBC equals to DE\n");}
else{
	printf("\nBC not equals to DE\n");}

return 0;
}
