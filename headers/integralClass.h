#pragma once

#include <iostream>
#include <functional>
#include <cmath>
#include <iomanip>
#include "randomGeneration.h"

class Integral
{
private:

    std::pair<double,double> m_bounds { } ; //First element is the lower bound , second is the upper bound
    int m_numberOfIntervals { } ;
    double m_sizeofBoundsInterval { } ;
    double m_valueOfIntegral { } ;
    double m_errorMargin { } ;
    double m_mean { } ;
    double m_variance { } ;
    double m_standardError { } ;
    double m_sigma1 { } ;
    double m_sigma2 { } ;
  
public:

    double func( double x ){ return std::exp(x) ; }

    void getBounds(){
        std::cout << "Lower bound : " ;
        std::cin >> m_bounds.first ;
        std::cout << "Upper bound : " ;
        std::cin >> m_bounds.second ;

        if( m_bounds.first > m_bounds.second ){
            std::cout << "It is required that lowerBound<upperBound !\n" ;
            this->getBounds() ;
        }
    }
    
    void getNumberOfIntervals(){
        std::cout << "Give the number of intervals (higher the number -> higher accuracy) : " ;
        std::cin >> m_numberOfIntervals ;

        if( m_numberOfIntervals <= 0 ){
            std::cout << "Number of intervals has to be > 0 !\n" ;
            this->getNumberOfIntervals() ;
        }
    } ;

    void setSizeOfIntervals(){ m_sizeofBoundsInterval = (m_bounds.second-m_bounds.first)/m_numberOfIntervals ; }
    
    void calculateIntegralAproximationMonoThreaded() 
    {
        for(int index { };index < m_numberOfIntervals;++ index)
        {
            double valueOfFunc { func(prng::getReal(m_sizeofBoundsInterval*index,m_sizeofBoundsInterval*(index+1))) } ; 
            m_valueOfIntegral += valueOfFunc*(m_sizeofBoundsInterval*(index+1)-m_sizeofBoundsInterval*index) ;
            m_sigma1 += valueOfFunc ;
            m_sigma2 += valueOfFunc*valueOfFunc ;
        }
    }

    void calculateMean(){ m_mean = m_sigma1/m_numberOfIntervals ; }
    void calculateVariance(){ m_variance = (m_sigma2/m_numberOfIntervals) - m_mean*m_mean ; }
    void calculateStandardError(){ m_standardError = (m_bounds.second-m_bounds.first)*std::sqrt(m_variance/m_numberOfIntervals) ; }
    void calculateMarginOfError95(){ m_errorMargin = 1.96 * m_standardError ;}

    void printValueOfIntegral(){ std::cout<<"Value of Integral : "<<std::setprecision(15)<<m_valueOfIntegral<<'\n' ; }
    void printErrorMargin(){ std::cout<<"Error margin(95% confidence) : "<<std::setprecision(15)<<m_errorMargin<<'\n' ; }

    void execute(){
        this->getBounds();
        this->getNumberOfIntervals();
        this->setSizeOfIntervals();
        this->calculateIntegralAproximationMonoThreaded();
        this->calculateMean();
        this->calculateVariance();
        this->calculateStandardError();
        this->calculateMarginOfError95();
        this->printValueOfIntegral();
        this->printErrorMargin();
    }
};
