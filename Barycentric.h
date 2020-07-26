class BarycentricConverter
{
public:
	BarycentricConverter(double A[2], double B[2], double C[2]);
	double* ToBarycentric(double cartesian[2], double barycentric[3]);
	double* ToCartesian(double barycentric[3], double cartesian[2]);
private:
	double A_[2], B_[2], C_[2];
	double A_to_B[2], A_to_C[2], B_to_C[2];
	double AB_norm[2], AC_norm[2], BC_norm[2];
	double A_dot_BC_norm, B_dot_BC_norm;
	double AB_dot_BC_norm, AC_dot_BC_norm;
};