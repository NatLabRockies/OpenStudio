/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SWIMMINGPOOLINDOOR_IMPL_HPP
#define EPMODEL_SWIMMINGPOOLINDOOR_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class SwimmingPoolIndoor_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~SwimmingPoolIndoor_Impl() override = default;

      bool addToNode(Node& node) override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;

      double averageDepth() const;
      bool setAverageDepth(double averageDepth);

      double coverEvaporationFactor() const;
      bool isCoverEvaporationFactorDefaulted() const;
      bool setCoverEvaporationFactor(double coverEvaporationFactor);
      void resetCoverEvaporationFactor();

      double coverConvectionFactor() const;
      bool isCoverConvectionFactorDefaulted() const;
      bool setCoverConvectionFactor(double coverConvectionFactor);
      void resetCoverConvectionFactor();

      double coverShortWavelengthRadiationFactor() const;
      bool isCoverShortWavelengthRadiationFactorDefaulted() const;
      bool setCoverShortWavelengthRadiationFactor(double coverShortWavelengthRadiationFactor);
      void resetCoverShortWavelengthRadiationFactor();

      double coverLongWavelengthRadiationFactor() const;
      bool isCoverLongWavelengthRadiationFactorDefaulted() const;
      bool setCoverLongWavelengthRadiationFactor(double coverLongWavelengthRadiationFactor);
      void resetCoverLongWavelengthRadiationFactor();

      double poolHeatingSystemMaximumWaterFlowRate() const;
      bool setPoolHeatingSystemMaximumWaterFlowRate(double poolHeatingSystemMaximumWaterFlowRate);

      double poolMiscellaneousEquipmentPower() const;
      bool setPoolMiscellaneousEquipmentPower(double poolMiscellaneousEquipmentPower);

      double maximumNumberofPeople() const;
      bool setMaximumNumberofPeople(double maximumNumberofPeople);

      boost::optional<Node> poolWaterInletNode() const;
      boost::optional<Node> poolWaterOutletNode() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
