//
// Created by andrzej on 27.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_BASE_64_TEST_HPP
#define BRAM_CONTROLLER_PROJECT_BASE_64_TEST_HPP


#include <gtest/gtest.h>
#include <base64/base_64.hpp>

class Base64Test : public ::testing::Test {
public:
    Base64 base64;

    Base64Test();

    virtual ~Base64Test();

    void SetUp() override;

    void TearDown() override;
};


#endif //BRAM_CONTROLLER_PROJECT_BASE_64_TEST_HPP
