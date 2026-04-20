/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERSURFACE_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERSURFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatExchangerSurface_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatExchangerSurface_Impl() override = default;

      boost::optional<double> hydronicTubingInsideDiameter() const;
      bool setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter);
      void resetHydronicTubingInsideDiameter();

      boost::optional<int> numberofTubingCircuits() const;
      bool setNumberofTubingCircuits(int numberofTubingCircuits);
      void resetNumberofTubingCircuits();

      boost::optional<double> hydronicTubeSpacing() const;
      bool setHydronicTubeSpacing(double hydronicTubeSpacing);
      void resetHydronicTubeSpacing();

      boost::optional<double> surfaceLength() const;
      bool setSurfaceLength(double surfaceLength);
      void resetSurfaceLength();

      boost::optional<double> surfaceWidth() const;
      bool setSurfaceWidth(double surfaceWidth);
      void resetSurfaceWidth();

      std::string lowerSurfaceEnvironment() const;
      bool isLowerSurfaceEnvironmentDefaulted() const;
      bool setLowerSurfaceEnvironment(const std::string& lowerSurfaceEnvironment);
      void resetLowerSurfaceEnvironment();

      std::vector<std::string> lowerSurfaceEnvironmentValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
