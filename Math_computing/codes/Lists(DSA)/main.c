#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libs/listgen.h"
#include "libs/listfun.h"

int  main()
{
avyuh *A,*B,*C,*D,*E,*vert;
double l=6; //lengths of a side 
int m =2,n=1,k=3; //(mxn) matrices
double CMA,BMD,DBC,BCA; //angles 
double BD,CD, AB,AD,AC,CE,AE,BC,DE;
double theta, Alpha, Beta, Beta1;

//load matrix from file
vert = loadList("vertices.dat",m,k);

printList(vert);
//Triangle vertices
B = Listcol(vert,0);
D = Listcol(vert,1);
C = Listcol(vert,2);


//printing the lists
//printList(vert);
//printList(B);
//printList(C);
//printList(D);

BD = Listnorm(Listsub(B,D));
CD = Listnorm(Listsub(C,D));

//printf("\nBD=%lf \n CD= %lf",BD,CD);

theta = 60;
Alpha = (180- theta)/2;

AB = BD * (sin(Alpha*(M_PI/180))/ sin(theta *(M_PI/180)));

//printf("\nAB= %lf\n",AB);

A = Mat_1(B, AB, Alpha*(M_PI/180),1);
printf("\nA\n");
printList(A);

AD = Listnorm(Listsub(A,D));
AC = Listnorm(Listsub(A,C));

//printf("\nAD=%lf \n AC= %lf",AD,AC);

Beta1 = (180/M_PI)*acos((AC*AC + CD*CD - AD*AD )/(2* AC* CD));
//printf("\nBeta1 = %lf\n",Beta1);

CE = AC * (sin(theta*(M_PI/180)) / sin(Alpha*(M_PI/180)));
//printf("\n CE =%lf",CE);

Beta = Alpha + Beta1;
//printf("Beta= %lf",Beta);

E = Mat_1( C, CE, Beta*(M_PI/180), -1);
printf("\nE\n");
printList(E);

AE = Listnorm(Listsub(A,E));
BC = Listnorm(Listsub(B,C));
DE = Listnorm(Listsub(D,E));

if( round(AB) == round(AD) )
	printf("\nAD equals to AB\n");
else
	printf("\nAD not equals to AB\n");

if( round(AC) == round(AE) )
	printf("\nAC equals to AE\n");
else
	printf("\nAC not equals to AE\n");

if( round(BC) == round(DE) )
	printf("\nBC equals to DE\n");
else
	printf("\nBC not equals to DE\n");

return 0;
}
