#include "gtest/gtest.h"
#include "../src/Collision/collision.h"

#define EPSILON 0.00001

TEST(EX1, Segment)
{
    Segment segment1(vec2{1,1}, vec2{2,2});
    Segment segment2(vec2{0,8.87}, vec2{15,0.87});
    Segment segment3(vec2{0,-99}, vec2{2,99});

    EXPECT_NEAR(1,segment1.factor_a,EPSILON);
    EXPECT_NEAR(0,segment1.factor_b,EPSILON);

    EXPECT_NEAR(-0.533333333,segment2.factor_a,EPSILON);
    EXPECT_NEAR(8.87,segment2.factor_b,EPSILON);

    EXPECT_NEAR(99,segment3.factor_a,EPSILON);
    EXPECT_NEAR(-99,segment3.factor_b,EPSILON);
}

TEST(EX1, getSegmentCrossPoint)
{
    Segment segment1(vec2{0,3}, vec2{10,8});
    Segment segment2(vec2{0,-2}, vec2{10, 13});

    vec2 result = getSegmentCrossPoint(segment1, segment2);

    EXPECT_NEAR(5,result.x,EPSILON);
    EXPECT_NEAR(5.5,result.y,EPSILON);


}

TEST(EX1, isSegmentsCrossing)
{
    Segment segment1(vec2{1,1}, vec2{20,20});
    Segment segment2(vec2{0,8.87}, vec2{15,0.87});

    ASSERT_EQ(true, isSegmentsCrossing(segment1,segment2));

}

TEST(EX1, isPointInsideTriangle)
{
    triangle A;
    A.points[0] = {0,0};
    A.points[1] = {0,10};
    A.points[2] = {10,0};

    triangle B;
    B.points[0] = {-1,1};
    B.points[1] = {-2,2};
    B.points[2] = {-4,3};

//    ASSERT_EQ(true, isPointInsideTriangle(A, {1,1}));
//    ASSERT_EQ(false, isPointInsideTriangle(A, {-1,1}));
    ASSERT_EQ(true, isPointInsideTriangle(B, {-2.1,2}));
    ASSERT_EQ(false, isPointInsideTriangle(B, {-2,2.1}));

}



TEST(EX1, isColliding)
{

    triangle A;
    A.points[0] = {0,0};
    A.points[1] = {0.1,10};
    A.points[2] = {10,0};

    triangle B;
    B.points[0] = {-1,1};
    B.points[1] = {-2,2};
    B.points[2] = {-4,3};

    triangle C;
    C.points[0] = {-1,1};
    C.points[1] = {-2,2};
    C.points[2] = {20,3};

    triangle D;
    D.points[0] = {1,1};
    D.points[1] = {2,2};
    D.points[2] = {4,3};

    triangle E;
    E.points[0] = {3,1};
    E.points[1] = {2,1};
    E.points[2] = {20,2};


    ASSERT_EQ(false, isColliding(A,B));
    ASSERT_EQ(false, isColliding(A,B));
    ASSERT_EQ(true, isColliding(A,C));
    ASSERT_EQ(true, isColliding(A,D));
    ASSERT_EQ(true, isColliding(A,E));


}
