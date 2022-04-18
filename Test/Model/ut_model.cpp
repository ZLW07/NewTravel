//
// Created by wei on 2022/4/11.
//

#include "Model/model_data.h"

int main()
{
    std::vector<ModelDataBase>  vecJoint1;
    std::vector<ModelDataBase>  vecJoint2;
    ModelManager oMod;
    bool bReadJoint1 = oMod.LoadModelData("../../Data/RobotModel/1.STL",vecJoint1);
    bool bReadJoint2 = oMod.LoadModelData("../../Data/RobotModel/2.STL",vecJoint2);
    if (bReadJoint1 && bReadJoint2)
    {
        ZLOG << vecJoint1.size();
        ZLOG << vecJoint2.size();
    }
}
