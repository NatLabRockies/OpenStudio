/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_METHODGROUPINGFIXTURE_IMPL_HPP
#define EPMODEL_METHODGROUPINGFIXTURE_IMPL_HPP

namespace openstudio {
namespace epmodel {
  namespace detail {

    class MethodGroupingFixture_Impl
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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
