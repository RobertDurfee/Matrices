# Matrices
C++ matrix class for accessing elements by name rather than index.

### Disclaimer

This is not production-worthy code! View this simply as a proof-of-concept.

### Initialization
```C++
Matrix();

Matrix(vector<string> labels);
Matrix(int size, char ** labels);

Matrix(vector<string> labels, vector<T> values);
Matrix(int size, char ** labels, T * values);

Matrix(vector<string> labels, T value);
Matrix(int size, char ** labels, T value);
```
A `Matrix` can be initialized several different ways:

1. Without parameters which will require `Assign` later on.
2. With labels only which, depending on the type, will require `Assign` later on.
3. With labels and values.
4. With labels and a single value which will be copied to each element.

Two headers are provided utilizing a vector of strings or a pointer to a pointer of charaters as labels to facilitate different applications and avoid converting types.

### Assigning
```C++
void Assign(vector<string> labels);
void Assign(int size, char ** labels);
  
void Assign(vector<string> labels, vector<T> values);
void Assign(int size, char ** labels, T * values);
  
void Assign(vector<string> labels, T value);
void Assign(int size, char ** labels, T value);
```
`Assign` methods provide the same functions as the constructors to allow alteration of the `Matrix` without declaring a new instance. Each time an `Assign` method is called, all the data in a `Matrix` will be deleted and new space will be allocated.

### Accessing by Label
```C++
T& operator[](string label);
T& operator[](char * label);
```
The purpose of creating this structure was to allow access to elements through a label rather than maintaining two different structres, one containing labels and the other containing values. As a result, the `operator[]` method allows a label to be passed as an index. The label is identified in the structure and the value it corresponds to is passed as output. This output can be read from or written to.

### Accessing by Index
```C++
T& operator[](int index);
```
This method will perform exactly as expected allowing access to values through regular indices. 

### Equating
```C++
Matrix<T>& operator=(const Matrix<T>& matrix);
```
The `operator=` method will allow a `Matrix` to become equal to another by first clearing the modified `Matrix` and allocating appropriate space and then copying each value and label to the new `Matrix`.

### Deinitialization
```C++
~Matrix()
```
A deconstructor is only needed for the pointer to a pointer of characters implementation as the vector of strings implementation uses RAII. In this destructor, all allocated memory used by the `Matrix` is freed.

### Typedefs
```C++
typedef Matrix<double> Matrix1D;
typedef Matrix<Matrix1D> Matrix2D;
typedef Matrix<Matrix2D> Matrix3D;
```
For convenience, three typedefs are provided. Since the `Matrix` class is generic, the class can become recursive. As a result, a 3-dimensional `Matrix` can be declared by typing `Matrix<Matrix<Matrix<double>>>`. This is a little ugly and can become annoying to type each time, therefore these typedefs are provided to simplify declarations.

### Macros
```C++
#define MATRIX1D(X_LABELS) (Matrix1D(X_LABELS))
#define MATRIX2D(X_LABELS, Y_LABELS) (Matrix2D(X_LABELS, MATRIX1D(Y_LABELS)))
#define MATRIX3D(X_LABELS, Y_LABELS, Z_LABELS) (Matrix3D(X_LABELS, MATRIX2D(Y_LABELS, Z_LABELS)))

#define MATRIX1D(X, X_LABELS) (Matrix1D(X, X_LABELS))
#define MATRIX2D(X, Y, X_LABELS, Y_LABELS) (Matrix2D(X, X_LABELS, MATRIX1D(Y, Y_LABELS)))
#define MATRIX3D(X, Y, Z, X_LABELS, Y_LABELS, Z_LABELS) (Matrix3D(X, X_LABELS, MATRIX2D(Y, Z, Y_LABELS, Z_LABELS)))
```
For additional convenience, three macros are provided. Since the `Matrix` class is generic, the class can become recursive. As a result, a 3-dimensional `Matrix` can be defined by typing `Matrix<Matrix<Matrix<double>>>(x, Matrix<Matrix<double>>(y, Matrix<double>(z, zLabels), yLabels), xLabels)`. This is incredibly ugly, confusing, and very annoying to type each time, therefore these macros are provided to simplify definitions.

### Example
```C++
#include "Matrices-StringVector.h"

int main()
{
	vector<string> shirts = { "T-Shirt", "Sweater", "Sweatshirt", "Coat", "Hoodie" };
	Matrix1D shirtsPreferences = MATRIX1D(shirts);

	shirtsPreferences["T-Shirt"] = 0.1;
	shirtsPreferences["Sweater"] = 0.3;
	shirtsPreferences["Sweatshirt"] = 0.3;
	shirtsPreferences["Coat"] = 0.2;
	shirtsPreferences["Hoodie"] = 0.1;

	vector<string> pants = { "Khakis", "Joggers", "Sweatpants", "Jeans" };
	Matrix<Matrix<double>> shirtsPantsPreferences = Matrix<Matrix<double>>(shirts, Matrix<double>(pants));

	shirtsPantsPreferences["T-Shirt"]["Khakis"] = 0.1;
	shirtsPantsPreferences["T-Shirt"]["Joggers"] = 0.1;
	shirtsPantsPreferences["T-Shirt"]["Sweatpants"] = 0.5;
	shirtsPantsPreferences["T-Shirt"]["Jeans"] = 0.3;

	vector<string> socks = { "Plain", "Striped", "Argyle" };
	Matrix3D shirtsPantsSocksPreferences = MATRIX3D(shirts, pants, socks);

	shirtsPantsSocksPreferences["T-Shirt"]["Khakis"]["Plain"] = 0.2;
	shirtsPantsSocksPreferences["T-Shirt"]["Khakis"]["Striped"] = 0.4;
	shirtsPantsSocksPreferences["T-Shirt"]["Khakis"]["Argyle"] = 0.4;

	shirtsPantsSocksPreferences["T-Shirt"]["Joggers"]["Plain"] = 0.1;
	shirtsPantsSocksPreferences["T-Shirt"]["Joggers"]["Striped"] = 0.2;
	shirtsPantsSocksPreferences["T-Shirt"]["Joggers"]["Argyle"] = 0.7;

	shirtsPantsSocksPreferences["T-Shirt"]["Sweatpants"]["Plain"] = 1.0;
	shirtsPantsSocksPreferences["T-Shirt"]["Sweatpants"]["Striped"] = 0.0;
	shirtsPantsSocksPreferences["T-Shirt"]["Sweatpants"]["Argyle"] = 0.0;

	shirtsPantsSocksPreferences["T-Shirt"]["Jeans"]["Plain"] = 0.9;
	shirtsPantsSocksPreferences["T-Shirt"]["Jeans"]["Striped"] = 0.0;
	shirtsPantsSocksPreferences["T-Shirt"]["Jeans"]["Argyle"] = 0.1;

	Matrix3D copy = shirtsPantsSocksPreferences;

	copy["T-Shirt"]["Khakis"]["Plain"] = 0.1;
	copy["T-Shirt"]["Khakis"]["Striped"] = 0.4;
	copy["T-Shirt"]["Khakis"]["Argyle"] = 0.5;

	return 0;
}
```
Produces a 1-dimensional `Matrix` to rank types of shirts, a 2-dimensional `Matrix` to rank shirts-pants combinations, and a 3-dimensional `Matrix` to rank shirts-pants-socks combinations. Then, the shirt-pants-socks combination `Matrix` is copied and a few preferences are changed. (The 2-dimensional `Matrix` is declared conventionally without the macro.)
