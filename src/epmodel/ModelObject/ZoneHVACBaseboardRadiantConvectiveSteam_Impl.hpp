/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVESTEAM_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVESTEAM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveSteam_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACBaseboardRadiantConvectiveSteam_Impl() override = default;

      boost::optional<double> heatingDesignCapacity() const;
      bool setHeatingDesignCapacity(double heatingDesignCapacity);
      bool isHeatingDesignCapacityAutosized() const;
      void autosizeHeatingDesignCapacity();

      boost::optional<double> degreeofSubCooling() const;
      bool setDegreeofSubCooling(double degreeofSubCooling);
      bool isDegreeofSubCoolingDefaulted() const;
      void resetDegreeofSubCooling();

      boost::optional<double> maximumSteamFlowRate() const;
      bool setMaximumSteamFlowRate(double maximumSteamFlowRate);
      bool isMaximumSteamFlowRateAutosized() const;
      void autosizeMaximumSteamFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
