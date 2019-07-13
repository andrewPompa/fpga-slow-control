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
    uint expected = (0x33 << 24) + (0x32 << 16) + (0x31 << 8) + 0x30;
    Base64 base64;
    std::shared_ptr<uint> decoded = base64.decodeWords(encoded);
    EXPECT_EQ(expected, decoded.get()[0]);
}

TEST_F(Base64Test, decodeTest2) {
    std::string encoded = "Y2hvcmF6eXRvcnBlZGE=";
    uint expected[] = {
            (0x63 << 24) + (0x68 << 16) + (0x6F << 8) + 0x72,
            (0x61 << 24) + (0x7A << 16) + (0x79 << 8) + 0x74,
            (0x6F << 24) + (0x72 << 16) + (0x70 << 8) + 0x65,
            (0x64 << 8) + 0x61,
    };
    Base64 base64;
    std::shared_ptr<uint> decoded = base64.decodeWords(encoded);
    EXPECT_EQ(expected[0], decoded.get()[0]);
    EXPECT_EQ(expected[1], decoded.get()[1]);
    EXPECT_EQ(expected[2], decoded.get()[2]);
    EXPECT_EQ(expected[3], decoded.get()[3]);
}

TEST_F(Base64Test, decodeTest3) {
    std::string encoded = "QQ==";
    uint expected = 0x41;
    Base64 base64;
    std::shared_ptr<uint> decoded = base64.decodeWords(encoded);
    EXPECT_EQ(expected, decoded.get()[0]);
}