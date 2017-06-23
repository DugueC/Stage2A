//
// Le fichier vec_cl.h contient la definition
// de la classe VECTOR.
//
// C'est un VECTOR d'entiers de dimensions : [0 ... N-1].
//
#ifndef _matcl_
#define _matcl_ 1

class dvector
{
	private :
   	double *pointer;
		int length_vector;
		void dvct(int lvect);

	public :
		dvector(){ dvct(0); };
		dvector(int lvect){ dvct(lvect); };
      ~dvector(void){ delete [] pointer;};
      void clean(){ delete [] pointer; };

      void setVector(int lvect) { dvct(lvect); };
      int getSize(){ return length_vector; };
      double getVal(int pos);
      void  setVal(int pos, double val);

      void printVector();
      void printPositiveValues();
      int  countPositiveValues();

      double sum();
      void multiplyScalar(double val);
      double scalarProduct(dvector *v);
      void add(dvector *v);
      void substract(dvector *v);
      void init(dvector *v);
      void initZeros();
      void norm();
      double computeNorm();

      void logVector(dvector *lv);
};



//
// La classe D_MATRIX est construite a l'aide de
// de la classe D_VECTOR. Une matrice est un tableau de vecteurs.
// Un vecteur represente une ligne.
//
class dmatrix
{
	private :
	int nrows,ncols;
	dvector *pointer;

	void dmat(int,int);

	public :
        dmatrix(){ dmat(0,0); };
	dmatrix(int number_rows,int number_cols)
	{
	 dmat(number_rows,number_cols);
	}
	~dmatrix()
		{
		  //cout<<"Destructor D_MATRIX \n";
		 delete [] pointer;
		};

         void setMatrix(int nr, int nc) { dmat(nr,nc); };
	 void initZeros();
	 int getRows() const {return  nrows;};
	 int getCols() const {return ncols;} ;
	 double getVal(int row, int col) const;
	 void  setVal(int row,int col, double val);

	 void saveMatrix(char *name_file) const;

	 void getMat(dmatrix *mat);

};

// endif _event_
#endif
