#ifndef TOOLS_RPS_H
#define TOOLS_RPS_H

#include <../../3rdparty/eigen-3.4.0/Eigen/Dense>

#include <../../3rdparty/eigen-3.4.0/unsupported/Eigen/CXX11/Tensor>

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

#endif  // TOOLS_RPS_H
