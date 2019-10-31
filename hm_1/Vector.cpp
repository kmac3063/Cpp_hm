#include "Vector.h"
#include "Matrix.h"

namespace mat_vec {

    // Умножение всех элементов вектора на число слева (k * v)
    Vector operator*(double k, const Vector &v){
        Vector t(v);
        for (size_t i = 0; i < v.size(); i++)
            t[i] *= k;
        return t;
    };

    // Конструирует вектор размера size со значениями value
    Vector::Vector(size_t size, double value){
        size_ = size;
        array = new double[size_];
        for (size_t i = 0; i < size_; i++)
            array[i] = value;
    };
    
    // Конструктор копирования
    Vector::Vector(const Vector &src){
        size_ = src.size();
        array = new double[size_];
        for (size_t i = 0; i < size_; i++)
            array[i] = src.array[i];
    };
    
    // Оператор присваивания
    Vector &Vector::operator=(const Vector &rhs){
        delete[] array;

        size_ = rhs.size();
        array = new double[size_];        
        for (size_t i = 0; i < size_; i++)
            array[i] = rhs[i];
        
        return *this;
    };
    
    // Деструктор
    Vector::~Vector(){
        delete[] array;
    };

    // Возвращает размер вектора
    size_t Vector::size() const{
        return size_;
    };
    
    // Доступ к n-му элементу вектора
    double Vector::operator[](size_t n) const{
        return array[n];
    };

    double& Vector::operator[](size_t n){
        return array[n];
    };

    // L2 норма вектора
    double Vector::norm() const{
        double res = 0;
        for (size_t i = 0; i < size_; i++){
            res += array[i] * array[i];
        }

        return std::sqrt(res);
    };
    
    // Возвращает новый вектор, полученный нормализацией текущего (this)
    Vector Vector::normalized() const{
        double nrm = norm();
        Vector vector(*this);

        for (size_t i = 0; i < size_; i++){
            vector[i] /= nrm;
        }

        return vector;
    };
    
    // Нормализует текущий вектор
    void Vector::normalize(){
        double nrm = norm();

        for (size_t i = 0; i < size_; i++){
            array[i] /= nrm;
        }
    };

    // Поэлементное сложение векторов
    Vector Vector::operator+(const Vector &rhs) const{
        Vector tmp(*this);
        for (size_t i = 0; i < size_; i++){
            tmp[i] += rhs[i];
        }

        return tmp;
    };

    Vector& Vector::operator+=(const Vector &rhs){
        for (size_t i = 0; i < size_; i++){
            array[i] += rhs[i];
        }

        return *this;
    }

    // Поэлементное вычитание векторов
    Vector Vector::operator-(const Vector &rhs) const{
        Vector tmp(*this);
        for (size_t i = 0; i < size_; i++){
            tmp[i] -= rhs[i];
        }

        return tmp;
    }
    Vector& Vector::operator-=(const Vector &rhs){
        for (size_t i = 0; i < size_; i++){
            array[i] -= rhs[i];
        }

        return *this;
    }

    // Поэлементное умножение векторов
    Vector Vector::operator^(const Vector &rhs) const{
        Vector tmp(*this);
        for (size_t i = 0; i < size_; i++){
            tmp[i] *= rhs[i];
        }

        return tmp;
    }

    Vector& Vector::operator^=(const Vector &rhs){
        for (size_t i = 0; i < size_; i++){
            array[i] *= rhs[i];
        }
        return *this;
    }

    // Скалярное произведение
    double Vector::operator*(const Vector &rhs) const{
        double res = 0;
        for (size_t i = 0; i < size_; i++)
            res += rhs[i] * array[i];
        return res;
    }

    // Умножение всех элементов вектора на скаляр справа (v * k)
    Vector Vector::operator*(double k) const{
        Vector tmp(*this);
        for (size_t i = 0; i < size_; i++){
            tmp[i] *= k;
        }

        return tmp;
    }

    Vector& Vector::operator*=(double k){
        for (size_t i = 0; i < size_; i++)
            array[i] *= k;

        return *this;
    };

    // Деление всех элементов вектора на скаляр
    Vector Vector::operator/(double k) const{
        Vector tmp(*this);
        for (size_t i = 0; i < size_; i++){
            tmp[i] /= k;
        }

        return tmp;
    }
    Vector& Vector::operator/=(double k){
        for (size_t i = 0; i < size_; i++)
            array[i] /= k;

        return *this;
    }

    // Умножение вектора на матрицу
    Vector Vector::operator*(const Matrix &mat) const{
        Vector t(mat.shape().second);     
        for (size_t i = 0; i < mat.shape().second; i++){
            double res = 0;
            
            for (size_t j = 0; j < size_; j++){
                res += array[j] * mat[j][i];
            }
            t[i] = res;
        }

        return t;
    }

    Vector& Vector::operator*=(const Matrix &mat){
        return *this = *this * mat;
    }

    // Поэлементное сравнение
    bool Vector::operator==(const Vector &rhs) const{
        if (rhs.size() != size_) return false;

        for (size_t i = 0; i < size_; i++)
            if (abs(rhs[i] - array[i]) > EPS)
                return false;
        
        return true;
    }

    bool Vector::operator!=(const Vector &rhs) const{
        return !(rhs == *this);
    }

    void Vector::print(){
        std::cout << "Size: " << size_ << '\n' << "{ ";
        for (size_t i = 0; i < size_; i++){
            std::cout << array[i] << " ";
        }
        std::cout << "}\n\n";
    }

}; // namespace mat_vec
