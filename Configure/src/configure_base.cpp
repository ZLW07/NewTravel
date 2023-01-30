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
    if (!oResult)
    {
        m_pElement = m_oXMLFile.RootElement();
        return true;
    }
    ZLOG << "Failed to load file, the error code is " << oResult;
    return false;
}

bool LoadConfigre::ParseFilePath(const std::string &sNodePath)
{
    std::string sNode = sNodePath;
    size_t iIndex = sNode.find('/');
    sNode = sNode.substr(iIndex + 1);
    iIndex = sNode.find('/');
    std::vector<std::string> vecResult;
    while (std::string::npos != iIndex)
    {
        std::string sPath = sNode.substr(0, iIndex);
        vecResult.push_back(sPath);
        sNode = sNode.substr(iIndex + 1);
        iIndex = sNode.find('/');
    }
    for (auto &ii : vecResult)
    {
        m_pElement = m_pElement->FirstChildElement(ii.c_str());
        if (nullptr == m_pElement)
        {
            ZLOG << "The node is not exist" << sNodePath;
            m_pElement = m_oXMLFile.RootElement();
            return false;
        }
    }

    iIndex = sNode.find('[');
    if (std::string::npos != iIndex)
    {
        std::string sEndNodeCount = sNode.substr(iIndex + 1, sNode.find(']') - iIndex - 1);
        std::string sEndNode = sNode.substr(0, iIndex);
        m_pElement = m_pElement->FirstChildElement(sEndNode.c_str());
        for (int i = 0; i < std::stoi(sEndNodeCount); ++i)
        {
            m_pElement = m_pElement->NextSiblingElement(sEndNode.c_str());
        }
    }
    else
    {
        m_pElement = m_pElement->FirstChildElement(sNode.c_str());
    }
    return true;
}

bool LoadConfigre::GetElementValue(const std::string &sNodePath, std::string &sValue)
{
    if (!ParseFilePath(sNodePath))
    {
        ZLOG << "The node path is not exist, the node is " << sNodePath;
        return false;
    }
    sValue = m_pElement->GetText();
    m_pElement = m_oXMLFile.RootElement();
    return true;
}
int32_t LoadConfigre::GetCountBrotherElement(const std::string &sNodePath)
{
    if (!ParseFilePath(sNodePath))
    {
        ZLOG << "The node path is not exist, the node is " << sNodePath;
        return false;
    }
    std::string sEndPath = sNodePath.substr(sNodePath.find_last_of('/') + 1, std::string::npos);
    if (std::string::npos != sEndPath.find('['))
    {
        ZLOG << "The node path is right style";
        m_pElement = m_oXMLFile.RootElement();
        return 0;
    }
    int iCount = 0;
    while (nullptr != m_pElement)
    {
        m_pElement = m_pElement->NextSiblingElement(sEndPath.c_str());
        iCount++;
    }
    m_pElement = m_oXMLFile.RootElement();
    return iCount;
}
