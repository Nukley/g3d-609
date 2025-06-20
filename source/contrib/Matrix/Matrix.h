/**
  @file Matrix.h
  @author Morgan McGuire, matrix@graphics3d.com


   <I>G3D::Matrix is licensed under the <A HREF="http://www.opensource.org/licenses/bsd-license.php">BSD license</A>

  <CODE>
   <IMG SRC="http://opensource.org/trademarks/osi-certified/web/osi-certified-120x100.gif">
   <DT>Copyright &copy; 2000-2005, Morgan McGuire
   <DT>All rights reserved.
   <P>
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   <P>
   Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
   <P>
   Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
   <P>
   Neither the name of Morgan McGuire, Brown University, nor the names of
   its contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
   <P>
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
   THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef G3D_MATRIX_H
#define G3D_MATRIX_H
#include <graphics3D.h>

namespace G3D {

/** 
 N x M matrix.  
 
 Although this class has the semantics
 The actual data is tracked internally by a reference counted pointer;
 it is efficient to pass and assign Matrix objects because no data is actually copied.
 This avoids the headache of pointers and allows natural math notation:

  <PRE>
    Matrix A, B, C;
    // ...

    C = A * f(B);
    C = C.inverse();

    A = Matrix::identity(4);
    C = A;
    C.set(0, 0, 2.0); // Triggers a copy of the data so that A remains unchanged.

    // etc.

  </PRE>

  The Matrix::debugNumCopyOps and Matrix::debugNumAllocOps counters
  increment every time an operation forces the copy and allocation of matrices.  You
  can use these to detect slow operations when efficiency is a major concern.

  Some methods accept an output argument instead of returning a value.  For example,
  <CODE>A = B.transpose()</CODE> can also be invoked as <CODE>B.transpose(A)</CODE>.
  The latter may be more efficient, since Matrix may be able to re-use the storage of
  A (if it has approximatly the right size and isn't currently shared with another matrix).
  

 */
class Matrix {
public:
    /** 
      Internal precision.  Currently float, but this may become a templated class in the future
      to allow operations like Matrix<double> and Matrix<ComplexFloat>.

      Not necessarily a plain-old-data type (e.g., could ComplexFloat), but must be something 
      with no constructor, that can be safely memcpyd, and that has a bit pattern of all zeros
      when zero.*/
    typedef float T;

    /** Incremented every time the elements of a matrix are copied.  Useful for profiling your
        own code that uses Matrix to determine when it is slow due to copying.*/
    static int                     debugNumCopyOps;

    /** Incremented every time a new matrix object is allocated.  Useful for profiling your
        own code that uses Matrix to determine when it is slow due to allocation.*/
    static int                     debugNumAllocOps;

private:

    /** Does not throw exceptions-- assumes the caller has taken care of 
        argument checking.*/
    class Impl : public ReferenceCountedObject {
    public:
        /** elt[r][c] = the element.  Pointers into data.*/
        T**                 elt;

        /** Row major data for the entire matrix. */
        T*                  data;

        /** The number of rows */
        int                 R;

        /** The number of columns */
        int                 C;

        size_t              dataSize;

        /** If R*C is much larger or smaller than the current, deletes all previous data
            and resets to random data.  Otherwise re-uses existing memory and just resets
            R, C, and the row pointers. */
        void setSize(int newRows, int newCols);

    public:

        inline Impl() : elt(NULL), data(NULL), R(0), C(0), dataSize(0) {}

        Impl(const Matrix3& M);

        Impl(const Matrix4& M);

        inline Impl(int r, int c) : elt(NULL), data(NULL), R(0), C(0), dataSize(0) {
            setSize(r, c);
        }

        Impl& operator=(const Impl& m);

        inline Impl(const Impl& B) : elt(NULL), data(NULL), R(0), C(0), dataSize(0) {
            // Use the assignment operator
            *this = B;
        }

        ~Impl();

        void setZero();

        inline void set(int r, int c, T v) {
            debugAssert((uint)r < (uint)R);
            debugAssert((uint)c < (uint)C);
            elt[r][c] = v;
        }

        inline const T& get(int r, int c) const {
            debugAssert((uint)r < (uint)R);
            debugAssert((uint)c < (uint)C);
            return elt[r][c];
        }

