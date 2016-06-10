#include<iostream>

using namespace std;


class DenseMatrix {

	public:
		enum Exception {
			ERR_INVALID_SIZE, ERR_OUT_OF_MEMORY,
			ERR_INVALID_RANGE, ERR_SIZE_MISMATCH,
			ERR_SINGULAR, ERR_MUSTSQUARE
		};
	public:
		DenseMatrix(int rsize, int csize);
		~DenseMatrix();
		DenseMatrix(const DenseMatrix& m);

		const DenseMatrix& operator=(const DenseMatrix& m);

		double A(int r, int c) const; //  Read
		double& A(int r, int c); //  Write

		int GetRow() const { return m_nRow; }
		int GetCol() const { return m_nCol; }

		void Print() const;
		bool IsSquare() const { return m_nCol == m_nRow; }
		bool ExchangeRow(int r1, int r2);

		DenseMatrix operator+(const DenseMatrix& m) const;
		DenseMatrix operator-(const DenseMatrix& m) const;
		DenseMatrix operator*(const DenseMatrix& m) const;

		/*double Determinant() const;
		DenseMatrix Solve(DenseMatrix Y);
		DenseMatrix Inverse() const;*/

		DenseMatrix SubMatrix(int row,int col)const;
		DenseMatrix Strassen(const DenseMatrix& m)const;
	protected:
		double *m_pArray;
		int m_nRow;
		int m_nCol;
};

DenseMatrix::DenseMatrix(int rsize,int csize){
	m_nRow=rsize;
	m_nCol=csize;
	m_pArray=new double[m_nRow*m_nCol];
	if(m_pArray==0) throw ERR_OUT_OF_MEMORY;
	for(int i=0;i<m_nRow*m_nCol;i++) m_pArray[i]=0.0;
}
DenseMatrix::~DenseMatrix(){
	delete[]m_pArray;
}
DenseMatrix::DenseMatrix(const DenseMatrix& m){
	m_nRow=m.m_nRow;
	m_nCol=m.m_nCol;
	m_pArray=new double[m_nRow*m_nCol];
	if(m_pArray==0) throw ERR_OUT_OF_MEMORY;
	for(int i=0;i<m_nRow*m_nCol;i++) m_pArray[i]=m.m_pArray[i];
}
const DenseMatrix& DenseMatrix::operator=(const DenseMatrix& m){
	delete[] m_pArray;
	m_nRow=m.m_nRow;
	m_nCol=m.m_nCol;
	m_pArray=new double[m_nRow*m_nCol];
	if(m_pArray==0) throw ERR_OUT_OF_MEMORY;
	for(int i=0;i<m_nRow*m_nCol;i++) m_pArray[i]=m.m_pArray[i];
	return *this;
}

double DenseMatrix::A(int r,int c)const{
	if(r<0 || r>=m_nRow || c<0 || c>=m_nCol) throw ERR_INVALID_RANGE;
	return m_pArray[r*m_nCol+c];
}

double& DenseMatrix::A(int r,int c){
	if(r<0 || r>=m_nRow || c<0 || c>=m_nCol) throw ERR_INVALID_RANGE;
	return m_pArray[r*m_nCol+c];
}

DenseMatrix DenseMatrix::operator+(const DenseMatrix& m)const{
	if(m_nRow!=m.m_nRow || m_nCol!=m.m_nCol) throw ERR_SIZE_MISMATCH;
	DenseMatrix result(m_nRow,m_nCol);
	for(int r=0;r<m_nRow;r++)
		for(int c=0;c<m_nCol;c++)
			result.A(r,c)=A(r,c)+m.A(r,c);
	return result;
}

DenseMatrix DenseMatrix::operator-(const DenseMatrix& m)const{
	if(m_nRow!=m.m_nRow || m_nCol!=m.m_nCol) throw ERR_SIZE_MISMATCH;
	DenseMatrix result(m_nRow,m_nCol);
	for(int r=0;r<m_nRow;r++)
		for(int c=0;c<m_nCol;c++)
			result.A(r,c)=A(r,c)-m.A(r,c);
	return result;
}

DenseMatrix DenseMatrix::operator*(const DenseMatrix& m)const{
	if(m_nCol!=m.m_nRow) throw ERR_SIZE_MISMATCH;
	DenseMatrix result(m_nRow,m.m_nCol);
	for(int r=0;r<m_nRow;r++)
		for(int c=0;c<m.m_nCol;c++)
			for(int k=0;k<m_nCol;k++)
				result.A(r,c)+=A(r,k)*m.A(k,c);
	return result;
}

//(0,0) (0,1) (1,0) (1,1)
DenseMatrix DenseMatrix::SubMatrix(int row,int col)const{
	if(!IsSquare()) throw ERR_MUSTSQUARE;
	
	int n=GetRow()/2;
	int r=row*n;
	int c=col*n;

	DenseMatrix m(n,n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			m.A(i,j)=A(r+i,c+j);
	return m;
}

DenseMatrix DenseMatrix::Strassen(const DenseMatrix& m)const{
	if(!IsSquare() || !m.IsSquare()) throw ERR_MUSTSQUARE;
	DenseMatrix rm(GetRow(),GetCol());
	if(GetRow()>1){
		int n=GetRow()/2;
		DenseMatrix A11(n,n),A12(n,n),A21(n,n),A22(n,n);
		A11=SubMatrix(0,0);
		A12=SubMatrix(0,1);
		A21=SubMatrix(1,0);
		A22=SubMatrix(1,1);

		DenseMatrix B11(n,n),B12(n,n),B21(n,n),B22(n,n);
		B11=SubMatrix(0,0);
		B12=SubMatrix(0,1);
		B21=SubMatrix(1,0);
		B22=SubMatrix(1,1);

		DenseMatrix P(n,n),Q(n,n),R(n,n),S(n,n),T(n,n),U(n,n),V(n,n);
		P = (A11 + A22).Strassen(B11 + B22);
		Q = (A21 + A22).Strassen(B11);
		R = A11.Strassen(B12 - B22);
		S = A22.Strassen(B21 - B11);
		T = (A11 + A12).Strassen(B22);
		U = (A21 - A11).Strassen(B11 + B12);
		V = (A12 - A22).Strassen(B21 + B22);

		DenseMatrix C11(n,n),C12(n,n),C21(n,n),C22(n,n);
		C11 = P + S - T + V;
		C12 = R + T;
		C21 = Q + S;
		C22 = P + R - Q + U;

		for(int r=0;r<n;r++){
			for(int c=0;c<n;c++){
				rm.A(r,c) = C11.A(r, c);
				rm.A(r,c+n) = C12.A(r,c);
				rm.A(r+n,c) = C21.A(r, c);
				rm.A(r+n,c+n) = C22.A(r, c);
			}
		}
	}
	else rm.A(0,0)=A(0,0)*m.A(0,0);
	
	return rm;
}
