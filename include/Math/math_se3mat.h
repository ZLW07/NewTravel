//
// Created by zw on 2021/10/19.
//

#ifndef NEWTRAVEL_MATH_SE3MAT_H
#define NEWTRAVEL_MATH_SE3MAT_H

#include "Math/math_matrix.h"
#include "Math/math_vector3d.h"
#include "Math/math_matrix_rotate.h"

class Se3Matrix: public CheckZero
    {
    friend std::ostream &operator<<(std::ostream &out, Se3Matrix &oSe3Matrix);
    public:
        Se3Matrix();
        Se3Matrix(RotateMat oRotateMat, Vector3D oPose);
        Se3Matrix(const Se3Matrix &oSe3Mat);
        double* operator[](const int iIndex) const;
        Se3Matrix GetMatrixExp6();
        Vector3D  GetScrewAxis(Se3Matrix &oMat4);
        RotateMat GetRotMatrix();
        Vector3D GetTranslation();
    private:
        Matrix m_oMat4;
    };

#endif // NEWTRAVEL_MATH_SE3MAT_H