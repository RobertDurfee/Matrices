# Matrices
C++ matrix class for accessing elements by name rather than index.

### Disclaimer

This is not production-worthy code! View this simply as a proof-of-concept.

### Initialization
```
Matrix();

Matrix(int size, vector<string> labels);
Matrix(int size, char ** labels);

Matrix(int size, vector<T> values, vector<string> labels);
Matrix(int size, T * values, char ** labels);

Matrix(int size, T value, vector<string> labels);
Matrix(int size, T value, char ** labels);
```
A `Matrix` can be initialized several different ways:

1. Without parameters which will require `Assign` later on.
2. With labels only which, depending on the type, will require `Assign` later on.
3. With labels and values.
4. With labels and a single value which will be copied to each element.

Two headers are provided utilizing a vector of strings or a pointer to a pointer of charaters as labels to facilitate different applications and avoid converting types.

### Assigning
```
void Assign(int size, vector<string> labels);
void Assign(int size, char ** labels);
  
void Assign(int size, vector<T> values, vector<string> labels);
void Assign(int size, T * values, char ** labels);
  
void Assign(int size, T value, vector<string> labels);
void Assign(int size, T & value, char ** labels);
```
`Assign` methods provide the same functions as the constructors to allow alteration of the `Matrix` without declaring a new instance. Each time an `Assign` method is called, all the data in a `Matrix` will be deleted and new space will be allocated.

### Accessing by Label
```
T& operator[](string label);
T& operator[](char * label);
```
The purpose of creating this structure was to allow access to elements through a label rather than maintaining two different structres, one containing labels and the other containing values. As a result, the `operator[]` method allows a label to be passed as an index. The label is identified in the structure and the value it corresponds to is passed as output. This output can be read from or written to.

### Accessing by Index
```
T& operator[](int index);
```
This method will perform exactly as expected allowing access to values through regular indices. 

### Equating
```
Matrix<T>& operator=(const Matrix<T>& matrix);
```
The `operator=` method will allow a `Matrix` to become equal to another by first clearing the modified `Matrix` and allocating appropriate space and then copying each value and label to the new `Matrix`.

### Deinitialization
```
~Matrix()
```
A deconstructor is only needed for the pointer to a pointer of characters implementation as the vector of strings implementation uses RAII. In this destructor, all allocated memory used by the `Matrix` is freed.

### Typedefs
```
typedef Matrix<double>   Matrix1D;
typedef Matrix<Matrix1D> Matrix2D;
typedef Matrix<Matrix2D> Matrix3D;
```
For convenience, three typedefs are provided. Since the `Matrix` class is generic, the class can become recursive. As a result, a 3-dimensional `Matrix` can be declared by typing `Matrix<Matrix<Matrix<double>>>`. This is a little ugly and can become annoying to type each time, therefore these typedefs are provided to simplify declarations.

### Macros
```
#define MATRIX1D(X, X_LABELS) (Matrix1D(X, X_LABELS))
#define MATRIX2D(X, Y, X_LABELS, Y_LABELS) (Matrix2D(X, MATRIX1D(Y, Y_LABELS), X_LABELS))
#define MATRIX3D(X, Y, Z, X_LABELS, Y_LABELS, Z_LABELS) (Matrix3D(X, MATRIX2D(Y, Z, Y_LABELS, Z_LABELS), X_LABELS))
```
For additional convenience, three macros are provided. Since the `Matrix` class is generic, the class can become recursive. As a result, a 3-dimensional `Matrix` can be defined by typing `Matrix<Matrix<Matrix<double>>>(x, Matrix<Matrix<double>>(y, Matrix<double>(z, zLabels), yLabels), xLabels)`. This is incredibly ugly, confusing, and very annoying to type each time, therefore these macros are provided to simplify definitions.

### Example
