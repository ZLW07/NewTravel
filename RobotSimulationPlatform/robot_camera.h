//
// Created by wei on 2022/12/22.
//

#ifndef NEWTRAVEL_ROBOT_CAMERA_H
#define NEWTRAVEL_ROBOT_CAMERA_H

#include "Eigen/Eigen"
#include <iostream>

 class RobotCamera
{
 public:
    RobotCamera()
    {
        OldMouse = new Eigen::Vector2d(0,0);
        Mouse = new Eigen::Vector2d(0,0);

        NewEye = new Eigen::Vector3d(2, 0, 0.5);
        NewUp = new Eigen::Vector3d(0, 0, 1);
        NewView = new Eigen::Vector3d(0, 0, 0.5);

        AuxY = new Eigen::Vector3d(0, 1, 0);
        AuxZ = new Eigen::Vector3d();
        *AuxZ = *NewEye - *NewView;
        AuxX = new Eigen::Vector3d();
        *AuxX = (*AuxY).cross(*AuxZ);
        AuxX->normalize();
    }

    Eigen::Matrix<double, 3, 3> getRotateMatrix(float angle, const Eigen::Vector3d &vector)
    {
        angle = angle / 2 * M_PI / 180;
        Eigen::Vector3d vec = vector.normalized();
        float cosa = cos(angle);
        float sina = sin(angle);

        double a = vec.x() * sina;
        double b = vec.y() * sina;
        double c = vec.z() * sina;

        Eigen::Matrix<double, 3, 3> matrix;
        matrix(0, 0) = 1.0 - 2.0 * (b * b + c * c);
        matrix(1, 1) = 1.0 - 2.0 * (c * c + a * a);
        matrix(2, 2) = 1.0 - 2.0 * (a * a + b * b);

        matrix(0, 1) = 2.0 * (a * b - c * cosa);
        matrix(0, 2) = 2.0 * (a * c + b * cosa);

        matrix(1, 0) = 2.0 * (a * b + c * cosa);
        matrix(1, 2) = 2.0 * (b * c - a * cosa);

        matrix(2, 0) = 2.0 * (a * c - b * cosa);
        matrix(2, 1) = 2.0 * (b * c + a * cosa);
        return matrix;
    }

     void getInitPos(int x, int y)
     {
         Mouse->x() = x;
         Mouse->y() = y;
         *OldMouse = *Mouse;
     }

    void executeRotateOperation(int x, int y)
    {
        Mouse->x() = x;
        Mouse->y() = y;
        Eigen::Vector3d MouseTrace = *AuxY * (OldMouse->y() - Mouse->y()) + *AuxX * (Mouse->x() - OldMouse->x());
        Eigen::Vector3d RotateAsix = MouseTrace.cross(*AuxZ);
        RotateAsix.normalize();

        float angle = MouseTrace.norm();
        Eigen::Matrix<double, 3, 3> rotatMatrix = getRotateMatrix(angle, RotateAsix);
        *NewEye = rotatMatrix * (*NewEye);
        *NewUp = rotatMatrix * (*NewUp);
        NewUp->normalized();

        *AuxY = *NewUp;
        *AuxZ = *NewEye - *NewView;
        *AuxX = (*AuxY).cross(*AuxZ);
        AuxX->normalize();
        *OldMouse = *Mouse;
    }



    //旋转后观察点方向与视线向上方向
    Eigen::Vector3d *NewEye;
    Eigen::Vector3d *NewUp;
    Eigen::Vector3d *NewView;

 private:
    //辅助坐标系三根轴
    Eigen::Vector3d *AuxX;
    Eigen::Vector3d *AuxY;
    Eigen::Vector3d *AuxZ;



    Eigen::Vector2d *OldMouse;
    Eigen::Vector2d *Mouse;
};

#endif // NEWTRAVEL_ROBOT_CAMERA_H
