

#ifndef SOFTBREEZE_MATH_UTILITY_H
#define SOFTBREEZE_MATH_UTILITY_H

#include <math.h>



softbreeze_namespace_beg

inline float AngleToRadian(float angle);


bool CohenSutherlandClip(int left, int right, int top, int buttom, OUTPUT int& beginX, OUTPUT int& beginY, OUTPUT int& endX, OUTPUT int& endY);

void BuildXYZRotationMatrix4(float thetaX, float thetaY, float thetaZ, OUTPUT Matrix4& matrix);


softbreeze_namespace_end

#endif

