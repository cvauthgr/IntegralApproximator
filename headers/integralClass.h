#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include "randomGeneration.h"

class Integral
{
private:

    std::pair<double,double> m_bounds { } ;
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
        do{
            std::cout << "Lower bound : " ;
            std::cin >> m_bounds.first ;
            if( std::cin.fail() ){
                std::cout << "Invalid input!\n" ;
                std::cin.clear() ;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n') ;
                continue ;
            }
            std::cout << "Upper bound : " ;
            std::cin >> m_bounds.second ;
            if( std::cin.fail() || m_bounds.first > m_bounds.second ){
                std::cout << "It is required that lowerBound<upperBound !\n" ;
                std::cin.clear() ;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n') ;
            }
        }while( m_bounds.first > m_bounds.second || std::cin.fail() ) ;
    }

    void getNumberOfIntervals(){
        do{
            std::cout << "Give the number of intervals (higher the number -> higher accuracy) : " ;
            std::cin >> m_numberOfIntervals ;
            if( m_numberOfIntervals <= 0 || std::cin.fail() ){
                std::cout << "Number of intervals has to be > 0 !\n" ;
                std::cin.clear() ;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n') ;
            }
        }while( m_numberOfIntervals <= 0 || std::cin.fail() ) ;
    }

    void setSizeOfIntervals(){ m_sizeofBoundsInterval = (m_bounds.second-m_bounds.first)/m_numberOfIntervals ; }

    void calculateIntegralAproximationMonoThreaded(){
        for(int index { } ; index < m_numberOfIntervals ; ++index){
            double valueOfFunc { func(prng::getReal(m_bounds.first + m_sizeofBoundsInterval*index, m_bounds.first + m_sizeofBoundsInterval*(index+1))) } ;
            m_valueOfIntegral += valueOfFunc*(m_sizeofBoundsInterval*(index+1)-m_sizeofBoundsInterval*index) ;
            m_sigma1 += valueOfFunc ;
            m_sigma2 += valueOfFunc*valueOfFunc ;
        }
    }

    void calculateMean(){ m_mean = m_sigma1/m_numberOfIntervals ; }
    void calculateVariance(){ m_variance = (m_sigma2/m_numberOfIntervals) - m_mean*m_mean ; }
    void calculateStandardError(){ m_standardError = (m_bounds.second-m_bounds.first)*std::sqrt(m_variance/m_numberOfIntervals) ; }
    void calculateMarginOfError95(){ m_errorMargin = 1.96 * m_standardError ; }

    void printValueOfIntegral(){ std::cout << "Value of Integral : " << std::setprecision(15) << m_valueOfIntegral << '\n' ; }
    void printErrorMargin(){ std::cout << "Error margin(95% confidence) : " << std::setprecision(15) << m_errorMargin << '\n' ; }

    void execute(){
        getBounds() ;
        getNumberOfIntervals() ;
        setSizeOfIntervals() ;
        calculateIntegralAproximationMonoThreaded() ;
        calculateMean() ;
        calculateVariance() ;
        calculateStandardError() ;
        calculateMarginOfError95() ;
        printValueOfIntegral() ;
        printErrorMargin() ;
    }
} ;
