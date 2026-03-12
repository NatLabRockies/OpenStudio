/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_METHODGROUPINGFIXTURE_HPP
#define EPMODEL_METHODGROUPINGFIXTURE_HPP

namespace openstudio {
namespace epmodel {

  namespace detail {
    class MethodGroupingFixture_Impl;
  }

  class MethodGroupingFixture
  {
   public:
    double alpha() const;
    bool setBeta(double beta);
    bool setAlpha(double alpha);
    void resetAlpha();
    bool isAlphaDefaulted() const;

    double beta() const;
    void resetBeta();
    bool setGamma(double gamma);
    bool setBetaValue(double betaValue);
    double gamma() const;
    bool isBetaDefaulted() const;
    bool setBeta(double betaValue, bool alternate);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
