#pragma once
#include <../../3rdparty/eigen-3.4.0/Eigen/Dense>

#include <../../3rdparty/eigen-3.4.0/unsupported/Eigen/CXX11/Tensor>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Tensor;

typedef VectorXd vec;
typedef MatrixXd mat;
typedef Tensor<double, 3> cube;