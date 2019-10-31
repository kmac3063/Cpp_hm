#include "Matrix.h"
#include "Vector.h"


namespace mat_vec {
	Matrix::Matrix(size_t size, double value): Matrix(size, size, value){}
	
	// Возвращает единичную матрицу
	Matrix Matrix::eye(size_t size){
		Matrix t(size);
		for (size_t i = 0; i < size; i++)
			t[i][i] = 1;

		return t;
	};

	// Возвращает матрицу с размерами rows x cols, заполненную value
	Matrix::Matrix(size_t rows, size_t cols, double value){
		size_ = {rows, cols};
		matrix = new double* [size_.first];

		for (size_t i = 0; i < size_.first; i++){
			matrix[i] = new double[size_.second];
			for (size_t j = 0; j < size_.second; j++)
				matrix[i][j] = value;
		}
	}

	// Конструктор копирования
	Matrix::Matrix(const Matrix &src){
		size_ = src.shape();
		
		matrix = new double* [size_.first];
		for (size_t i = 0; i < size_.first; i++){
			matrix[i] = new double[size_.second];

			for (size_t j = 0; j < size_.second; j++)
				matrix[i][j] = src[i][j];
		}
	}

	// Оператор присваивания
	Matrix &Matrix::operator=(const Matrix &rhs){
		for (size_t i = 0; i < size_.first; i++)
			delete[] matrix[i];
		delete[] matrix;

		size_ = rhs.shape();
		matrix = new double* [size_.first];
		for (size_t i = 0; i < size_.first; i++){
			matrix[i] = new double[size_.second];

			for (size_t j = 0; j < size_.second; j++)
				matrix[i][j] = rhs[i][j];
		}

		return *this;
	}

	// Деструктор
	Matrix::~Matrix(){
		for (size_t i = 0; i < size_.first; i++)
			delete[] matrix[i];
		delete[] matrix;
	};

	// Изменяет ширину и высоту матрицы, не изменяя при этом
	// порядок следования элементов от левого верхнего к правому нижнему:
	//
	// [1 2 3] -> [1 2]
	// [4 5 6] -> [3 4]
	//            [5 6]
	void Matrix::reshape(size_t rows, size_t cols){
		Matrix t(rows, cols, 0);
		size_t i1 = 0;
		size_t j1 = 0;

		for (size_t i = 0; i < rows; i++){
			for (size_t j = 0; j < cols; j++){
				t[i][j] = matrix[i1][j1];
				j1 = (j1 + 1) % size_.second;
				if (j1 == 0)
					i1++;
			}
		}

		*this = t;
	}

	// Возвращает пару {rows, cols} -- количество строк и столбцов матрицы
	std::pair<size_t, size_t> Matrix::shape() const{
		return size_;
	}

	// Возвращает элемент на позиции [row, col]
	double Matrix::get(size_t row, size_t col) const{
		return matrix[row][col];
	}

	double* Matrix::operator[](size_t n){
		return matrix[n];
	}

	double* Matrix::operator[](size_t n) const{
		return matrix[n];
	}

