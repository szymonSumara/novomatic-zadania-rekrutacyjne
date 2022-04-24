//
// Created by szymon on 22.04.22.
//

#include "collision.h"
#include <cmath>
#include <iostream>


float dotProduct(vec2 vector1, vec2 vector2){
    return  vector1.x * vector2.y - vector1.y* vector2.x;
}

bool isPointInsideTriangle(triangle const & tri, vec2 const & point){

    int negativeCount = 0;
    int positiveCount = 0;

    for(int i = 0 ; i < tri.points.size(); i++)
        if(dotProduct(
                { point.x - tri.points[( i+1 )% 3].x ,  point.y - tri.points[( i+1 )% 3].y},
                {  tri.points[i].x - tri.points[( i+1 )% 3].x ,tri.points[i].y -   tri.points[( i+1 )%3].y }
        ) < 0 )
            negativeCount += 1;
        else
            positiveCount += 1 ;

    return !(negativeCount > 0 && positiveCount > 0);
}

vec2 getSegmentCrossPoint(Segment const & first , Segment const & second){
    vec2 result{
            ( first.factor_b - second.factor_b ) / (second.factor_a - first.factor_a),
            result.x * first.factor_a + first.factor_b
    };

    return result;
}

bool isSegmentsCrossing( Segment const & first , Segment const & second ){

    vec2 crossPoint = getSegmentCrossPoint(first, second);

    return ( first.min_x() < crossPoint.x && crossPoint.x < first.max_x() )
           && ( first.min_y() < crossPoint.y && crossPoint.y < first.max_y() )
           && ( second.min_x() < crossPoint.x && crossPoint.x < second.max_x() )
           && ( second.min_y() < crossPoint.y && crossPoint.y < second.max_y() );
}


bool isColliding(triangle const & first ,triangle const & second){


    Segment first_a(first.points[0], first.points[1]);
    Segment first_b(first.points[1], first.points[2]);
    Segment first_c(first.points[2], first.points[0]);

    Segment second_a(second.points[0], second.points[1]);
    Segment second_b(second.points[1], second.points[2]);
    Segment second_c(second.points[2], second.points[0]);

    if(isSegmentsCrossing(first_a, second_a)) return true;
    if(isSegmentsCrossing(first_a, second_b)) return true;
    if(isSegmentsCrossing(first_a, second_c)) return true;

    if(isSegmentsCrossing(first_b, second_a)) return true;
    if(isSegmentsCrossing(first_b, second_b)) return true;
    if(isSegmentsCrossing(first_b, second_c)) return true;

    if(isSegmentsCrossing(first_c, second_a)) return true;
    if(isSegmentsCrossing(first_c, second_b)) return true;
    if(isSegmentsCrossing(first_c, second_c)) return true;

    for( vec2 point : first.points)
        if(isPointInsideTriangle(second,point)) return true;

    for( vec2 point : second.points)
        if(isPointInsideTriangle(first,point)) return true;


    return false;
}

bool isSegmentCrossingWithCircle(const vec2  & circleCenter, const float circleRadius, const Segment & segment){

    float h = circleCenter.x;
    float k = circleCenter.y;
    float r = circleRadius;
    float a = segment.factor_a;
    float b = segment.factor_b;


    float A = 1 + a*a;
    float B = -2*h + 2*a*b - 2*a*k;
    float C = h*h + b*b + k*k - 2 * b * k  - r*r;

    float Delta = B*B - 4*A*C;
    if(Delta < 0 ) return false;

    float x1 = ( -B - sqrt(Delta))/ (2*A);
    float x2 = ( -B + sqrt(Delta))/ (2*A);
    return (segment.min_x() < x1 && x1 < segment.max_x()) || (segment.min_x() < x2 && x2 < segment.max_x());

}

bool isCircleContainPoint(const vec2 & circleCenter, const float r , const vec2 & point){

    float distance = (circleCenter.x - point.x) * (circleCenter.x - point.x) + (circleCenter.y - point.y) * (circleCenter.y - point.y);
    return distance < r * r;

}

bool isCircleCollidingWithRectangle(const vec2 & circleCenter, const float r , const vec2 & A, const vec2 & B, const vec2 & C, const vec2 & D) {

    if(isCircleContainPoint(circleCenter , r, A )) return true;

    triangle first;
    first.points[0] = {A.x,A.y};
    first.points[1] = {B.x,B.y};
    first.points[2] = {C.x,C.y};

    triangle second;
    second.points[0] = {A.x,A.y};
    second.points[1] = {C.x,C.y};
    second.points[2] = {D.x,D.y};

    if( isPointInsideTriangle(first, {circleCenter.x,circleCenter.y})
        || isPointInsideTriangle(second, {circleCenter.x,circleCenter.y}) ){
        return true;
    }

    Segment a({A.x,A.y},{B.x,B.y} );
    Segment b({B.x,B.y},{C.x,C.y} );
    Segment c({C.x,C.y},{D.x,D.y} );
    Segment d({D.x,D.y},{A.x,A.y} );

    if(isSegmentCrossingWithCircle(circleCenter, r,a)) return true;
    if(isSegmentCrossingWithCircle(circleCenter, r,b)) return true;
    if(isSegmentCrossingWithCircle(circleCenter, r,c)) return true;
    if(isSegmentCrossingWithCircle(circleCenter, r,d)) return true;

    return false;
}

