#include <iostream>
#include "ukf.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;

UKF::UKF()
    :n_x_(5)
    ,n_z_(3)
    ,n_x_aug_(n_x_+2)
    ,n_sig_aug_(2*n_x_aug_+1)
    ,lambda_(3-n_x_aug_)
    ,weights(n_sig_aug_)
    ,x_aug_(n_x_aug_)
    ,P_aug_(n_x_aug_,n_x_aug_)
    ,A_aug_(n_x_aug_,n_x_aug_)
    ,Xsig_aug_(n_x_aug_,n_sig_aug_)
    ,Xsig_pred_(n_x_,n_sig_aug_)
    ,x_pred_(n_x_)
    ,P_pred_(n_x_,n_x_)
    ,Zsig_(n_z_,n_sig_aug_)
    ,z_pred_(n_z_)
    ,S_(n_z_,n_z_)
    ,R_(n_z_,n_z_)
    ,Tc_(n_x_,n_z_)
    ,K_(n_x_,n_z_)
{
  Init();
}

UKF::~UKF()
{

}

void UKF::Init() {
    // set weights
    double w0 = lambda_/(lambda_+double(n_x_aug_)), w = 0.5/(lambda_+double(n_x_aug_));
    weights.fill(w);
    weights(0) = w0;
    //cout << "Weights:\n" << weights;

    x_aug_.fill(0.0);
    P_aug_.fill(0.0);
    //A_aug
    Xsig_aug_.fill(0.0);

    // radar measurement noise standard deviation radius in m
    double std_radr = 0.3;
    // radar measurement noise standard deviation angle in rad
    double std_radphi = 0.0175;
    // radar measurement noise standard deviation radius change in m/s
    double std_radrd = 0.1;

    R_.fill(0.0);
    R_(0,0) = std_radr*std_radr;
    R_(1,1) = std_radphi*std_radphi;
    R_(2,2) = std_radrd*std_radrd;
}

void UKF::GenerateSigmaPoints(const Eigen::VectorXd& x,const Eigen::MatrixXd& P, Eigen::MatrixXd& Xsig_aug)
{

  // Process noise standard deviation longitudinal acceleration in m/s^2
  double std_a = 0.2;

  // Process noise standard deviation yaw acceleration in rad/s^2
  double std_yawdd = 0.2;

  // create augmented mean state
  x_aug_.head(n_x_) = x;
  x_aug_[n_x_] = 0;
  x_aug_[n_x_+1] = 0;

  // create augmented covariance matrix
  P_aug_.topLeftCorner(n_x_,n_x_) = P;
  P_aug_(n_x_,n_x_) = std_a*std_a;
  P_aug_(n_x_+1,n_x_+1) = std_yawdd*std_yawdd;

  // create square root matrix
  A_aug_ = P_aug_.llt().matrixL();

  // create augmented sigma points
  double coef = sqrt(lambda_ + n_x_aug_);
  Xsig_aug.col(0) = x_aug_;
  for(int j=0; j<n_x_aug_; ++j){
    Xsig_aug.col(j+1)          = x_aug_ + coef*A_aug_.col(j);
    Xsig_aug.col(j+1+n_x_aug_) = x_aug_ - coef*A_aug_.col(j);
  }

  // print result
  //std::cout << "Xsig_aug = " << std::endl << Xsig_aug << std::endl;

}

void UKF::SigmaPointPrediction(const double delta_t, Eigen::MatrixXd& Xsig_pred)
{
  //check Xsig_pred size: n_x * n_sig_aug_


  // predict sigma points
  VectorXd diff_vec = VectorXd(n_x_), noise_vec = VectorXd(n_x_);
  
  for(int i=0; i<n_sig_aug_;++i){
    double v = Xsig_aug_(2,i), phi = Xsig_aug_(3,i), phi_dot = Xsig_aug_(4,i),
           nu_a = Xsig_aug_(5,i), nu_phi = Xsig_aug_(6,i);

    noise_vec(0) = 0.5*delta_t*delta_t*cos(phi)*nu_a;
    noise_vec(1) = 0.5*delta_t*delta_t*sin(phi)*nu_a;
    noise_vec(2) = delta_t*nu_a;
    noise_vec(3) = 0.5*delta_t*delta_t*nu_phi;
    noise_vec(4) = delta_t*nu_phi;

    diff_vec(0) = phi_dot!=0 ? (sin(phi+phi_dot*delta_t)-sin(phi))*v/phi_dot : v*cos(phi)*delta_t;
    diff_vec(1) = phi_dot!=0 ? (cos(phi)-cos(phi+phi_dot*delta_t))*v/phi_dot : v*cos(phi)*delta_t;
    diff_vec(2) = 0;
    diff_vec(3) = phi_dot*delta_t;
    diff_vec(4) = 0;

    Xsig_pred.col(i) = Xsig_aug_.col(i).head(n_x_) + diff_vec + noise_vec;
  }

  // print result
  //std::cout << "Xsig_pred = " << std::endl << Xsig_pred << std::endl;
}

