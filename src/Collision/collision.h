//
// Created by szymon on 22.04.22.
//

#ifndef NOVOMATIC_COLLISION_H
#define NOVOMATIC_COLLISION_H

#include <array>
#include <algorithm>
#include <iostream>

struct vec2{
    float x,y;
};


class Segment{
public:
    vec2 a;
    vec2 b;
    float factor_a;
    float factor_b;

   Segment(vec2 a, vec2 b) : a(a), b(b) {
       if( a.x == b.x ){
           std::cout<<"eq";
           this->b.x += 0.0000001;
       }
       calculateFactors();
   }

   void calculateFactors(){
       std::cout << a.x  << " b: " << b.x << "\n";
       factor_a = (a.y - b.y) / (a.x - b.x);
       factor_b = a.y - a.x * factor_a;
   }

    float max_x() const {
        return std::max(a.x, b.x);
    }

    float max_y() const {
     return std::max(a.y, b.y);
    }

    float min_x() const {
        return std::min(a.x, b.x);
    }

    float min_y() const {
        return std::min(a.y, b.y);;
    }
};

struct triangle{
    std::array<vec2,3> points;
};

float dotProduct(vec2 vector1, vec2 vector2);
bool isPointInsideTriangle(const triangle  & tri,const vec2  & point);
vec2 getSegmentCrossPoint(const Segment  & first ,const Segment  & second);
bool isSegmentsCrossing(const Segment  & first ,const Segment  & second );
bool isColliding(const triangle & first ,const triangle  & second);
bool isSegmentCrossingWithCircle(const vec2  & circleCenter, const float circleRadius, const Segment & segment);
bool isCircleCollidingWithRectangle(const vec2 & circleCenter, const float r , const vec2 & A, const vec2 & B, const vec2 & C, const vec2 & D);

#endif //NOVOMATIC_COLLISION_H
