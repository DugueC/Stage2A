//
// Le fichier vec_cl.cpp contient les
// methodes de la classe VECTOR, D_VECTOR et D_MATRIX.
// Le fichier contient egalement un test Kolmogorov-Smirnov,
// sur les  donnes contenues dans des vecteurs D_VECTOR.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>

#include "matcl.h"

using namespace std;


//
// Classe D_VECTOR
//
void dvector :: dvct (int lvect)
{
	int i;

	//cout<<"Constructor D_VECTOR \n";

	length_vector=lvect;
	pointer=new double[lvect];

	if (pointer==NULL)
		{
		 cout<< "\n ERREUR : dans l'allocation du D_VECTOR ! \n";
		 exit(1);
		}

	// initialisation du vecteur;
	for(i=0;i<lvect;i++)
		pointer[i]=0.0;
}


void dvector :: printVector(void)
{
	int i;

	for(i=0;i<length_vector;i++)
	  //cout<<"\n" <<i<<"=>"<<pointer[i];
	  printf("%f\n",pointer[i]);

}
int dvector :: countPositiveValues()
{
	int sum=0;

	for(int i=0;i<length_vector;i++)
   	if (pointer[i]>0.0) sum++;

   return sum;
}
void dvector :: printPositiveValues()
{
	int i;

	for(i=0;i<length_vector;i++)
   	if (pointer[i]>0.0) cout<<pointer[i]<<"\n";

}
double dvector :: getVal(int pos)
{
	int condition;

	condition=( pos >= 0 ) && ( pos<length_vector );

	if (condition)
		{
			return pointer[pos];
		}
	else
		{
			cout <<"ERREUR : GetVal dans D_VECTOR !!!\n";
			cout <<"Longueur vecteur : "<<length_vector<<"\n";
			cout <<"... position : "<<pos<<".\n";exit(1);
		};
}

void dvector :: setVal(int pos, double val)
{
	int condition;

	condition=( pos>=0 ) && ( pos<length_vector );

	if (condition)
			pointer[pos]=val;
	else
		{
			cout <<"ERREUR : SetVal dans D_VECTOR !!!\n";
			cout <<"Longueur vecteur : "<<length_vector<<"\n";
			cout <<"... position : "<<pos<<".\n";
			exit(1);
		}
}

double dvector :: sum()
{
 int j;
 double s=0.0;

 for(j=0;j<length_vector;j++) s+=getVal(j);

 return s;
}


void dvector :: multiplyScalar(double val)
{
	int i;
   double temp;

	for(i=0;i<length_vector;i++)
		{
         temp=val*getVal(i);
         setVal(i,temp);
		}

}

double dvector :: computeNorm()
{
  	int i;
   double temp=0.0,val,tol=1e-25;

	for(i=0;i<length_vector;i++)
		{
        val=getVal(i);
        temp+=val*val;;
		}
   /*if (temp<=tol)
	  {
	   cout<<"ERROR :  computeNorm() in DVECTOR() \n";
      exit(1);
     }*/

   return sqrt(temp);
   
}

void dvector :: logVector(dvector *lv)
{
	double val;
   int i;

	for(i=0;i<length_vector;i++)
		{
        val=getVal(i);
        if(val > 0)
        	 lv->setVal(i,log(val));
        else
        	{
          cout<<"ERROR : logVector() in DVECTOR() \n";
          cout<<val<<"\n";
          cout<<i<<"\n";
          exit(1);
         }

		}
}



void dvector :: norm()
{
	double temp=computeNorm();
   multiplyScalar(1.0/temp);

}
double dvector :: scalarProduct(dvector *v)
{
   int i;
   double temp=0.0,val;
   if (getSize()==v->getSize())
		for(i=0;i<length_vector;i++)
		{
		       val=getVal(i)*v->getVal(i);
		       temp+=val;
		}
   else
	  {
	   cout<<"ERROR : scalarProduct() in DVECTOR() \n";
           exit(1);
          }

   return temp;

}

