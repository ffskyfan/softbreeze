
#include "../softbreeze.h"

#include <limits>

#include "matrix4.h"


#include "utility.h"



softbreeze_namespace_beg


void BuildXYZRotationMatrix4(float thetaX, float thetaY, float thetaZ, Matrix4& OUTPUT matrix)
{

	// this helper function takes a set if euler angles and computes
	// a rotation matrix from them, usefull for object and camera
	// work, also  we will do a little testing in the function to determine
	// the rotations that need to be performed, since there's no
	// reason to perform extra matrix multiplies if the angles are
	// zero!

	Matrix4 mx(matrix4_zero);
	Matrix4 my(matrix4_zero); 
	Matrix4 mz(matrix4_zero); 

	float sinThetA = 0, cosThetA = 0;   // used to initialize matrices
	int rotSeq = 0;                  // 1 for x, 2 for y, 4 for z

	// step 0: fill in with identity matrix
	matrix = matrix4_identity;

	float epsilon = std::numeric_limits<float>::epsilon();

	

	// step 1: based on zero and non-zero rotation angles, determine
	// rotation sequence
	if(fabs(thetaX) > epsilon) // x
		rotSeq = rotSeq | 1;

	if(fabs(thetaY) > epsilon) // y
		rotSeq = rotSeq | 2;

	if(fabs(thetaZ) > epsilon) // z
		rotSeq = rotSeq | 4;

	// now case on sequence
	switch(rotSeq) {
	case 0: // no rotation
	{
		// what a waste!
		return;
	} break;

	case 1: // x rotation
	{
		// compute the sine and cosine of the angle
		cosThetA = cos(thetaX);
		sinThetA = sin(thetaX);

		// set the matrix up 
		mx = Matrix4(1, 0, 0, 0,
			0, cosThetA, sinThetA, 0,
			0, -sinThetA, cosThetA, 0,
			0, 0, 0, 1);

		// that's it, copy to output matrix
		matrix = mx;
		return;

	} break;

	case 2: // y rotation
	{
		// compute the sine and cosine of the angle
		cosThetA = cos(thetaY);
		sinThetA = sin(thetaY);

		// set the matrix up 
		my = Matrix4(cosThetA, 0, -sinThetA, 0,
			0, 1, 0, 0,
			sinThetA, 0, cosThetA, 0,
			0, 0, 0, 1);

		// that's it, copy to output matrix
		matrix = my;
		return;

	} break;

	case 3: // xy rotation
	{
		// compute the sine and cosine of the angle for x
		cosThetA = cos(thetaX);
		sinThetA = sin(thetaX);

		// set the matrix up 
		mx = Matrix4(1, 0, 0, 0,
			0, cosThetA, sinThetA, 0,
			0, -sinThetA, cosThetA, 0,
			0, 0, 0, 1);

		// compute the sine and cosine of the angle for y
		cosThetA = cos(thetaY);
		sinThetA = sin(thetaY);

		// set the matrix up 
		// set the matrix up 
		my = Matrix4(cosThetA, 0, -sinThetA, 0,
			0, 1, 0, 0,
			sinThetA, 0, cosThetA, 0,
			0, 0, 0, 1);

		// concatenate matrices 
		//matrix = mx*my;
		return;

	} break;

	case 4: // z rotation
	{
		// compute the sine and cosine of the angle
		cosThetA = cos(thetaZ);
		sinThetA = sin(thetaZ);

		// set the matrix up 
		mz = Matrix4(cosThetA, sinThetA, 0, 0,
			-sinThetA, cosThetA, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);


		// that's it, copy to output matrix
		matrix = mz;
		return;

	} break;

	case 5: // xz rotation
	{
		// compute the sine and cosine of the angle x
		cosThetA = cos(thetaX);
		sinThetA = sin(thetaX);
		mx = Matrix4(1, 0, 0, 0,
			0, cosThetA, sinThetA, 0,
			0, -sinThetA, cosThetA, 0,
			0, 0, 0, 1);

		// compute the sine and cosine of the angle z
		cosThetA = cos(thetaZ);
		sinThetA = sin(thetaZ);
		mz = Matrix4(cosThetA, sinThetA, 0, 0,
			-sinThetA, cosThetA, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		// concatenate matrices 
		//matrix = mx*mz;
		return;

	} break;

	case 6: // yz rotation
	{
		// compute the sine and cosine of the angle y
		cosThetA = cos(thetaY);
		sinThetA = sin(thetaY);
		my = Matrix4(cosThetA, 0, -sinThetA, 0,
			0, 1, 0, 0,
			sinThetA, 0, cosThetA, 0,
			0, 0, 0, 1);


		// compute the sine and cosine of the angle z
		cosThetA = cos(thetaZ);
		sinThetA = sin(thetaZ);
		mz = Matrix4(cosThetA, sinThetA, 0, 0,
			-sinThetA, cosThetA, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		// concatenate matrices 
		//matrix = my*mz;
		return;

	} break;

	case 7: // xyz rotation
	{
		// compute the sine and cosine of the angle x
		cosThetA = cos(thetaX);
		sinThetA = sin(thetaX);
		mx = Matrix4(1, 0, 0, 0,
			0, cosThetA, sinThetA, 0,
			0, -sinThetA, cosThetA, 0,
			0, 0, 0, 1);

		// compute the sine and cosine of the angle y
		cosThetA = cos(thetaY);
		sinThetA = sin(thetaY);
		my = Matrix4(cosThetA, 0, -sinThetA, 0,
			0, 1, 0, 0,
			sinThetA, 0, cosThetA, 0,
			0, 0, 0, 1);


		// compute the sine and cosine of the angle z
		cosThetA = cos(thetaZ);
		sinThetA = sin(thetaZ);
		mz = Matrix4(cosThetA, sinThetA, 0, 0,
			-sinThetA, cosThetA, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		// concatenate matrices, watch order!
		matrix = mx*my;
		//matrix = matrix*mz;
	} break;

	default: break;

	} // end switch


}


softbreeze_namespace_end

