#include "vmath.hpp"
#include <iomanip>
#include <ctime>
namespace VM
{

    float fastInverseSqrt(float x) 
    { 
        float xHalf = 0.5f * x;                // Compute half of the input
        int32_t i;                             // To hold the integer representation
        float y = x;                           // Preserve the original float value

        // Reinterpret the float bits as an integer
        i = *(reinterpret_cast<int32_t*>(&y)); // Access float as int
        i = 0x5f3759df - (i >> 1);             // Apply magic constant and shift
        y = *(reinterpret_cast<float*>(&i));   // Reinterpret back to float

        y = y * (1.5f - xHalf * y * y);        // First iteration
        y = y * (1.5f - xHalf * y * y);        // Second iteration (optional)

        return y;
    }

    float Vector2::magnitude(){return sqrt(x*x+y*y);}
    float Vector2::dot(const Vector2& v1, const Vector2& v2)
    {
        return v1.x*v2.x+v1.y*v2.y;
    }
    bool Vector2::normalize(void)
    {
        if (!std::isfinite(x) || !std::isfinite(y))
        {
            return false;
        }
        float sq = x*x + y*y;
        if (std::fabs(sq) < __FLT_EPSILON__)
        {
            return false;
        }
        float r_sqrt = fastInverseSqrt(sq);
        this->x*=r_sqrt;
        this->y*=r_sqrt;
        return true;
    }
    Vector2 Vector2::normalized(void) const
    {
        Vector2 V2Normalized(*this);
        V2Normalized.normalize();
        return V2Normalized;
    }
    Vector2::Vector2(const Vector2& other): x(other.x), y(other.y) {}
    float Vector2::operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw std::runtime_error("vector2 index out of range");
        }
    }

    float Vector3::magnitude(){return sqrt(x*x+y*y+z*z);}
    bool Vector3::normalize(void)
    {
        if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
        {
            return false;
        }
        float sq = x*x + y*y + z*z; 
        if (std::fabs(sq) < __FLT_EPSILON__)
        {
            return false;
        }
        float r_sqrt = fastInverseSqrt(sq);
        this->x*=r_sqrt;
        this->y*=r_sqrt;
        this->z*=r_sqrt;
        return true;
    }
    Vector3 Vector3::normalized(void) const
    {
        Vector3 V3Normalized(*this);
        V3Normalized.normalize();
        return V3Normalized;
    }
    Vector3::Vector3(const Vector3& other): x(other.x), y(other.y), z(other.z){}
    float Vector3::operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z; 
        default:
            throw std::runtime_error("vector3 index out of range");
        }
    }
    float Vector3::dot(const Vector3& v1, const Vector3& v2)
    {
        return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
    }
    Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2)
    {
        return Vector3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);            
    }

    float Vector4::dot(const Vector4& v1, const Vector4& v2)
    {
        return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z + v1.w*v2.w;
    }
    float Vector4::magnitude(){return sqrt(x*x+y*y+z*z+w*w);}
    bool Vector4::normalize(void) 
    {
        if (!std::isfinite(x) || !std::isfinite(y) ||  !std::isfinite(z)|| !std::isfinite(w))
        {
            return false;
        }
        float sq = x*x + y*y +z*z + w*w;
        if (std::fabs(sq) < __FLT_EPSILON__)
        {
            return false;
        }
        float r_sqrt = fastInverseSqrt(sq);

        this->x*=r_sqrt;
        this->y*=r_sqrt;
        this->z*=r_sqrt;
        this->w*=r_sqrt;
        return true;
    }
    Vector4 Vector4::normalized(void) const
    {
        Vector4 V4Normalized(*this);
        V4Normalized.normalize();
        return V4Normalized;
    }
    Vector4::Vector4(const Vector4& other): x(other.x), y(other.y), z(other.z), w(other.w) {}
    float Vector4::operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;  
        default:
            throw std::runtime_error("vector3 index out of range");
        }
    }

    std::ostream& operator << (std::ostream& output, const Vector2& vector)
    {
        output << "(" << vector.x << ", " << vector.y << ")";
        return output;
    }
    std::ostream& operator << (std::ostream& output, const Vector3& vector)
    {
        output << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return output;
    }
    std::ostream& operator << (std::ostream& output, const Vector4& vector)
    {
        output << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
        return output;
    }

    Vector2 operator + (const Vector2& v1, const Vector2& v2)
    {
        return Vector2(v1.x+v2.x, v1.y+v2.y);
    }
    Vector3 operator + (const Vector3& v1, const Vector3& v2)
    {
        return Vector3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
    }
    Vector4 operator + (const Vector4& v1, const Vector4& v2)
    {
        return Vector4(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w);
    }

    Vector2 operator - (const Vector2& v1, const Vector2& v2)
    {
        return Vector2(v1.x-v2.x, v1.y-v2.y);
    }
    Vector3 operator - (const Vector3& v1, const Vector3& v2)
    {
        return Vector3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
    }
    Vector4 operator - (const Vector4& v1, const Vector4& v2)
    {
        return Vector4(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w);
    }


    Matrix::~Matrix()
    {   
        // std::cout << "~M";
        if (matrix == nullptr)
        {
            std::cerr << "Data lost. Nullptr matrix\n";
        }
        else
        {
            for (int i = 0; i!= this->rows; i++)
            {
                delete [] matrix[i];
            }
            delete [] matrix;
        }
    }    
    std::ostream& operator << (std::ostream& output, const Matrix& m)
    {
        // std::cout << "out(" << m.rows << " " <<  m.columns << ")\n";
        for (int i=0; i != m.rows; i++)
        {
            for (int j=0; j != m.columns; j++)
            {
                float el = m.matrix[i][j];
                if (std::fabs(el) <= __FLT_EPSILON__*100){el = 0;}
                std::cout <<std::setw(12) << std::left << el;
            }
            std::cout << "\n";
        }
        return output;
    }
    Matrix::Matrix(int rows, int columns)
    {
        this->rows = rows;
        this->columns = columns;
        // std::cout << "M(" << rows << ", " << columns << ")\n";
        this->matrix = new float* [rows];
        for (int i =0; i!= rows; i++)
        {
            matrix[i] = new float[columns];
            for (int j =0; j!= columns; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    Matrix operator+(const Matrix& m1, const Matrix& m2)
    {
        if ((m1.columns != m2.columns) || (m1.rows != m2.rows))
        {
            throw std::runtime_error("Matrix size must be equal to perform addition\n");
        }
        Matrix newMatrix(m1.rows, m1.rows);
        for (int i = 0; i!= m1.rows; i++)
        {
            for (int j = 0; j!= m1.columns; j++)
            {
                newMatrix.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
            }
        }
        return newMatrix;
    }
    Matrix operator*(float a, const Matrix& m)
    {
        Matrix newMatrix(m.rows, m.rows);
        for (int i = 0; i!= m.rows; i++)
        {
            for (int j = 0; j!= m.columns; j++)
            {
                newMatrix.matrix[i][j] = m.matrix[i][j]*a;
            }
        }
        return newMatrix;
    }
    Matrix operator*(const Matrix& m, float a)
    {
        return a*m;
    }
    Matrix operator-(const Matrix& m1, const Matrix& m2)
    {
        if ((m1.columns != m2.columns) || (m1.rows != m2.rows))
        {
            throw std::runtime_error("Matrix size must be equal to perform substraction\n");
        }
        Matrix newMatrix(m1.rows, m1.rows);
        for (int i = 0; i!= m1.rows; i++)
        {
            for (int j = 0; j!= m1.columns; j++)
            {
                newMatrix.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
            }
        }
        return newMatrix;
    }
    bool operator==(const Matrix& m1, const Matrix& m2)
    {
        if ((m1.columns != m2.columns) || (m1.rows != m2.rows))
        {
            return false;
        }
        for (int i = 0; i!= m1.rows; i++)
        {
            for (int j = 0; j!= m1.columns; j++)
            {
                if (m1.matrix[i][j] != m2.matrix[i][j])
                {
                    return false;
                }
                
            }
        }
        return true;
    }
    Matrix Matrix::identity(int size)
    {
        if (size <= 0)
        {
            throw std::runtime_error("Matrix size must be at least 1\n");
        }
        Matrix newMatrix(size, size);
        for (int i = 0; i!= size; i++)
        {
            newMatrix.matrix[i][i] = 1;
            
        }
        return newMatrix;
    }
    Matrix Matrix::zero(int size)
    {
        if (size <= 0)
        {
            throw std::runtime_error("Matrix size must be at least 1\n");
        }
        Matrix newMatrix(size, size);
        return newMatrix;
    }
    Matrix Matrix::enumeratrix(int size)
    {
        if (size <= 0)
        {
            throw std::runtime_error("Matrix size must be at least 1\n");
        }
        Matrix newMatrix(size, size);
        for (int i = 0; i!= size; i++)
        {
            for (int j = 0; j!= size; j++)
            {
                newMatrix.matrix[i][j] = i*size+j; 
            }
        }
        return newMatrix;
    }
    Matrix Matrix::randomatrix(int size)
    {
        if (size <= 0)
        {
            throw std::runtime_error("Matrix size must be at least 1\n");
        }
        Matrix newMatrix(size, size);
        srand(time(0));
        for (int i = 0; i!= size; i++)
        {
            for (int j = 0; j!= size; j++)
            {
                newMatrix.matrix[i][j] = float((rand()%100))/10.0; 
            }
        }
        return newMatrix;
    }
    Vector Matrix::operator[](int index) const
    {
        // std::cout << this->rows << "\n";
        Vector NewVector;
        if (index >= this->rows)
        {
            std::cout << this->rows;
            throw std::runtime_error("Index > rows");
        }
        for (int i =0; i!=this->columns;i++)
        {
            NewVector.push_back(this->matrix[index][i]);
        }
            
        // NewVector.size = this->columns;
        return NewVector;
    }
    Matrix Matrix::transpose()
    {
        if (this->columns != this->rows)
        {
            throw std::runtime_error("Matrix must be square to perform transposition\n");
        }
        Matrix newMatrix(this->rows, this->rows);
        for (int i = 0; i!= this->rows; i++)
        {
            for (int j = 0; j!= this->columns; j++)
            {
                newMatrix.matrix[i][j] = this->matrix[j][i];
            }
        }
        return newMatrix;
    }
    Matrix operator*(const Matrix& m1,const Matrix& m2)
    {
        if (m1.rows != m2.columns)
        {
            throw std::runtime_error("M1 columns and M2 rows count must be equal to perform multiplication\n");
        }
        Matrix newMatrix(m1.rows, m2.columns);
        for (int i = 0; i!= m1.rows; i++)
        {
            for (int j = 0; j!= m2.columns; j++)
            {
                for (int k =0; k!= m1.columns; k++)
                {
                    newMatrix.matrix[i][j]+=m1.matrix[i][k]*m2.matrix[k][j];
                }
                
            }
        }
        return newMatrix;
    }
    Matrix Matrix::submatrix(int row, int column) const
    {
        if ((row <0) || (row>=this->rows) || (column <0) || (column>=this->columns) )
        {
            throw std::runtime_error("Submatrix index out of range\n");
        }

        int row_index, column_index; 
        Matrix newMatrix(this->rows-1, this->columns-1);
        for (int i = 0; i!= this->rows; i++)
        {
            for (int j = 0; j!=this->columns; j++)
            {
                if (i==row){continue;}
                if (j==column){continue;}
                // std::cout << "(" << i << ", " << j << ") for ";
                if (i>row){row_index=i-1;}
                else {row_index = i;}
                if (j>column){column_index=j-1;}
                else {column_index = j;}
                // std::cout << "(" << row_index << ", " << column_index << ") ";
                newMatrix.matrix[row_index][column_index]=this->matrix[i][j];
            }
            // std::cout << "\n";
        }
        return newMatrix;
    }
    float Matrix::determinant(void) const
    {
        if (this->columns != this->rows)
        {
            throw std::runtime_error("Matrix must be square to calculate determinant\n");
        }
        // std::cout << *this << "\n\n";
        
        if ((this->rows==2))
        {
            return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
        }
        float res=0;
        int coef = 0;
        for (int j = 0; j!= this->columns; j++)
        {
            if (j%2==0){coef = 1;}
            else{coef = -1;}
            res+= coef*this->submatrix(0,j).determinant()*matrix[0][j];
        }
        
        return res;
    }
    Matrix Matrix::inverse(void) const  // breaks on small size
    {
        if (this->columns != this->rows)
        {
            throw std::runtime_error("Matrix must be square to calculate inverse\n");
        }
        // std::cout << (*this).determinant() << "\n\n";
        float det = this->determinant();
        if (this->columns != this->rows)
        {
            throw std::runtime_error("Matrix is non inversible");
        }
        
        Matrix NewMatrix(columns, columns);
        int coef;
        for (int i =0; i!= rows; i++)
        {
            for (int j = 0; j!=columns; j++)
            {
                if ((i+j)%2==0){coef=1;}
                else {coef = -1;}
                NewMatrix.matrix[i][j] = float(coef * this->submatrix(i,j).determinant());
            }
        }
        return NewMatrix.transpose()*(1/det);
    }

    Vector::Vector()
    {
        this->values = new float[5];
        this->capacity = 5;
        this->size = 0;
    }
    Vector::Vector(float value)
    {
        this->values = new float[5];
        this->values[0] = value;
        this->capacity = 5;
        this->size = 1;
    }
    Vector::Vector(const Vector& other)
    {
        this->values = new float[5];
        this->capacity = 5;
        this->size = 0;
        for (int i = 0; i!= other.size; i++)
        {
            this->push_back(other[i]);
        }
        this->size = other.size;
    }
    void Vector::push_back(float value)
    {
        if (size == capacity)
        {
            resize();
        }
        this->values[size] = value;
        this->size ++;
    }
    void Vector::resize()
    {
        if (this->values == nullptr)
        {
            throw std::runtime_error("Nullptr vector pointer");
        }
        float* newValues = new float[this->capacity*2];
        for (int i = 0; i!= this->size; i++)
        {
            newValues[i] = (*this)[i];
        }
        delete [] this->values;
        this->values = newValues;
        this->capacity *=2;
        
    }
    Vector::~Vector()
    {
        delete [] this->values;
    }
    std::ostream& operator << (std::ostream& output, const Vector& v)
    {
        // std::cout << "out(" << m.rows << " " <<  m.columns << ")\n";
        std::cout << "(";
        for (int i=0; i != v.size; i++)
        {
            std::cout << v[i];
            if (i == v.size-1)
            {
                std::cout << ")";
            }
            else
            {
                std::cout << ", ";
            }
        }
        return output;
    }
    float& Vector::operator[](int index) const
    {
        // std::cout << "out(" << m.rows << " " <<  m.columns << ")\n";
        if (index >= this->size)
        {
            throw std::runtime_error("Index > vector size");
        }
        return this->values[index];
    }
    Vector operator - (const Vector& v1, const Vector& v2)
    {
        if (v1.size != v2.size)
        {
            throw std::runtime_error("Размеры векторов должны совпадать для вычитания");
        }
        Vector NewVector;
        for (int i = 0; i!=v1.size; i++)
        {
            NewVector.push_back(v1[i] - v2[i]);
        }
        return NewVector;            
    }
    Vector operator + (const Vector& v1, const Vector& v2)
    {
        if (v1.size != v2.size)
        {
            throw std::runtime_error("Размеры векторов должны совпадать для сложения");
        }
        Vector NewVector;
        for (int i = 0; i!=v1.size; i++)
        {
            NewVector.push_back(v1[i] + v2[i]);
        }
        return NewVector;            
    }
    float Vector::dot(const Vector& v1, const Vector& v2)
    {
        if (v1.size != v2.size)
        {
            throw std::runtime_error("Размеры векторов должны совпадать для скалярного умножения");
        }
        float ans;
        for (int i = 0; i!=v1.size; i++)
        {
            ans+= v1[i] * v2[i];
        }
        return ans;            
    }

}

