//
// Created by zw on 2021/10/20.
//

#ifndef NEWTRAVEL_MATH_MATRIX_ROTATE_H
#define NEWTRAVEL_MATH_MATRIX_ROTATE_H

#include "math_matrix.h"
#include "Math/math_vector3d.h"

class RotateMat: public CheckZero
    {
    friend std::ostream &operator<<(std::ostream &out, RotateMat &oRotateMat);
    public:
        RotateMat();
        RotateMat(int iEyeValue);
        ~RotateMat();
        RotateMat(const RotateMat &oRotate);
        double* operator[](int iIndex) const;
        RotateMat operator+(RotateMat &oRot);
        RotateMat operator*(double &dData);
        RotateMat operator*(RotateMat &dData);
        Vector3D operator*(const Vector3D &oVec3D);
        void operator/(double dData);
        double Norm2();

        RotateMat GetMatrixExp3();
        Vector3D GetScrewAxis();
    private:
        Matrix m_oRateMat;
    };


RotateMat GetSkewSymmetric(const Vector3D &oV3dData);



#endif // NEWTRAVEL_MATH_MATRIX_ROTATE_H
