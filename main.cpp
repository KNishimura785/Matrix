#include <iostream>

#include "Matrix.h"
#include "Vector.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void prntmat( Matrix::Matrix<int> *m );
void prntmat( Matrix::Matrix<double> *m );

class M_AddOne : public Matrix::MatrixFunctor<int,int>
{
	public:
		int function(int element, unsigned int y, unsigned int x)
		{
			return element+1;
		}
};

class M_ToDub : public Matrix::MatrixFunctor<int,double>
{
	public:
		double function(int element, unsigned int y, unsigned int x)
		{
			double temp = (double)element;
			return temp + 0.5;
		}
};

int main(int argc, char** argv)
{
	int ilist[][3] = {{1,2,3},{4,5,6}};
	Matrix::Matrix<int> mat(2,3,(int*)ilist);
	prntmat(&mat);
	M_AddOne *f = new M_AddOne;
	std::cout<<f->function(1,1,1)<<'\n';
	Matrix::Matrix<int> mat2 = mat.Apply(f);
	prntmat(&mat2);
	M_ToDub * f2 = new M_ToDub;
	Matrix::Matrix<double> mat3 = mat.Apply(f2);
	prntmat(&mat3);
	delete f, f2;
	/*int ilist2 [] = {1,2,3};
	int ilist3 [] = {-1,3,7};
	Vector::Vector<int> v1(3,ilist2);
	Vector::Vector<int> v2(3,ilist3);
	Vector::Vector<int> cross = v1.CrossP(v2);
	prntmat(&cross);
	/*Matrix::Matrix<int> mat(2,3,1);
	Matrix::Matrix<int> mat2(3,2,1);
	mat(1,2)=2; mat(1,3)=3; mat(2,1)=4; mat(2,2)=5; mat(2,3)=6;
	mat2(1,2)=2; mat2(2,1)=3; mat2(2,2)=4; mat2(3,1)=5; mat2(3,2)=6;
	Matrix::Matrix<int> product = mat * mat2;
	Matrix::Matrix<int> matt = mat.Transpose();
	std::cout<<"Matrix 1:\n";
	prntmat( &mat );
	std::cout<<"\nMatrix 2:\n";
	prntmat( &mat2 );
	std::cout<<"\nMatrix1*Matrix 2:\n";
	prntmat( &product );
	std::cout<<"\nMatrix 1 Transpose:\n";
	prntmat( &matt );
	Matrix::Matrix<int> combined=mat2.vConcat(matt);
	std::cout<<"\nMatrix 2 vConcat with M1 Transpose:\n";
	prntmat(&combined);
	Matrix::Matrix<int> hcombined=mat2.hConcat(matt);
	std::cout<<"\nMatrix 2 hConcat with M1 Transpose:\n";
	prntmat(&hcombined);*/
	return 0;
}

void prntmat( Matrix::Matrix<int> *m )
{
	std::cout<<'[';
	for(unsigned int i=0;i<m->dy;i++)
	{
		for(unsigned int j=0;j<m->dx;j++)
		{
			std::cout<<m->data[j+i*m->dx];
			if(j!=m->dx-1)
				std::cout<<'\t';
		}
		if(i!=m->dy-1)
			std::cout<<'\n';
	}
	std::cout<<']'<<'\n';
}

void prntmat( Matrix::Matrix<double> *m )
{
	std::cout<<'[';
	for(unsigned int i=0;i<m->dy;i++)
	{
		for(unsigned int j=0;j<m->dx;j++)
		{
			std::cout<<m->data[j+i*m->dx];
			if(j!=m->dx-1)
				std::cout<<'\t';
		}
		if(i!=m->dy-1)
			std::cout<<'\n';
	}
	std::cout<<']'<<'\n';
}
