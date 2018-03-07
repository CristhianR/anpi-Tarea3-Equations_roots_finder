/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: Pablo Alvarado
 * @Date  : 10.02.2018
 */

#include <cmath>
#include <limits>
#include <functional>

#include "Exception.hpp"

#ifndef ANPI_NEWTON_RAPHSON_HPP
#define ANPI_NEWTON_RAPHSON_HPP

namespace anpi {
  
  /**
   * Find the roots of the function funct looking by means of the
   * Newton-Raphson method
   *
   * @param funct a functor of the form "T funct(T x)"
   * @param xi initial root guess
   * 
   * @return root found, or NaN if none could be found.
   *
   * @throws anpi::Exception if inteval is reversed or both extremes
   *         have same sign.
   */
  template<typename T>
  T rootNewtonRaphson(const std::function<T(T)>& funct,T xi,const T eps) {

      const T h = T(0.000000001);
      int iteracionesMax = 10000;
      T xold = xi;


      while(0 < iteracionesMax){

          T derivada = (funct(xi+h) - funct(xi-h)) / (T(2)*T(h));
          if(std::abs(derivada) < std::numeric_limits<T>::epsilon()){
              //Derivada cero
              xi = xold + T(1);
              derivada = (funct(xi+h) - funct(xi-h)) / T(2*h);
          }
          T dx = funct(xi) / derivada;
          xi = xi - dx;
          if(std::abs(dx) < eps){

              return xi;

          }
          --iteracionesMax;
      }

      // Return NaN if no root was found
      return std::numeric_limits<T>::quiet_NaN();
  }

}
  
#endif
