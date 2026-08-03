/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CFACTORUNDERGROUNDWALLCONSTRUCTION_IMPL_HPP
#define EPMODEL_CFACTORUNDERGROUNDWALLCONSTRUCTION_IMPL_HPP

#include "ConstructionBase/ConstructionBase_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API CFactorUndergroundWallConstruction_Impl : public ConstructionBase_Impl
    {
     public:
      using ConstructionBase_Impl::ConstructionBase_Impl;
      virtual ~CFactorUndergroundWallConstruction_Impl() override = default;

      double cFactor() const;
      bool setCFactor(double cFactor);

      double height() const;
      bool setHeight(double height);

      bool isOpaque() const override {
        return true;
      }
      bool isFenestration() const override {
        return false;
      }
      bool isSolarDiffusing() const override {
        return false;
      }
      bool isModelPartition() const override {
        return false;
      }
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
