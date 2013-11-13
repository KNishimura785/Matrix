#ifndef NMATRIX_H
#define NMATRIX_H

namespace Matrix
{
	template <class T, class V>
	class MatrixFunctor
	{
		public:
			virtual V function(T, unsigned int, unsigned int)
			{ return V(0); }
	};
	
	template <class T>
	class Matrix
	{
		public:
			unsigned int dy,dx;
			T* data;
			Matrix();
			Matrix(const Matrix<T>& other);
			Matrix<T>& operator=(const Matrix<T>& other);
			Matrix(unsigned int, unsigned int);
			Matrix(unsigned int, unsigned int, T);
			Matrix(unsigned int, unsigned int, T*);
			~Matrix();
			
			bool inBounds( unsigned int y, unsigned int x )
			{ return (y>0&&y<=dy&&x>0&&x<=dx); }
			T* GetElementAddr(unsigned int y, unsigned int x)
			{ return &data[(y-1)*dx+(x-1)]; }
			void Set(unsigned int y, unsigned int x, T d)
			{ if(inBounds(y,x)) (*GetElementAddr(y,x))=d; }
			T Get(unsigned int y, unsigned int x)
			{if(inBounds(y,x)) return (*GetElementAddr(y,x));
			return T(0); }
			static Matrix<T> Identity(unsigned int);
			Matrix<T> Transpose();
			Matrix<T> SubMatrix(unsigned int, unsigned int, unsigned int, unsigned int);
			
			template <class V>
			Matrix<V> Apply(MatrixFunctor<T,V>*);
			
			T& operator()(unsigned int, unsigned int);
			Matrix<T> vConcat(Matrix<T>&);
			Matrix<T> hConcat(Matrix<T>&);
	};
	
	template <class T>
	Matrix<T>::Matrix() : Matrix(1,1)
	{
	}
	
	template <class T>
	Matrix<T>::Matrix(const Matrix<T> &m) : dy(m.dy), dx(m.dx)
	{
		data = (T*) 0;
		data = new T [dy*dx];
		for(unsigned int i=0; i<dy*dx;i++)
			data [i] = m.data[i];
	}
	
	template <class T>
	Matrix<T>& Matrix<T>::operator=( const Matrix<T>& m )
	{
		if( &m == this )
			return *this;
		if( dy != m.dy || dx != m.dx )
		{
			if(data)
				delete [] data;
			dy = m.dy;
			dx = m.dx;
			data = new T [dy*dx];
		}
		for(unsigned int i=0; i<dy*dx;i++)
			data [i] = m.data[i];
		return *this;
	}
	
	template <class T>
	Matrix<T>::Matrix( unsigned int y, unsigned int x) : dy(y), dx(x)
	{
		data = new T [dy*dx];
		for(unsigned int i=0; i<dy*dx;i++)
			data [i] = T(0);
	}
	
	template <class T>
	Matrix<T>::Matrix( unsigned int y, unsigned int x, T d) : dy(y), dx(x)
	{
		data = new T [dy*dx];
		for(unsigned int i=0; i<dy*dx;i++)
			data [i] = d;
	}
	
	template <class T>
	Matrix<T>::Matrix( unsigned int y, unsigned int x, T* d ) : dy(y), dx(x)
	{
		data = new T [dy*dx];
		for(unsigned int i=0; i<dy*dx;i++)
			data [i] = d[i];
	}
	
	template <class T>
	Matrix<T>::~Matrix()
	{
		if( data )
			delete [] data;
	}
	
	template <class T>
	Matrix<T> Matrix<T>::Identity(unsigned int N)
	{
		Matrix<T> result(N,N);
		for(int i=1;i<=N;i++)
			result.Set(i,i,T(1));
		return result;
	}
	
	template <class T>
	Matrix<T> Matrix<T>::Transpose()
	{
		Matrix<T> mat(dx,dy);
		for( unsigned int j=1; j<=dy; j++ )
		{
			for( unsigned int i=1; i<=dx; i++ )
			{
				mat.Set(i,j,Get(j,i));
			}
		}
		return mat;
	}
	
