//
// Created by andrzej on 27.06.19.
//

#include "base_64_test.hpp"

Base64Test::Base64Test() {}

Base64Test::~Base64Test() {

}

void Base64Test::SetUp() {
    Test::SetUp();
}

void Base64Test::TearDown() {
    Test::TearDown();
}


TEST_F(Base64Test, encodeTest) {
    u_char bytes[] = {
            0x30, 0x30, 0x31, 0x31,
            0x32, 0x32, 0x33, 0x33,
            0x41, 0x41, 0x42, 0x42,
            0x43, 0x43, 0x44, 0x44,
            0x34, 0x34, 0x35, 0x35,
            0x36, 0x36, 0x37, 0x37,
            0x45, 0x45, 0x46, 0x46,
            0x41, 0x41, 0x42, 0x42
    };
    std::string encoded = base64.encode(bytes, 32);
    std::string expected = "MDAxMTIyMzNBQUJCQ0NERDQ0NTU2Njc3RUVGRkFBQkI=";
    EXPECT_EQ(encoded == expected, true);
}

TEST_F(Base64Test, decodeTest) {
    std::string encoded = "MzIxMA==";
    u_char expected[] = {0x33, 0x32, 0x31, 0x30};
    Base64 base64;
    std::vector<u_char> decoded = base64.decode(encoded);
    u_char *decodeBytes = &decoded[0];
    EXPECT_EQ(decoded.size(), 4);
    for (int i = 0; i < decoded.size(); ++i) {
        EXPECT_EQ(decodeBytes[i], expected[i]);
    }
}