//
// Created by wei on 2023/1/29.
//

#ifndef NEWTRAVEL_CONFIGURE_BASE_H
#define NEWTRAVEL_CONFIGURE_BASE_H

#include "TinyXml2/include/tinyxml2.h"
#include <iostream>
#include <vector>

namespace zl
{
class LoadConfigre
{
public:
    LoadConfigre();
    ~LoadConfigre();
    bool ReadXML(const std::string &sFilePath);
    bool GetElementValue(const std::string &sNodePath, std::string &sValue);
    int32_t GetCountBrotherElement(const std::string &sNodePath);

private:
    bool ParseFilePath(const std::string &sNodePath);

private:
    tinyxml2::XMLDocument m_oXMLFile;
    tinyxml2::XMLElement *m_pElement;
};
}
#endif // NEWTRAVEL_CONFIGURE_BASE_H