        /** Multiplies this by B and puts the result in out. */
        void mul(const Impl& B, Impl& out) const;

        /** Ok if out == this or out == B */
        void add(const Impl& B, Impl& out) const;

        /** Ok if out == this or out == B */
        void add(T B, Impl& out) const;

        /** Ok if out == this or out == B */
        void sub(const Impl& B, Impl& out) const;

        /** Ok if out == this or out == B */
        void sub(T B, Impl& out) const;

        /** B - this */
        void lsub(T B, Impl& out) const;

        /** Ok if out == this or out == B */
        void arrayMul(const Impl& B, Impl& out) const;

        /** Ok if out == this or out == B */
        void mul(T B, Impl& out) const;

        /** Ok if out == this or out == B */
        void arrayDiv(const Impl& B, Impl& out) const;

        /** Ok if out == this or out == B */
        void div(T B, Impl& out) const;

        void negate(Impl& out) const;

        /** Slow way of computing an inverse; for reference */
        void inverseViaAdjoint(Impl& out) const;

        /** Use Gaussian elimination with pivots to solve for the inverse destructively in place. */
        void inverseInPlaceGaussJordan();

        void adjoint(Impl& out) const;

        /** Matrix of all cofactors */
        void cofactor(Impl& out) const;

        /**
         Cofactor [r][c] is defined as C[r][c] = -1 ^(r+c) * det(A[r][c]),
         where A[r][c] is the (R-1)x(C-1) matrix formed by removing row r and
         column c from the original matrix. 
        */
        T cofactor(int r, int c) const;

        /** Ok if out == this or out == B */
        void transpose(Impl& out) const;

        T determinant() const;

        /** Determinant computed without the given row and column */
        T determinant(int r, int c) const;

        void arrayLog(Impl& out) const;

        void arrayExp(Impl& out) const;

        void arraySqrt(Impl& out) const;

        void arrayCos(Impl& out) const;

        void arraySin(Impl& out) const;

        void swapRows(int r0, int r1);

        void swapAndNegateCols(int c0, int c1);

        void mulRow(int r, const T& v);

        void abs(Impl& out) const;

        /** Makes a (R-1)x(C-1) copy of this matrix */
        void withoutRowAndCol(int excludeRow, int excludeCol, Impl& out) const;

        bool anyNonZero() const;

        bool allNonZero() const;

        void setRow(int r, const T* vals);

        void setCol(int c, const T* vals);
    };

    typedef ReferenceCountedPointer<Impl> ImplRef;

    ImplRef       impl;

    inline Matrix(ImplRef i) : impl(i) {}
    inline Matrix(Impl* i) : impl(ImplRef(i)) {}

    /** Used by SVD */
    class SortRank {
    public:
        T           value;
        int         col;

        inline bool operator>(const SortRank& x) const {
            return x.value > value;
        }
        
        inline bool operator<(const SortRank& x) const {
            return x.value < value;
        }
        
        inline bool operator>=(const SortRank& x) const {
            return x.value >= value;
        }
        
        inline bool operator<=(const SortRank& x) const {
            return x.value <= value;
        }
        
        inline bool operator==(const SortRank& x) const {
            return x.value == value;
        }

        inline bool operator!=(const SortRank& x) const {
            return x.value != value;
        }
    };

public:

    Matrix() : impl(new Impl(0, 0)) {}

    Matrix(const Matrix3& M) : impl(new Impl(M)) {}

    Matrix(const Matrix4& M) : impl(new Impl(M)) {}

    template<class S>
    static Matrix fromDiagonal(const Array<S>& d) {
        Matrix D = zero(d.length(), d.length());
        for (int i = 0; i < d.length(); ++i) {
            D.set(i, i, d[i]);
        }
        return D;
    }

    static Matrix fromDiagonal(const Matrix& d);

    /** Returns a new matrix that is all zero. */
    Matrix(int R, int C) : impl(new Impl(R, C)) {
        impl->setZero();
    }

    /** Returns a new matrix that is all zero. */
    static Matrix zero(int R, int C);

    /** Returns a new matrix that is all one. */
    static Matrix one(int R, int C);

    /** Returns a new identity matrix */
    static Matrix identity(int N);

