#include "Barycentric.h"
#include "Vector2D.h"

BarycentricConverter::BarycentricConverter(double A[2], double B[2], double C[2])
{
	A_[0] = A[0];
	A_[1] = A[1];
	B_[0] = B[0];
	B_[1] = B[1];
	C_[0] = C[0];
	C_[1] = C[1];
	Sub2D(B, A, A_to_B);
	Sub2D(C, A, A_to_C);
	Sub2D(C, B, B_to_C);
	GetNormal2D(A_to_B, AB_norm);
	GetNormal2D(A_to_C, AC_norm);
	GetNormal2D(B_to_C, BC_norm);
	A_dot_BC_norm = Dot2D(BC_norm, A);
	B_dot_BC_norm = Dot2D(BC_norm, B);
	AB_dot_BC_norm = Dot2D(BC_norm, A_to_B);
	AC_dot_BC_norm = Dot2D(BC_norm, A_to_C);
}

double* BarycentricConverter::ToBarycentric(double cartesian[2], double barycentric[3])
{
	barycentric[0] = (Dot2D(BC_norm, cartesian) - B_dot_BC_norm) / -AB_dot_BC_norm;
	barycentric[1] = (Dot2D(AC_norm, cartesian) - A_dot_BC_norm) /  AB_dot_BC_norm;
	barycentric[2] = (Dot2D(AB_norm, cartesian) - A_dot_BC_norm) / -AC_dot_BC_norm;
	return barycentric;
}

double* BarycentricConverter::ToCartesian(double barycentric[3], double cartesian[2])
{
	cartesian[0] = barycentric[0] * A_[0] + barycentric[1] * B_[0] + barycentric[2] * C_[0];
	cartesian[1] = barycentric[0] * A_[1] + barycentric[1] * B_[1] + barycentric[2] * C_[1];
	return cartesian;
}