	// Поэлементное сложение
	Matrix Matrix::operator+(const Matrix &rhs) const{
		Matrix t(*this);
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				t[i][j] += rhs[i][j];
			}
		}
		
		return t;
	}

	Matrix &Matrix::operator+=(const Matrix &rhs){
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				matrix[i][j] += rhs[i][j];
			}
		}

		return *this;
	}

	// Поэлементное вычитание
	Matrix Matrix::operator-(const Matrix &rhs) const{
		Matrix t(*this);
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				t[i][j] -= rhs[i][j];
			}
		}
		
		return t;
	}
	Matrix &Matrix::operator-=(const Matrix &rhs){
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				matrix[i][j] -= rhs[i][j];
			}
		}

		return *this;
	}

	// Матричное умножение
	Matrix Matrix::operator*(const Matrix &rhs) const{
		Matrix t(size_.first, rhs.size_.second, 0);
		
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < rhs.size_.second; j++){
				double res = 0;
				for (size_t k = 0; k < size_.second; k++)
					res += matrix[i][k] * rhs[k][j];
				t[i][j] = res;
			}
		}
		
		return t;
	}

	Matrix& Matrix::operator*=(const Matrix &rhs){
		return *this = *this * rhs;
	}

	// Умножение всех элементов матрицы на константу
	Matrix Matrix::operator*(double k) const{
		Matrix t(*this);
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				t[i][j] *= k;
			}
		}
		
		return t;
	}
	Matrix &Matrix::operator*=(double k){
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				matrix[i][j] *= k;
			}
		}

		return *this;
	}

	// Деление всех элементов матрицы на константу
	Matrix Matrix::operator/(double k) const{
		Matrix t(*this);
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				t[i][j] /= k;
			}
		}
		
		return t;
	}
	Matrix &Matrix::operator/=(double k){
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				matrix[i][j] /= k;
			}
		}

		return *this;
	}
	// Возвращает новую матрицу, полученную транспонированием текущей (this)
	Matrix Matrix::transposed() const{
		Matrix t(size_.second, size_.first, 0);

		for(size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++){
				t[j][i] = matrix[i][j];
			}
		}

		return t;
	}

	// Транспонирует текущую матрицу
	void Matrix::transpose(){
		if (size_.first == size_.second){
			for (size_t i = 0; i < size_.first; i++)
				for (size_t j = i; j < size_.second; j++)
					std::swap(matrix[i][j], matrix[j][i]);
		}
		else{
			*this = (*this).transposed();
		}
	}

	// Определитель
	double Matrix::determinant(mat_vec::Matrix mat, size_t size){ 
		double det = 0;
		mat_vec::Matrix t_mat(size, 0);

		if (size == 1)
			return mat[0][0];
		if (size == 2)
			return (mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1]);

		for (size_t k = 0; k < size; k++) {
			t_mat = mat.сofactor(0, k);
			det += (pow(-1, k) * mat[0][k] * determinant(t_mat, size - 1));
		}
		
		return det;
	}

	double Matrix::det() const{
		return determinant(*this, size_.first);
	}
	// Обратная матрица
	Matrix Matrix::inv() const{
		return Matrix(adjoint() / det());
	}

	Matrix Matrix::adjoint() const{
		size_t size = size_.first;
		
		Matrix adj(size), temp(size);
	    
		if (size == 1) { 
	        adj[0][0] = 1; 
	        return adj; 
	    }
	  
	    for (size_t i = 0; i < size; i++) { 
	        for (size_t j = 0; j < size; j++){ 
	            temp = сofactor(i, j);

	            adj[j][i] = pow(-1, i + j) * determinant(temp, size - 1); 
	        } 
	    } 
		return adj;
	} 
		
	Matrix Matrix::сofactor(size_t p, size_t q) const{
		size_t size = size_.first;

		Matrix temp(size);
		size_t i = 0, j = 0;

		// Looping for each element of the matrix 
		for (size_t row = 0; row < size; row++){
			if (row == p) continue;
			for (size_t col = 0; col < size; col++){
				if (col == q) continue;

				temp[i][j++] = matrix[row][col]; 					
				if (j == size - 1){
					j = 0;
					i++;
				}
			}
		}

		return temp;
	}
		
	  
	// Умножение матрицы на вектор
	Vector Matrix::operator*(const Vector &vec) const{
		Vector t(size_.first);

		for (size_t i = 0; i < size_.first; i++){
			double res = 0;

			for (size_t j = 0; j < vec.size(); j++){
				res += matrix[i][j] * vec[j];
			}
			t[i] = res;
		}

		return t;
	}

	// Поэлементное сравнение
	bool Matrix::operator==(const Matrix &rhs) const{
		if (size_ != rhs.shape()) 
			return false;
	
		for (size_t i = 0; i < size_.first; i++)
			for (size_t j = 0; j < size_.second; j++)
				if (abs(matrix[i][j] - rhs[i][j]) > EPS)
					return false;
		
		return true;
	}

	bool Matrix::operator!=(const Matrix &rhs) const{
		return !(*this == rhs);
	}

	void Matrix::print(){
		std::cout << "Size: " << size_.first << " x " << size_.second << "\n"; 
		for (size_t i = 0; i < size_.first; i++){
			for (size_t j = 0; j < size_.second; j++)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}
		
		std::cout << '\n';
	}
};
 // namespace mat_vec