void UKF::PredictMeanAndCovariance()
{
    // check x_out size: n_x

    // predict state mean
    x_pred_.fill(0.0);
    for(int i =0; i<n_sig_aug_; ++i){
        x_pred_ += weights(i)*Xsig_pred_.col(i);
    }

    // predict state covariance matrixi
    P_pred_.fill(0.0);
    for(int i=0; i<n_sig_aug_; ++i){
        VectorXd tmp = Xsig_pred_.col(i) - x_pred_;
        if (tmp(3)> M_PI) tmp(3)-=2.*M_PI;
        if (tmp(3)<-M_PI) tmp(3)+=2.*M_PI;
        P_pred_ += weights(i) * tmp * tmp.transpose();
    }

  // print result
//   std::cout << "Predicted state" << std::endl;
//   std::cout << x_pred_ << std::endl;
//   std::cout << "Predicted covariance matrix" << std::endl;
//   std::cout << P_pred_ << std::endl;

}

void UKF::PredictMeasurement()
{
    Zsig_.fill(0.0);

    // transform predicted sigma points into measurement space
    for(int i=0; i<n_sig_aug_; ++i){
      double px = Xsig_pred_(0,i), py = Xsig_pred_(1,i), v= Xsig_pred_(2,i),
             phi = Xsig_pred_(3,i), phi_dot = Xsig_pred_(4,i);
      Zsig_(0,i) = sqrt(px*px+py*py);//rho
      Zsig_(1,i) = atan2(py,px);//phi
      Zsig_(2,i) = Zsig_(0,i)==0? 0 : (px*v*cos(phi)+py*v*sin(phi))/Zsig_(0,i);//rho dot
    }
    
    // calculate mean predicted measurement
    z_pred_.fill(0.0);
    for (int i=0; i<n_sig_aug_; ++i){
      z_pred_ += weights(i)*Zsig_.col(i);
    }
    
    // calculate innovation covariance matrix S
    S_.fill(0.0);
    for(int i=0; i<n_sig_aug_; ++i){
      VectorXd tmp = Zsig_.col(i)-z_pred_;
      S_ += weights(i)*tmp*tmp.transpose();
    }
    S_ += R_;


    // print result
    //std::cout << "z_pred: " << std::endl << z_pred_ << std::endl;
    //std::cout << "S: " << std::endl << S_ << std::endl;
}

void UKF::Predict(const Eigen::VectorXd& x,const Eigen::MatrixXd& P, const double dt)
{
    GenerateSigmaPoints(x,P,this->Xsig_aug_);
    SigmaPointPrediction(dt, this->Xsig_pred_);
    PredictMeanAndCovariance();
    PredictMeasurement();
}

void UKF::Update(const Eigen::VectorXd& z, Eigen::VectorXd& x, Eigen::MatrixXd& P)
{
  // calculate cross correlation matrix
  Tc_.fill(0.0);
  for(int i=0; i<n_sig_aug_; ++i){
    MatrixXd tmp = MatrixXd(n_x_,n_z_);
    tmp = (Xsig_pred_.col(i)-x_pred_)*(Zsig_.col(i)-z_pred_).transpose();
    Tc_ += weights(i)*tmp;
  }

  // calculate Kalman gain K;
  K_ = Tc_*S_.inverse();//n_x*n_z

  // update state mean and covariance matrix
  x = x_pred_ + K_*(z-z_pred_);
  P = P_pred_ - K_*S_*K_.transpose();

  // print result
  //std::cout << "Updated state x: " << std::endl << x << std::endl;
  //std::cout << "Updated state covariance P: " << std::endl << P << std::endl;

}