#ifndef MATRICES_STRING_VECTOR_HEADER
#define MATRICES_STRING_VECTOR_HEADER

#include <vector>   //vector
#include <string>   //string

using namespace std;

template<typename T>
class Matrix
{
public:
	Matrix();
	Matrix(vector<string> labels);
	Matrix(vector<T> values, vector<string> labels);
	Matrix(T value, vector<string> labels);
	
	void Assign(vector<string> labels);
	void Assign(vector<T> values, vector<string> labels);
	void Assign(T value, vector<string> labels);
	
	T& operator[](string label);
	T& operator[](int index);
	Matrix<T>& operator=(const Matrix<T>& matrix);
	
private:
	vector<string> labels;
	vector<T> values;

	int GetIndexOfLabel(string label);
	void Allocate(int size);
};

typedef Matrix<double>   Matrix1D;
typedef Matrix<Matrix1D> Matrix2D;
typedef Matrix<Matrix2D> Matrix3D;

#define MATRIX1D(X, X_LABELS) (Matrix1D(X, X_LABELS))
#define MATRIX2D(X, Y, X_LABELS, Y_LABELS) (Matrix2D(X, MATRIX1D(Y, Y_LABELS), X_LABELS))
#define MATRIX3D(X, Y, Z, X_LABELS, Y_LABELS, Z_LABELS) (Matrix3D(X, MATRIX2D(Y, Z, Y_LABELS, Z_LABELS), X_LABELS))

template<typename T>
Matrix<T>::Matrix()
{

}
template<typename T>
Matrix<T>::Matrix(vector<string> labels)
{
	Assign(labels);
}
template<typename T>
Matrix<T>::Matrix(vector<T> values, vector<string> labels)
{
	Assign(values, labels);
}
template<typename T>
Matrix<T>::Matrix(T value, vector<string> labels)
{
	Assign(value, labels);
}

template<typename T>
void Matrix<T>::Assign(vector<string> labels)
{
	Allocate((int)labels.size());

	for (int i = 0; i < (int)labels.size(); i++)
		this->labels[i] = labels[i];
}
template<typename T>
void Matrix<T>::Assign(vector<T> values, vector<string> labels)
{
	Assign(labels);

	for (int i = 0; i < (int)values.size(); i++)
		this->values[i] = values[i];
}
template<typename T>
void Matrix<T>::Assign(T value, vector<string> labels)
{
	Assign(labels);

	for (int i = 0; i < (int)labels.size(); i++)
		this->values[i] = value;
}

template<typename T>
T& Matrix<T>::operator[] (string label)
{
	return operator[](GetIndexOfLabel(label));
}
template<typename T>
T& Matrix<T>::operator[] (int index)
{
	if (index >= 0 && index < (int)values.size())
		return values[index];
	else
		throw;
}
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
{
	Allocate((int)matrix.labels.size());

	for (int i = 0; i < (int)labels.size(); i++)
	{
		labels[i] = matrix.labels[i];
		values[i] = matrix.values[i];
	}

	return *this;
}

template<typename T>
int Matrix<T>::GetIndexOfLabel(string label)
{
	for (int i = 0; i < (int)labels.size(); i++)
		if (labels[i] == label)
			return i;

	return -1;
}

template<typename T>
void Matrix<T>::Allocate(int size)
{
	values = vector<T>(size);
	labels = vector<string>(size);
}

#endif
