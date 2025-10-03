#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>

class TestTriangles : public ::testing::Test
{
protected:
    
    void SetUp() {
      
    }
    void TearDown() {
      
    }
};

TEST_F(TestTriangles, Functions) {
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}