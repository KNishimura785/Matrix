#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"

namespace Vector
{
	template <class T>
	class Vector : public Matrix::Matrix<T>
	{
		public:
			Vector();
			Vector( unsigned int );
			Vector( unsigned int, T* );
			Vector( Matrix::Matrix<T>& );
			Matrix::Matrix<T> ToSkewSymmetric();
			T DotP(Vector<T>&);
			Vector<T> CrossP(Vector<T>&);
	};

	template <class T>
	Vector<T>::Vector()
	{}
	template <class T>
	Vector<T>::Vector(unsigned int y) : Matrix::Matrix<T>(y,1)
	{}
	template <class T>
	Vector<T>::Vector(unsigned int y, T* d) : Matrix::Matrix<T>(y,1,d)
	{}
	template <class T>
	Vector<T>::Vector(Matrix::Matrix<T>& m) : Matrix::Matrix<T>(m.dy,1)
	{
		for(int i=1;i<=m.dy;i++)
			Matrix::Matrix<T>::Set(i,1,m(i,1));
	}
	template <class T>
	Matrix::Matrix<T> Vector<T>::ToSkewSymmetric()
	{
		if(Matrix::Matrix<T>::dy!=3)
			return Matrix::Matrix<T>();
		Matrix::Matrix<T> result(3,3);
		result(3,2)=Matrix::Matrix<T>::data[0];
		result(2,3)=-1*Matrix::Matrix<T>::data[0];
		result(1,3)=Matrix::Matrix<T>::data[1];
		result(3,1)=-1*Matrix::Matrix<T>::data[1];
		result(2,1)=Matrix::Matrix<T>::data[2];
		result(1,2)=-1*Matrix::Matrix<T>::data[2];
		return result;
	}
	template <class T>
	T Vector<T>::DotP(Vector<T> &v)
	{
		unsigned int min = Matrix::Matrix<T>::dy<v.dy ? Matrix::Matrix<T>::dy : v.dy;
		T sum = T(0);
		for( unsigned int i=0;i<min;i++)
			sum = sum + Matrix::Matrix<T>::data[i] * v.data[i];
		return sum;
	}
	template <class T>
	Vector<T> Vector<T>::CrossP( Vector<T> &v )
	{
		Matrix::Matrix<T> uhat = ToSkewSymmetric();
		Matrix::Matrix<T> temp = uhat*v;
		return Vector<T>(temp);
	}
};

#endif
