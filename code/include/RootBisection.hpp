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

#ifndef ANPI_ROOT_BISECTION_HPP
#define ANPI_ROOT_BISECTION_HPP

namespace anpi {
  
  /**
   * Find the roots of the function funct looking for it in the
   * interval [xl,xu], using the bisection method.
   *
   * @param funct a std::function of the form "T funct(T x)"
   * @param xl lower interval limit
   * @param xu upper interval limit
   *
   * @return root found, or NaN if none could be found.
   *
   * @throws anpi::Exception if inteval is reversed or both extremes
   *         have same sign.
   */
  template<typename T>
  T rootBisection(const std::function<T(T)>& funct,T xl,T xu,const T eps) {

    // TODO: Put your code in here!

    if(xu < xl){

        throw anpi::Exception("El intervalo esta invertido.");
    }

    if(funct(xl)*funct(xu) > T(0)){

      throw anpi::Exception("No hay cambio de signo en la funcion en el intervalo escogido.");

    }else{

        if(std::abs(funct(xl)) < std::numeric_limits<T>::epsilon()){

            return xl;

        }else if(std::abs(funct(xu)) < std::numeric_limits<T>::epsilon()){

            return xu;
        }

    }

    //int n = std::log2((xu-xl)/eps);
    int n = 1000;

    T xr = xl;
    T ea = T();
    T fl = funct(xl);

    for(int i = 0; i < n ; ++i){

      T xrold = xr;
      xr = (xl+xu) / T(2);
      T fr = funct(xr);
      if(std::abs(xr) > std::numeric_limits<T>::epsilon()){

          ea = std::abs((xr-xrold)/xr) * T(100);

      }

      T cond = fr * fl;

      if(cond < T(0)){

        xu = xr;


      }else if(cond > T(0)){

        xl = xr;
        fl = fr;

      }else{

        ea = T(0);
        if(std::abs(fl) < std::numeric_limits<T>::epsilon()){

          xr = xl;
        }

      }

      if(ea < eps){

        return xr;

      }

    }
    return std::numeric_limits<T>::quiet_NaN();
  }
}
  
#endif
