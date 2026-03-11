/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYEXPOSEDFOUNDATIONPERIMETER_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYEXPOSEDFOUNDATIONPERIMETER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyExposedFoundationPerimeter_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyExposedFoundationPerimeter_Impl() override = default;

      std::string exposedPerimeterCalculationMethod() const;
      bool setExposedPerimeterCalculationMethod(const std::string& exposedPerimeterCalculationMethod);

      boost::optional<double> totalExposedPerimeter() const;
      bool setTotalExposedPerimeter(double totalExposedPerimeter);

      double exposedPerimeterFraction() const;
      bool setExposedPerimeterFraction(double exposedPerimeterFraction);
      bool isExposedPerimeterFractionDefaulted() const;
      void resetExposedPerimeterFraction();

      std::vector<std::string> exposedPerimeterCalculationMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
