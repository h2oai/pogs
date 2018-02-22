#pragma once

#ifdef WIN32
#define tsvd_export __declspec(dllexport)
#else
#define tsvd_export
#endif

#include "../data/matrix.cuh"

namespace tsvd


{

	extern "C"
	{
		struct params
		{
			int X_n;
			int X_m;
			int k;
			const char* algorithm;
			int n_iter;
			int random_state;
			float tol;
			int verbose;
			int gpu_id;
		};

		/**
		 *
		 * \param 		  	_X
		 * \param [in,out]	_Q
		 * \param [in,out]	_w
		 * \param [in,out]  _U
		 * \param [out] 	_explained_variance
		 * \param[out]		_explained_variance_ratio
		 * \param 		  	_param
		 */

		tsvd_export void truncated_svd(const double * _X, double * _Q, double * _w, double* _U, double* _explained_variance, double* _explained_variance_ratio, params _param);

	}

	template<typename T>
	void cusolver_tsvd(Matrix<T> &X, double* _Q, double* _w, double* _U, double* _explained_variance, double* _explained_variance_ratio, params _param);

	template<typename T>
	void power_tsvd(Matrix<T> &X, double* _Q, double* _w, double* _U, double* _explained_variance, double* _explained_variance_ratio, params _param);

	template<typename T>
	tsvd_export void truncated_svd_matrix(Matrix<T> &X, double* _Q, double* _w, double* _U, double* _explained_variance, double* _explained_variance_ratio, params _param);

	void outer_product(Matrix<float>& A, float eigen_value, const Matrix<float>& eigen_vector, const Matrix<float>& eigen_vector_transpose, DeviceContext& context);
	void outer_product(Matrix<double>& A, float eigen_value, const Matrix<double>& eigen_vector, const Matrix<double>& eigen_vector_transpose, DeviceContext& context);

}
