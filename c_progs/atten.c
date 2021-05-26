//////////////////////////////////////////////////////////////////////////////
///  @file atten.c
///  @brief Calculates resistive RF attenuators
///  @copy William R Cooke 2021
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>

// the formulas for these attenuators come from
// https://www.electronics-notes.com/articles/radio/
//   rf-attenuators/pi-t-resistive-attenuator-pad-circuit-design-formula.php
//
//   N = Vin/Vout
//
//   T attenuator
//    -----VVV-----VVV------
//         R1   |   R1
//              Z
//   R0         Z  R2      R0
//              |
//              |
//    ---------------------
//
//    R1 = R0*(N-1)/(N+1)
//    R2 = R0*( (2N)/(N^2 -1) )
//
//    PI attenuator
//    ----------------VVV------------
//              |     R4      |
//              Z             Z
//        R3    Z         R3  Z
//              |             |
//              |             |
//    -------------------------------
//
//    R3 = R0 * (N+1)/(N-1)
//    R4 = R0*( (N^2-1)/(2N) )
//
//    Bridged T attenuator
//    --------------VVV-------------
//             |     R5    |
//             Z           Z
//         R0  Z           Z R0
//             |           |
//             -----VVV-----
//                   |
//                   Z
//                   Z  R6
//                   |
//     ----------------------------
//
//     R5 =
//     R6 =

typedef struct atten
{
  double r0;
  double r1;
  double r2;
  double r3;
  double r4;
  double r5;
  double r6;
} attenuator_t;

attenuator_t calcPi(double r0, double db);
attenuator_t calcT(double r0, double db);
attenuator_t calcBridgedT(double r0, double db);


int main(int argc, char** argv)
{
  int rtn = 0;



  return rtn;
}

attenuator_t calcPi(double r0, double db)
{
  attenuator_t rtn;

  return rtn;
}

attenuator_t calcT(double r0, double db)
{
  attenuator_t rtn;

  return rtn;
}

attenuator_t calcBridgedT(double r0, double db)
{
  attenuator_t rtn;

  return rtn;
}

