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

#ifndef ANPI_ROOT_BRENT_HPP
#define ANPI_ROOT_BRENT_HPP

namespace anpi {
  
  /**
   * Find the roots of the function funct looking for it in the
   * interval [xl,xu], using the Brent's method.
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
  T rootBrent(const std::function<T(T)>& funct,T xl,T xu,const T eps) {

    // TODO: Put your code in here!

    T fl = funct(xl);
    T fu = funct(xu);

    if(fl * fu > T(0)){

      throw anpi::Exception("El intervalo no encierra la raiz");

    } else {

      if(std::abs(fl) < std::numeric_limits<T>::epsilon()){

        return xl;

      }else if(std::abs(fu) < std::numeric_limits<T>::epsilon()){

        return xu;

      }

    }

    if(xu < xl){

      throw anpi::Exception("El intervalo esta invertido");
    }

    if(std::abs(fl) < std::abs(fu)){

      std::swap(xl,xu);
      std::swap(fl,fu);
    }

    T xm = xl;
    T fm = fl;
    bool bandera = true;
    T xr = T(0);
    T d = T(0);

    for(int i = 0; i < std::numeric_limits<T>::digits; ++i){


      if(std::abs(xu-xl) < eps / T(2)){

        return xr;

      }

      if(fl != fm && fu != fm){ //Interpolacion cuadratica inversa

        xr = (xl * fu * fm ) / ((fl - fu)*(fl - fm))
            + (xu * fl * fm) / ((fu - fl)*(fu - fm))
            + (xr * fl * fu) / ((fm - fl)*(fm - fu));

      }else{ //Secante

        xr = xu - fu * ((xu - xl)/(fu - fl));

      }

      if( (xu < xr < ((T(3) * xl + xu) / T(4))) ||
          (bandera && std::abs(xr - xu) >= std::abs(xu - xm) / T(2)) ||
          (!bandera && std::abs(xr - xu) >= std::abs(xm - d) / T(2)) ||
          (bandera && std::abs(xu - xm) < std::abs(eps)) ||
          (!bandera && std::abs(xm -d) < std::abs(eps))
        ){
        //Biseccion
        xr = (xl + xu) / T(2);
        bandera = true;

      }else{

        bandera = false;

      }

      T fr = funct(xr);
      d = xm;
      xm = xu;
      fm = fu;

      if(fl*fr < T(0)){

        xu = xr;
        fu = fr;

      }else{

        xl = xr;
        fl = fr;

      }

      if(std::abs(fl) < std::abs(fu)){

          std::swap(xl,xu);
          std::swap(fl,fu);

      }


    }

    // Return NaN if no root was found
    return std::numeric_limits<T>::quiet_NaN();
  }
}
  
#endif

