/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATERDESIGN_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATERDESIGN_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl() override = default;

      std::string heatingDesignCapacityMethod() const;
      bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
      void resetHeatingDesignCapacityMethod();

      boost::optional<double> heatingDesignCapacityPerFloorArea() const;
      bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
      void resetHeatingDesignCapacityPerFloorArea();

      double fractionofAutosizedHeatingDesignCapacity() const;
      bool isFractionofAutosizedHeatingDesignCapacityDefaulted() const;
      bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);
      void resetFractionofAutosizedHeatingDesignCapacity();

      double convergenceTolerance() const;
      bool isConvergenceToleranceDefaulted() const;
      bool setConvergenceTolerance(double convergenceTolerance);
      void resetConvergenceTolerance();

      double fractionRadiant() const;
      bool setFractionRadiant(double fractionRadiant);

      boost::optional<double> fractionofRadiantEnergyIncidentonPeople() const;
      bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);
      void resetFractionofRadiantEnergyIncidentonPeople();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
