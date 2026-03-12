/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "MethodGroupingFixture.hpp"
#include "MethodGroupingFixture_Impl.hpp"

namespace openstudio {
namespace epmodel {

  double MethodGroupingFixture::alpha() const {
    return 1.0;
  }

  bool MethodGroupingFixture::setAlpha(double alpha) {
    return alpha > 0.0;
  }

  bool MethodGroupingFixture::isAlphaDefaulted() const {
    return false;
  }

  bool MethodGroupingFixture::setBeta(double beta) {
    return beta > 0.0;
  }

  void MethodGroupingFixture::resetAlpha() {}

  double MethodGroupingFixture::beta() const {
    return 2.0;
  }

  bool MethodGroupingFixture::setGamma(double gamma) {
    return gamma > 0.0;
  }

  bool MethodGroupingFixture::setBetaValue(double betaValue) {
    return betaValue > 0.0;
  }

  void MethodGroupingFixture::resetBeta() {}

  double MethodGroupingFixture::gamma() const {
    return 3.0;
  }

  bool MethodGroupingFixture::isBetaDefaulted() const {
    return true;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double MethodGroupingFixture_Impl::alpha() const {
      return 1.0;
    }

    bool MethodGroupingFixture_Impl::setAlpha(double alpha) {
      return alpha > 0.0;
    }

    bool MethodGroupingFixture_Impl::isAlphaDefaulted() const {
      return false;
    }

    bool MethodGroupingFixture_Impl::setBeta(double beta) {
      return beta > 0.0;
    }

    void MethodGroupingFixture_Impl::resetAlpha() {}

    double MethodGroupingFixture_Impl::beta() const {
      return 2.0;
    }

    bool MethodGroupingFixture_Impl::setGamma(double gamma) {
      return gamma > 0.0;
    }

    bool MethodGroupingFixture_Impl::setBetaValue(double betaValue) {
      return betaValue > 0.0;
    }

    void MethodGroupingFixture_Impl::resetBeta() {}

    double MethodGroupingFixture_Impl::gamma() const {
      return 3.0;
    }

    bool MethodGroupingFixture_Impl::isBetaDefaulted() const {
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
