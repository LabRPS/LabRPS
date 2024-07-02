#ifndef GENERAL_TOOL_RPS_H
#define GENERAL_TOOL_RPS_H

#include <Eigen/Eigen>
#include <unsupported/Eigen/CXX11/Tensor>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Tensor;

using Eigen::MatrixXcd;
using Eigen::VectorXcd;

typedef VectorXd vec;
typedef MatrixXd mat;
typedef Tensor<double, 3> cube;

typedef VectorXcd cx_vec;
typedef MatrixXcd cx_mat;
typedef Tensor<std::complex<double>, 3> cx_cube;

#endif  // WL_RPS_H