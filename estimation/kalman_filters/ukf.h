#pragma once

#ifndef UKF_H
#define UKF_H

#include <eigen3/Eigen/Dense>
#include <cmath>

class UKF {
public:
  /**
   * Constructor
   */
    UKF();

  /**
   * Destructor
   */
    virtual ~UKF();

  /**
   * Init Initializes Unscented Kalman filter
   */
    void Init();

    void GenerateSigmaPoints(const Eigen::VectorXd& x,const Eigen::MatrixXd& P, Eigen::MatrixXd& Xsig_aug);

    void SigmaPointPrediction(const double delta_t, Eigen::MatrixXd& Xsig_pred);

    void PredictMeanAndCovariance();

    void PredictMeasurement();

    void Predict(const Eigen::VectorXd& x,const Eigen::MatrixXd& P, const double dt);

    void Update(const Eigen::VectorXd& z, Eigen::VectorXd& x, Eigen::MatrixXd& P);

private:
    int n_x_;
    int n_z_;
    int n_x_aug_;
    int n_sig_aug_;
    double lambda_;
    Eigen::VectorXd weights;//n_sig_aug

    Eigen::VectorXd x_aug_;//augmented mean vector created from input state
    Eigen::MatrixXd P_aug_;//aug cov, nxaug*nxaug
    Eigen::MatrixXd A_aug_;

    Eigen::MatrixXd Xsig_aug_;//aug sig points,nxaug*nsigaug
    Eigen::MatrixXd Xsig_pred_;//predicted sig points, nx*n_sig_aug
    Eigen::VectorXd x_pred_;//predicted mean state, nx
    Eigen::MatrixXd P_pred_;//predicted cov, nx*nx

    Eigen::MatrixXd Zsig_;//predicted sig pts in meas space
    Eigen::VectorXd z_pred_;//mean predicted measurement
    Eigen::MatrixXd S_;//meas cov S
    Eigen::MatrixXd R_;

    Eigen::MatrixXd Tc_;//cross corelation
    Eigen::MatrixXd K_;
};

#endif  // UKF_H