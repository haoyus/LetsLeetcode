#include <eigen3/Eigen/Dense>
#include <cmath>
#include "ukf.h"
#include "../utility/timer.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

//g++ main.cpp ukf.cpp -o main

int main() {

    // Create a UKF instance
    UKF ukf;

    // set example state
    VectorXd x(5);// = VectorXd(5);
    x <<   5.7441,
           1.3800,
           2.2049,
           0.5015,
           0.3528;

    // create example covariance matrix
    MatrixXd P(5,5);// = MatrixXd(5, 5);
    P <<     0.0043,   -0.0013,    0.0030,   -0.0022,   -0.0020,
            -0.0013,    0.0077,    0.0011,    0.0071,    0.0060,
             0.0030,    0.0011,    0.0054,    0.0007,    0.0008,
            -0.0022,    0.0071,    0.0007,    0.0098,    0.0100,
            -0.0020,    0.0060,    0.0008,    0.0100,    0.0123;

      VectorXd z(3);// = VectorXd(3);
    z <<
       5.9214,   // rho in m
       0.2187,   // phi in rad
       2.0062;   // rho_dot in m/s

    MatrixXd Xsig_aug = MatrixXd(7,15), Xsig_pred = MatrixXd(5,15);
    
    for(int i=0; i<20; ++i){
{ SimpleTimer t;
    ukf.Predict(x,P,0.1);
    ukf.Update(z,x,P);
    //ukf.GetNIS(z);
}
    }

    std::cout << "final x:\n" << x << std::endl;

    std::cout << "NIS: " << ukf.GetNIS(z) << std::endl;
    return 0;
}