#ifndef VMATH_HPP
#define VMATH_HPP


#include <math.h>
#include <iostream>
#include <stdexcept>
#define __FLT_EPSILON__ 1.19209289550781250000000000000000000e-7F


namespace VM
{
    float fastInverseSqrt(float x);
    
    struct Vector2
    {
        float x, y;
        Vector2(float Nx = 0, float Ny = 0) : x(Nx), y(Ny) {}
        Vector2(const Vector2& other);
        bool normalize(void);
        
        Vector2 normalized(void) const;
        float magnitude();
        static float dot(const Vector2& v1, const Vector2& v2);
        friend std::ostream& operator << (std::ostream& output, const Vector2& vector);
        friend Vector2 operator + (const Vector2& vector1, const Vector2& vector2);
        friend Vector2 operator - (const Vector2& vector1, const Vector2& vector2);
        float operator[](int index) const;
    };

    struct Vector3
    {
        float x, y, z;
        Vector3(float Nx = 0, float Ny = 0, float Nz = 0) : x(Nx), y(Ny), z(Nz) {}
        Vector3(const Vector3& other);
        bool normalize(void);
        Vector3 normalized(void) const;
        float magnitude();
        static float dot(const Vector3& v1, const Vector3& v2);
        static Vector3 cross(const Vector3& v1, const Vector3& v2);
        friend std::ostream& operator << (std::ostream& output, const Vector3& vector);
        friend Vector3 operator + (const Vector3& vector1, const Vector3& vector2);
        friend Vector3 operator - (const Vector3& vector1, const Vector3& vector2);
        float operator[](int index) const;
    };
    
    struct Vector4
    {
        float x, y, z, w;
        Vector4(float Nx = 0, float Ny = 0, float Nz = 0, float Nw = 0) : x(Nx), y(Ny), z(Nz), w(Nw) {}
        Vector4(const Vector4& other);
        bool normalize(void);
        Vector4 normalized(void) const;
        float magnitude();
        static float dot(const Vector4& v1, const Vector4& v2);
        friend std::ostream& operator << (std::ostream& output, const Vector4& vector);
        friend Vector4 operator + (const Vector4& v1, const Vector4& v2);
        friend Vector4 operator - (const Vector4& v1, const Vector4& v2);
        float operator[](int index) const;
    };

    struct Vector
    {
        float* values;
        int size;
        int capacity;
        Vector();
        Vector(float val);
        Vector(const Vector& other);
        ~Vector();
        void resize();
        static float dot(const Vector& v1, const Vector& v2);
        void push_back(float value);
        float& operator [] (int index) const;
        friend std::ostream& operator << (std::ostream& output, const Vector& vector);
        friend Vector operator + (const Vector& v1, const Vector& v2);
        friend Vector operator - (const Vector& v1, const Vector& v2);
    };
    struct Matrix
    {
        int rows, columns;
        float  ** matrix;
        Matrix(int rows = 1, int columns = 1);
        ~Matrix();
        Vector operator [] (int index) const;
        static Matrix identity(int size);
        static Matrix zero(int size);
        static Matrix enumeratrix(int size);
        static Matrix randomatrix(int size);
        Matrix transpose();
        Matrix submatrix(int row, int column) const;
        float determinant(void) const;
        Matrix inverse(void) const;
        friend bool operator==(const Matrix& m1, const Matrix& m2);
        friend std::ostream& operator << (std::ostream& output, const Matrix& matrix);
        friend Matrix operator - (const Matrix& m1, const Matrix& m2);
        friend Matrix operator + (const Matrix& m1, const Matrix& m2);
        friend Matrix operator * (float a, const Matrix& m);
        friend Matrix operator * (const Matrix& m, float a);
        friend Matrix operator * (const Matrix& m1, const Matrix& m2);

    };
    
}

#endif //VMATH_HPP