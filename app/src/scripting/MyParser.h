#ifndef MYPARSER_H
#define MYPARSER_H

#include <../3rdparty/muparser/muParser.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf.h>

#include <qstringlist.h>

using namespace mu;

/*!\brief Mathematical parser class based on muParser.
 *
 * \section future_plans Future Plans
 * Eliminate in favour of Script/ScriptingEnv.
 * This will allow you to use e.g. Python's global variables and functions
 * everywhere.
 * Before this happens, a cleaner and more generic solution for accessing the
 * current ScriptingEnv
 * should be implemented (maybe by making it a property of Project; see
 * ApplicationWindow).
 * [ assigned to knut ]
 */
class MyParser : public Parser {
 public:
  MyParser();

  static QStringList functionsList();
  static QString explainFunction(int index);

  static double bessel_J0(double x) { return gsl_sf_bessel_J0(x); }

  static double bessel_J1(double x) { return gsl_sf_bessel_J1(x); }

  static double bessel_Jn(double x, double n) {
    return gsl_sf_bessel_Jn(static_cast<int>(n), x);
  }

  static double bessel_Y0(double x) { return gsl_sf_bessel_Y0(x); }

  static double bessel_Y1(double x) { return gsl_sf_bessel_Y1(x); }
  static double bessel_Yn(double x, double n) {
    return gsl_sf_bessel_Yn(static_cast<int>(n), x);
  }
  static double beta(double a, double b) { return gsl_sf_beta(a, b); }
  static double erf(double x) { return gsl_sf_erf(x); }
  static double erfc(double x) { return gsl_sf_erfc(x); }
  static double erfz(double x) { return gsl_sf_erf_Z(x); }
  static double erfq(double x) { return gsl_sf_erf_Q(x); }
  static double gamma(double x) { return gsl_sf_gamma(x); }
  static double gammaln(double x) { return gsl_sf_lngamma(x); }
  static double hazard(double x) { return gsl_sf_hazard(x); }
};

#endif  // MYPARSER_H
