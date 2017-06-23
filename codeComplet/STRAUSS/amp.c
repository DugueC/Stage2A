#include "amp.h"
#include <iostream>

using namespace std;


AuxiliaryModelPrior ::  AuxiliaryModelPrior( Prior *cp, Sampler *ca, dvector *cvalInit, dvector *cminVal, dvector *cmaxVal, dvector *cdy, int ctime_theta, dvector *cdelta)
{
 this->prior=cp;
 this->algo=ca;

 size=cdy->getSize();

 theta.setVector(size);
 minVal.setVector(size);
 maxVal.setVector(size);
 delta.setVector(size);
 dy.setVector(size);
 theta.init(cvalInit);
 minVal.init(cminVal);
 maxVal.init(cmaxVal);
 delta.init(cdelta);
 dy.init(cdy);
 
 time_theta=ctime_theta;

 // initialize auxiliary variables ...
 dx.setVector(size);
 dx.initZeros();

}

void AuxiliaryModelPrior :: proposeTheta()
{
  // choose a random component
  int pos=whran.discrete_uniform(0,size-1);

  double step,max_val,min_val,theta_val;
  
  step=delta.getVal(pos)*(whran.uniform()-0.5);
  theta_val=theta.getVal(pos)+step;
  max_val=maxVal.getVal(pos);
  min_val=minVal.getVal(pos);

  if(theta_val>max_val)
	    theta_val=theta.getVal(pos);
  if(theta_val<min_val)
	    theta_val=theta.getVal(pos);

  theta.setVal(pos,theta_val);
}


void AuxiliaryModelPrior :: proposeAuxiliar()
{
  algo->sim(x);
  setDataX(x);
}


void AuxiliaryModelPrior :: metropolisWalk()
{
 double u,alpha,p_y_ratio,q_ratio;
 dvector temp_theta(size),temp_dx(size);
 Pattern temp_x;

 for(int i=0;i<time_theta;i++)
  {
   temp_theta.init(&theta);
   temp_dx.init(&dx);
 
   proposeTheta();
 
   p_y_ratio=computeRatioDensity(&dy,&theta,&temp_theta);
   q_ratio=computeRatioProposalDensity(&temp_dx,&temp_theta,&dx,&theta);
   alpha=p_y_ratio*q_ratio;

   u=whran.uniform();
   if( u > alpha)
   	{
     	 theta.init(&temp_theta);
         dx.init(&temp_dx);
         }
  }
}


double AuxiliaryModelPrior :: computeRatioDensity(dvector *data, dvector *theta_final, dvector *theta_initial)
{
 int i;
 
 dvector temp(size);
 temp.init(theta_final);
 temp.substract(theta_initial);

 return exp(data->scalarProduct(&temp));

}
double AuxiliaryModelPrior :: computeRatioProposalDensity(dvector *data_n, dvector *theta_n, dvector *data_o, dvector *theta_o)
{
  double p1,p2;

  p1=data_n->scalarProduct(theta_n);
  p2=data_o->scalarProduct(theta_o);
 
  return exp(p1-p2);

}
   
void AuxiliaryModelPrior :: printTheta( char *name_file)
{
   ofstream out_stream;
   out_stream.open(name_file, ofstream::out | ofstream::app);
   if( out_stream.fail() )
   	{
	 cout << "ERROR : opening file in printTheta() ";
      	 cout << name_file << " \n";
	 exit(1);
	}

   double val;
   for(int i=0;i<size;i++)
   	{
      	 val=theta.getVal(i);
         out_stream<<val<<" ";
        }

   out_stream<<endl;
   out_stream.close();
}



void AuxiliaryModelPrior :: report()
{
 cout<<"AuxiliaryModelPrior class for parameter estimation ...\n";

 cout<<"Model ...\n";
 prior->report();


 cout<<"Data Y :\n";
 dy.printVector();

 cout<<"Data X :\n";
 dx.printVector();

 cout<<"Theta ... \n";
 theta.printVector();

 cout<<"Min Values ...\n";
 minVal.printVector();

 cout<<"Max Values ...\n";
 maxVal.printVector();

 cout<<"Delta Values ...\n";
 delta.printVector(); 
}







