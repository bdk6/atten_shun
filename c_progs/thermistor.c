//////////////////////////////////////////////////////////////////////////////
/// @file thermistor.c
/// @brief Calculates values of temp / resistance for (NTC) thermistors
/// @copy 2021 William R Cooke Small Time Electronics
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>

double calcR(double B, double R, double kelvinRef, double kelvinU);
double calcRCelsius(double B, double R, double cRef, double cU);

int main(int argc, char** argv)
{
  int rtn = 0;
  double r = calcRCelsius(4050, 10000, 25, 50);
  printf("R for T of 50 C is %f \n", r);

  r = calcR(4050, 10000, 25+273.15, 50+273.15);
  printf("R for T of 50 deg is %f \n", r);


  return rtn;
}
double calcRCelsius(double B, double R, double cRef, double cU)
{
  return calcR(B, R, cRef + 273.15, cU + 273.15);
}

double calcR(double B, double R, double kelvinRef, double kelvinU)
{
  double rtn = 0.0;
  // B = T2*T1/(T2-T1) * ln(R1/R2)
  // T1 is ref temp in kelvins
  // T2 is desired temp in kelvins
  // R1 is reference temp resistance
  // R2 is resistance at T2

  // sub params for variables
  // B = kelvinU * kelvinRef / (kelvinU - kelvinRef) * ln(R/?)
  // B * (kelvinU - kelvinRef)/(kelvinU * kelvinRef) = ln(R/?)
  // exp(B*(kelvinU-kelvinRef)/(kelvinU*kelvinRef) = R/?
  // ? = R/(exp(B*(kelvinU-kelvinRef)/(kelvinU*kelvinRef)))

  double rUnknown = R/(exp(B*(kelvinU-kelvinRef)/(kelvinU*kelvinRef)));
  rtn = rUnknown;
			   


  return rtn;
}

