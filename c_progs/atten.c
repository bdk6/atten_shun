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
//
// From here:
// https://www.allaboutcircuits.com/tools/bridged-tee-attenuator-calculator/
// We get R5 = Z0*(10^(db/20 -1)
//    and R6 = Z0*1/(10^(db/20) + 1)
//     or R5 = Z0*(N-1)
//    and R6 = Z0*1/(N+1)
//    N is 10^(db/20)
//
// We also get a different way to draw it which shows the name better
//
//                      R5
//               ------VVV------
//               |             |
//       ----------VVV-----VVV----------
//                Z0    |    Z0
//                      Z R6
//                      Z
//       ---------------|---------------

typedef struct atten
{
  double db;
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
void drawPi(attenuator_t a);
void drawT(attenuator_t a);
void drawBridgedT(attenuator_t a);
double dbToRatio(double db);


int main(int argc, char** argv)
{
  int rtn = 0;
  double r;
  r = dbToRatio(10);
  printf("10 db is %f \n", r);
  r = dbToRatio(20);
  printf("20 db is %f \n", r);
  r = dbToRatio(30);
  printf("30 db is %f \n", r);
  r = dbToRatio(60);
  printf("60 db is %f \n", r);

  double db = 1;
  while(db < 70)
    {
      attenuator_t atn;
      atn = calcPi(50, db);
      drawPi(atn);
      atn = calcT(50,db);
      drawT(atn);
      atn = calcBridgedT(50,db);
      drawBridgedT(atn);
      db *= 2;
    };


  return rtn;
}

// Values go into R3,R4
attenuator_t calcPi(double r0, double db)
{
  attenuator_t rtn;
  double N = dbToRatio(db);
  rtn.db = db;
  rtn.r0 = r0;
  rtn.r3 = r0* (N+1)/(N-1);
  rtn.r4 = r0* (N*N-1)/(2*N);

  return rtn;
}

// Values go into R1,R2
attenuator_t calcT(double r0, double db)
{
  attenuator_t rtn;
  double N = dbToRatio(db);
  rtn.db = db;
  rtn.r0 = r0;
  rtn.r1 = r0 * (N-1)/(N+1);
  rtn.r2 = r0 * (2*N)/(N*N-1);

  return rtn;
}

// Values into R5,R6
attenuator_t calcBridgedT(double r0, double db)
{
  attenuator_t rtn;
  double N = dbToRatio(db);
  rtn.db = db;
  rtn.r0 = r0;
  rtn.r5 = r0*(N-1);
  rtn.r6 = r0*(1.0/(N+1.0));

  return rtn;
}

void drawPi(attenuator_t a)
{
  printf("\n Pi attenuator for %3.2f db and %3.1f Ohms \n", a.db, a.r0);
  printf("        %3.2f   \n", a.r4);
  printf("------------VVV------------\n");
  printf("       |           |       \n");
  printf("       Z           Z       \n");
  printf("  %3.2fZ           Z %3.2f \n", a.r3);
  printf("       Z           Z       \n");
  printf("       |           |       \n");
  printf("---------------------------\n");
  printf("                           \n");
  
}

void drawT(attenuator_t a)
{
  printf("\n  T attenuator for %3.2f db and %3.1f Ohms \n", a.db, a.r0);
  printf("      %3.2f                 ",a.r1);
  printf("-------VVV-------VVV-------\n");
  printf("             |             \n");
  printf("             Z             \n");
  printf("             Z %3.2f       \n", a.r2);
  printf("             Z             \n");
  printf("             |             \n");
  printf("---------------------------\n");
  printf("                           \n");
  
}

void drawBridgedT(attenuator_t a)
{
  printf("\n Bridged T attenuator for %3.2f db and %3.1f Ohms \n", a.db, a.r0);
  printf("                           \n");
  printf("            VVV            \n");
  printf("-------VVV-------VVV-------\n");
  printf("    |                 |    \n");
  printf("    Z                 Z    \n");
  printf("    Z %3.2f           Z  %3.2f \n", a.r0);
  printf("    Z                 Z    \n");
  printf("    |                 |    \n");
  printf("    -------------------    \n");
  printf("             |             \n");
  printf("             Z             \n");
  printf("             Z %3.2f       \n", a.r6);
  printf("             Z             \n");
  printf("             |             \n");
  printf("---------------------------\n");
  printf("                           \n");
}

double dbToRatio(double db)
{
  double rtn = -1.0;
  db = fabs(db);  // no negative ATTENUATION
  rtn = pow(10, db/20.0);

  return rtn;
}