	template <class T>
	Matrix<T> Matrix<T>::SubMatrix(unsigned int y1, unsigned int x1, unsigned int y2, unsigned int x2)
	{
		Matrix<T> mat(y2-y1+1,x2-x1+1);
		unsigned int y,x;
		y=1;
		for( unsigned int j=y1; j<=y2; j++ )
		{
			x=1;
			for( unsigned int i=x1; i<=x2; i++ )
			{
				mat.Set(y,x,Get(j,i));
				x++;
			}
			y++;
		}
		return mat;
	}
	
	template <class T>
	T& Matrix<T>::operator()(unsigned int y, unsigned int x)
	{
		if( inBounds(y,x) )
			return data[(x-1)+(y-1)*dx];
		return data[0];
	}
	
	template <class T>
	template <class V>
	Matrix<V> Matrix<T>::Apply( MatrixFunctor<T,V> *obj )
	{
		Matrix<V> product(dy,dx);
		for( unsigned int j=0;j<dy;j++)
		{
			for( unsigned int i=0; i<dx;i++)
			{
				product.data[i+j*dx]=obj->function(data[i+j*dx],j,i);
			}
		}
		return product;
	}
	
	template <class T>
	Matrix<T> Matrix<T>::vConcat(Matrix<T>& m)
	{
		if(dx!=m.dx)
			return *this;
		Matrix<T> result(dy+m.dy,dx);
		for( int i=0;i<dy*dx;i++)
			result.data[i]=data[i];
		unsigned int p = dy*dx;
		for( int i=0;i<m.dy*m.dx;i++)
		{
			result.data[p]=m.data[i];
			p++;
		}
		return result;
	}
	
	template <class T>
	Matrix<T> Matrix<T>::hConcat(Matrix<T>& m)
	{
		if(dy!=m.dy)
			return *this;
		Matrix<T> result(dy,dx+m.dx);
		for(int j=0;j<dy;j++)
		{
			for(int i=0;i<dx;i++)
				result.data[i+j*(dx+m.dx)]=data[i+j*dx];
			for(int i=0;i<m.dx;i++)
				result.data[i+dx+j*(dx+m.dx)]=m.data[i+j*dx];
		}
		return result;
	}
	
	template <class T>
	Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
	{
		if( lhs.dy!=rhs.dy || lhs.dx!=rhs.dx )
			return Matrix<T>();
		Matrix<T> result(lhs.dy,lhs.dx);
		for(unsigned int i=0; i<lhs.dy*lhs.dx;i++)
			result.data[i] = lhs.data[i]+rhs.data[i];
		return result;
	}
	
	template <class T>
	Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
	{
		if( lhs.dy!=rhs.dy || lhs.dx!=rhs.dx )
			return Matrix<T>();
		Matrix<T> result(lhs.dy,lhs.dx);
		for(unsigned int i=0; i<lhs.dy*lhs.dx;i++)
			result.data[i] = lhs.data[i]-rhs.data[i];
		return result;
	}
	
	template <class T>
	Matrix<T> operator*(Matrix<T> &lhs, Matrix<T> &rhs)
	{
		if( lhs.dx != rhs.dy )
			return Matrix<T>();
		Matrix<T> product(lhs.dy,rhs.dx);
		T tempsum;
		for( unsigned int j=1;j<=lhs.dy;j++)
		{
			for( unsigned int i=1; i<=rhs.dx;i++)
			{
				tempsum = T(0);
				for( unsigned int k=1;k<=lhs.dx;k++)
					tempsum=tempsum+lhs.Get(j,k)*rhs.Get(k,i);
				product.Set(j,i,tempsum);
			}
		}
		return product;
	}
	
	template <class T, class V>
	Matrix<T> operator*(V p, Matrix<T> &rhs)
	{
		Matrix<T> product(rhs.dy,rhs.dx);
		for( unsigned int j=0;j<rhs.dy;j++)
		{
			for( unsigned int i=0; i<rhs.dx;i++)
			{
				product.data[i+j*product.dx]=rhs.data[i+j*product.dx]*p;
			}
		}
		return product;
	}
};


#endif
