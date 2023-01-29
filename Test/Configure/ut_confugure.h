//
// Created by wei on 2023/1/29.
//

#ifndef NEWTRAVEL_UT_CONFUGURE_H
#define NEWTRAVEL_UT_CONFUGURE_H

#include "Configure/configure_base.h"
#include "gtest/gtest.h"

class TestConfigure : public ::testing::Test
{
public:
    TestConfigure();
    ~TestConfigure() override = default;
    std::shared_ptr<LoadConfigre> m_pLoadConfigure;
};

TestConfigure::TestConfigure()
{
    m_pLoadConfigure = std::make_shared<LoadConfigre>();
}

TEST_F(TestConfigure,ReadFile)
{
    std::string sFilePath = "/home/wei/Documents/NewTravel/Test/Configure/TestFile.xml";
    EXPECT_TRUE(m_pLoadConfigure->ReadXML(sFilePath));
    std::string sResult;
    std::string sNodePath = "/TaskMsg/TaskMsgName";
    EXPECT_TRUE(m_pLoadConfigure->GetElementValue(sNodePath,sResult));
    std::cout << "sResult " << sResult << std::endl;
}

#endif // NEWTRAVEL_UT_CONFUGURE_H