    /** Uniformly distributed values between zero and one. */
    static Matrix random(int R, int C);

    /** The number of rows */
    inline int rows() const {
        return impl->R;
    }

    /** Number of columns */
    inline int cols() const {
        return impl->C;
    }

    /** Generally more efficient than A * B */
    Matrix& operator*=(const T& B);

    /** Generally more efficient than A / B */
    Matrix& operator/=(const T& B);

    /** Generally more efficient than A + B */
    Matrix& operator+=(const T& B);

    /** Generally more efficient than A - B */
    Matrix& operator-=(const T& B);

    /** No performance advantage over A * B because
        matrix multiplication requires intermediate
        storage. */
    Matrix& operator*=(const Matrix& B);

    /** Generally more efficient than A + B */
    Matrix& operator+=(const Matrix& B);

    /** Generally more efficient than A - B */
    Matrix& operator-=(const Matrix& B);

    /** Returns a new matrix that is a subset of this one,
        from r1:r2 to c1:c2, inclusive.*/
    Matrix subMatrix(int r1, int r2, int c1, int c2) const;

    /** Matrix multiplication.  To perform element-by-element multiplication, 
        see arrayMul. */
    inline Matrix operator*(const Matrix& B) const {
        Matrix C(impl->R, B.impl->C);
        impl->mul(*B.impl, *C.impl);
        return C;
    }

    /** See also A *= B, which is more efficient in many cases */
    inline Matrix operator*(const T& B) const {
        Matrix C(impl->R, impl->C);
        impl->mul(B, *C.impl);
        return C;
    }

    /** See also A += B, which is more efficient in many cases */
    inline Matrix operator+(const Matrix& B) const {
        Matrix C(impl->R, impl->C);
        impl->add(*B.impl, *C.impl);
        return C;
    }

    /** See also A -= B, which is more efficient in many cases */
    inline Matrix operator-(const Matrix& B) const {
        Matrix C(impl->R, impl->C);
        impl->sub(*B.impl, *C.impl);
        return C;
    }

    /** See also A += B, which is more efficient in many cases */
    inline Matrix operator+(const T& v) const {
        Matrix C(impl->R, impl->C);
        impl->add(v, *C.impl);
        return C;
    }

    /** See also A -= B, which is more efficient in many cases */
    inline Matrix operator-(const T& v) const {
        Matrix C(impl->R, impl->C);
        impl->sub(v, *C.impl);
        return C;
    }


    Matrix operator>(const T& scalar) const;

    Matrix operator<(const T& scalar) const;

    Matrix operator>=(const T& scalar) const;

    Matrix operator<=(const T& scalar) const;

    Matrix operator==(const T& scalar) const;

    Matrix operator!=(const T& scalar) const;

    /** scalar B - this */
    inline Matrix lsub(const T& B) const {
        Matrix C(impl->R, impl->C);
        impl->lsub(B, *C.impl);
        return C;
    }

    inline Matrix arrayMul(const Matrix& B) const {
        Matrix C(impl->R, impl->C);
        impl->arrayMul(*B.impl, *C.impl);
        return C;
    }

    Matrix3 toMatrix3() const;

    Matrix4 toMatrix4() const;
    
    Vector2 toVector2() const;

    Vector3 toVector3() const;

    Vector4 toVector4() const;

    /** Mutates this */
    void arrayMulInPlace(const Matrix& B);

    /** Mutates this */
    void arrayDivInPlace(const Matrix& B);

    // Declares an array unary method and its explicit-argument counterpart
#   define DECLARE_METHODS_1(method)\
    inline Matrix method() const {\
        Matrix C(impl->R, impl->C);\
        impl->method(*C.impl);\
        return C;\
    }\
    void method(Matrix& out) const;


    DECLARE_METHODS_1(abs)
    DECLARE_METHODS_1(arrayLog)
    DECLARE_METHODS_1(arrayExp)
    DECLARE_METHODS_1(arraySqrt)
    DECLARE_METHODS_1(arrayCos)
    DECLARE_METHODS_1(arraySin)
    DECLARE_METHODS_1(negate)

#   undef DECLARE_METHODS_1

    inline Matrix operator-() const {
        return negate();
    }

