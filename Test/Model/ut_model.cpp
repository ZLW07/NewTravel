//
// Created by wei on 2022/4/11.
//

#include "Model/model_data.h"

int main()
{
    ModelData oMod;
    bool bRead = oMod.ReadAscllSTlFile("/home/wei/CLionProjects/NewTravel/Test/Model/1.STL");
    auto Data = oMod.GetPointCoordinateValue();
    for (int ii = 0; ii <  Data.size();ii++)
    {
        ZLOG<< "Data is " << Data[ii].v3dNormalVector;
    }
    ZLOG << bRead;
}