void dvector :: add(dvector *v)
{
 int i,l_v=v->getSize();
 double temp;

 if(l_v!=length_vector)
 	{
 	 cout <<"ERROR : add() in DVECTOR !!!\n";
  	 exit(1);
 	}
 else
  for(i=0;i<length_vector;i++)
  	{
  	 temp=getVal(i)+v->getVal(i);
          setVal(i,temp);
  	}
}
void dvector :: substract(dvector *v)
{
 int i,l_v=v->getSize();
 double temp;

 if(l_v!=length_vector)
 	{
  		cout <<"ERROR : substract() in DVECTOR !!!\n";
      cout<<l_v<<"\n";
      cout<<length_vector<<"\n";
  		exit(1);
 	}
 else
  for(i=0;i<length_vector;i++)
  	{
   	temp=getVal(i) - v->getVal(i);
   	setVal(i,temp);
  	}
}

void dvector :: init(dvector *v)
{
 int i,l_v=v->getSize();
 double temp;

 if(l_v!=length_vector)
 	{
  		cout <<"ERROR : init() in DVECTOR !!!\n";
  		exit(1);
 	}
 else
 	for(i=0;i<length_vector;i++)
  			{
   			temp=v->getVal(i);
   			setVal(i,temp);
  			}
}

void dvector :: initZeros()
{
	int i;

   for(i=0;i<length_vector;i++) pointer[i]=0.0;
}




///////////////////////////////////////////////////////////////
//
// La classe DMATRIX
//
///////////////////////////////////////////////////////////////
void dmatrix :: dmat(int number_rows, int number_cols)
{
 int i;

 nrows=number_rows;
 ncols=number_cols;

 pointer=new dvector[nrows];

 if (pointer==NULL)
	{
	 cout<<"ERREUR : dans l'allocation D_MATRIX ! \n";
	 exit(1);
	}

 for (i=0;i<nrows;i++)
	pointer[i].setVector(ncols);

 //cout<<"Constructor D_MATRIX \n";
}

void dmatrix :: initZeros()
{
 int i,j;

 for(i=0;i<nrows;i++)
	for(j=0;j<ncols;j++)
		setVal(i,j,0.0);
}

double dmatrix :: getVal(int row,int col) const
{
       int condition;

	condition=(row>=0)&&(row<nrows)&&(col>=0)&&(col<ncols);

	if (condition)
		{
			return pointer[row].getVal(col);
		}
	else
		{
			cout <<"ERREUR : getVal() dans DMATRIX !!!\n";
			exit(1);
		}
}

void dmatrix :: setVal(int row,int col,double val)
{
	int condition;

	condition=(row>=0)&&(row<nrows)&&(col>=0)&&(col<ncols);

	if (condition)
			pointer[row].setVal(col,val);
	else
	{
	  cout<<"ERREUR : setVal() dans DMATRIX !!!\n" ;
	  cout<<row<<" : "<<col<<"\n";
	  exit(1);
	}
}

void dmatrix :: saveMatrix(char *name_file) const
{
   FILE *data_file;

   if( (data_file=fopen(name_file,"wt")) == NULL ) {
         cout << "ERROR DMATRIX : opening file in saveMatrix() ";
         cout << name_file <<" n";
         exit(1);
      }

   fprintf(data_file,"%d\n",getRows());
   fprintf(data_file,"%d\n",getCols());

   float val;

   for(int i=0 ; i <  getRows() ; i++)
   	for(int j= 0 ; j < getCols() ; j++ )
		{
		 val = getVal(i,j);
		 fprintf(data_file,"%d %d %5.2f\n",i,j,val);
		}

   fclose(data_file);

}

void dmatrix :: getMat(dmatrix *mat)
{
 if ( (getRows() != mat->getRows()) || (getCols() != mat->getCols()) )
	{
         cout<<"ERROR : DMATRIX initMat() - dimension matching !!!\n";
	 exit(1);
	}

 int i,j;
 float val;

 for(i=0;i<nrows;i++)
	for(j=0;j<ncols;j++)
		{
		  val=getVal(i,j);
		  mat->setVal(i,j,val);
		}
}