    /**
     A<SUP>-1</SUP>
     */
    inline Matrix inverse() const {
        Impl* A = new Impl(*impl);
        A->inverseInPlaceGaussJordan();
        return Matrix(A);
    }

    inline T determinant() const {
        return impl->determinant();
    }

    /**
     A<SUP>T</SUP>
     */
    inline Matrix transpose() const {
        Impl* A = new Impl(cols(), rows());
        impl->transpose(*A);
        return Matrix(A);
    }

    /** Transpose in place; more efficient than transpose */
    void transpose(Matrix& out) const;

    inline Matrix adjoint() const {
        Impl* A = new Impl(cols(), rows());
        impl->adjoint(*A);
        return Matrix(A);
    }

    /**     
     (A<SUP>T</SUP>A)<SUP>-1</SUP>A<SUP>T</SUP>) computed 
     using SVD.

     @param tolerance Use -1 for automatic tolerance.
     */
    Matrix pseudoInverse(float tolerance = -1) const;

    /**
     (A<SUP>T</SUP>A)<SUP>-1</SUP>A<SUP>T</SUP>) computed
     using Gauss-Jordan elimination.
     */
    inline Matrix gaussJordanPseudoInverse() const {
        Matrix trans = transpose();
        return (trans * (*this)).inverse() * trans;
    }

    /** Singular value decomposition.  Factors into three matrices 
        such that this = U * fromDiagonal(d) * V.transpose().

        The matrix must have at least as many rows as columns.
         
        @param sort If true (default), the singular values
        are arranged so that D is sorted from largest to smallest.
        */
    void svd(Matrix& U, Array<T>& d, Matrix& V, bool sort = true) const;

    void set(int r, int c, T v);

    void setCol(int c, const Matrix& vec);

    void setRow(int r, const Matrix& vec);

    Matrix col(int c) const;

    Matrix row(int r) const;

    T get(int r, int c) const;

    Vector2int16 size() const {
        return Vector2int16(rows(), cols());
    }

    int numElements() const {
        return rows() * cols();
    }

    void swapRows(int r0, int r1);

    /** Swaps columns c0 and c1 and negates both */
    void swapAndNegateCols(int c0, int c1);

    void mulRow(int r, const T& v);

    /** Returns true if any element is non-zero */
    bool anyNonZero() const;

    /** Returns true if all elements are non-zero */
    bool allNonZero() const;

    inline bool allZero() const {
        return !anyNonZero();
    }

    inline bool anyZero() const {
        return !allNonZero();
    }

    /** Serializes in Matlab source format */
    void serialize(TextOutput& t) const;

    void debugPrint(const std::string& name) const;

    inline void debugPrint() const {
        static const std::string name = "";
        debugPrint(name);
    }

    /** 2-norm (sqrt(sum(squares)) */
    double norm() const;

    /**
      Low-level SVD functionality.  Useful for applications that do not want
      to construct a Matrix but need to perform the SVD operation.

      this = U * D * V'

      Assumes that rows >= cols

      @return NULL on success, a string describing the error on failure.
      @param U rows x cols matrix to be decomposed, gets overwritten with U, a rows x cols matrix with orthogonal columns.
      @param D vector of singular values of a (diagonal of the D matrix).  Length cols.
      @param V returns the right orthonormal transformation matrix, size cols x cols

      @cite Based on Dianne Cook's implementation, which is adapted from 
      svdecomp.c in XLISP-STAT 2.1, which is code from Numerical Recipes 
      adapted by Luke Tierney and David Betz.  The Numerical Recipes code 
      is adapted from Forsythe et al, who based their code on Golub and
      Reinsch's original implementation.
    */
    static const char* svdCore(float** U, int rows, int cols, float* D, float** V);

};

}

inline G3D::Matrix operator-(const G3D::Matrix::T& v, const G3D::Matrix& M) {
    return M.lsub(v);
}

inline G3D::Matrix operator*(const G3D::Matrix::T& v, const G3D::Matrix& M) {
    return M * v;
}

inline G3D::Matrix operator+(const G3D::Matrix::T& v, const G3D::Matrix& M) {
    return M + v;
}

inline G3D::Matrix abs(const G3D::Matrix& M) {
    return M.abs();
}

#endif

