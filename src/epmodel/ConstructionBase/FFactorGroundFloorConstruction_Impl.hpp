/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FFACTORGROUNDFLOORCONSTRUCTION_IMPL_HPP
#define EPMODEL_FFACTORGROUNDFLOORCONSTRUCTION_IMPL_HPP

#include "ConstructionBase/ConstructionBase_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FFactorGroundFloorConstruction_Impl : public ConstructionBase_Impl
    {
     public:
      using ConstructionBase_Impl::ConstructionBase_Impl;
      virtual ~FFactorGroundFloorConstruction_Impl() override = default;

      double fFactor() const;
      bool setFFactor(double fFactor);

      double area() const;
      bool setArea(double area);

      double perimeterExposed() const;
      bool setPerimeterExposed(double perimeterExposed);

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
