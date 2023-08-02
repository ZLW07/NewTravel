//
// Created by wei on 2023/5/11.
//

#ifndef NEWTRAVEL_UT_COLLISION_DETECTION_H
#define NEWTRAVEL_UT_COLLISION_DETECTION_H
#include "CollisionDetection/model_cillision_detection.h"
#include "Kinematics/modern_robotics.h"
#include "gtest/gtest.h"

class TestCollision : public ::testing::Test
{
public:
    TestCollision(){};
    ~TestCollision() {}

    void Save(std::string sFileName, zl::ModelDataElement &oModelDataElement)
    {
        std::ofstream file(sFileName);
        file << "solid object\n";
        for (int ii = 0; ii < oModelDataElement.v3dNormalVector.size(); ii++)
        {
            file << " facet normal " << oModelDataElement.v3dNormalVector.at(ii).X() << " "
                 << oModelDataElement.v3dNormalVector.at(ii).Y() << " " << oModelDataElement.v3dNormalVector.at(ii).Z()
                 << "\n";
            file << "  outer loop\n";
            file << "     vertex " << oModelDataElement.vecPoint.at(ii).avPoint[0].X()/1000 << " "
                 << oModelDataElement.vecPoint.at(ii).avPoint[0].Y()/1000 << " "
                 << oModelDataElement.vecPoint.at(ii).avPoint[0].Z()/1000 << "\n";
            file << "     vertex " << oModelDataElement.vecPoint.at(ii).avPoint[1].X()/1000 << " "
                 << oModelDataElement.vecPoint.at(ii).avPoint[1].Y()/1000 << " "
                 << oModelDataElement.vecPoint.at(ii).avPoint[1].Z()/1000 << "\n";
            file << "     vertex " << oModelDataElement.vecPoint.at(ii).avPoint[2].X()/1000 << " "
                 << oModelDataElement.vecPoint.at(ii).avPoint[2].Y()/1000 << " "
                 << oModelDataElement.vecPoint.at(ii).avPoint[2].Z()/1000 << "\n";
            file << "  endloop\n";
            file << " endfacet\n";
        }
        file << "endsolid object\n";
        file.close();
    }

private:
};

#endif // NEWTRAVEL_UT_COLLISION_DETECTION_H
