//
// Created by wei on 2023/1/29.
//

#include "Configure/configure_base.h"
#include "Log/log.h"

LoadConfigre::LoadConfigre() = default;

LoadConfigre::~LoadConfigre() = default;

bool LoadConfigre::ReadXML(const std::string &sFilePath)
{
    auto oResult = m_oXMLFile.LoadFile(sFilePath.c_str());
    if(!oResult)
    {
        m_pElement = m_oXMLFile.RootElement();
        return true;
    }
    ZLOG << "Failed to load file, the error code is " << oResult;
    return false;
}

std::vector<std::string> LoadConfigre::ParseFilePath(const std::string &sNodePath)
{
    std::string sNode = sNodePath;
    size_t iIndex = sNode.find('/');
    sNode = sNode.substr(iIndex + 1);
    iIndex = sNode.find('/');
    std::vector<std::string> vecResult;
    while(std::string::npos != iIndex)
    {
        std::string sPath = sNode.substr(0,iIndex);
        vecResult.push_back(sPath);
        sNode = sNode.substr(iIndex + 1);
        iIndex = sNode.find('/');
    }
    vecResult.push_back(sNode);
    return vecResult;
}

bool LoadConfigre::GetElementValue(const std::string &sNodePath, std::string &sValue)
{
    auto oPath = ParseFilePath(sNodePath);
    for (auto & ii : oPath)
    {
        m_pElement = m_pElement->FirstChildElement(ii.c_str());
        if (nullptr == m_pElement)
        {
            ZLOG << "The node is not exist" << sNodePath;
            return false;
        }
    }
    sValue = m_pElement->GetText();
    m_pElement = m_oXMLFile.RootElement();
    return true;
}
