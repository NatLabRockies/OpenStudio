/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLERMECHANICALVENTILATION_IMPL_HPP
#define EPMODEL_CONTROLLERMECHANICALVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"
#include "DesignSpecificationOutdoorAirSpaceList.hpp"

#include <utility>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class ControllerOutdoorAir;
  class ControllerMechanicalVentilation;
  class Model;
  class ModelObject;
  class Schedule;
  class ThermalZone;

  namespace detail {

    class EPMODEL_API ControllerMechanicalVentilation_Impl : public ModelObject_Impl
    {
     public:
      struct OutdoorAirClaimFieldObservation
      {
        boost::optional<openstudio::Handle> managedTargetHandle;
        boost::optional<std::string> rawTarget;
        bool hasEvidence{false};
        bool canonical{false};
      };

      struct OutdoorAirClaimInspection
      {
        std::vector<openstudio::Handle> canonicalClaimantHandles;
        std::vector<openstudio::Handle> malformedClaimantHandles;
        bool hasMalformedClaim{false};

        bool exactlyOwnedBy(const openstudio::Handle& ownerHandle) const {
          return !hasMalformedClaim && canonicalClaimantHandles.size() == 1u && canonicalClaimantHandles.front() == ownerHandle;
        }

        bool unclaimed() const {
          return !hasMalformedClaim && canonicalClaimantHandles.empty();
        }
      };

      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ControllerMechanicalVentilation_Impl() override = default;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      bool demandControlledVentilation() const;
      bool isDemandControlledVentilationDefaulted() const;
      bool setDemandControlledVentilation(bool value);
      void resetDemandControlledVentilation();

      std::string systemOutdoorAirMethod() const;
      bool isSystemOutdoorAirMethodDefaulted() const;
      bool setSystemOutdoorAirMethod(const std::string& value);
      void resetSystemOutdoorAirMethod();
      std::vector<std::string> systemOutdoorAirMethodValues() const;

      boost::optional<openstudio::epmodel::ControllerOutdoorAir> controllerOutdoorAir() const;
      static OutdoorAirClaimFieldObservation observeOutdoorAirClaimField(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir);
      static bool clearOutdoorAirClaimField(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir);
      OutdoorAirClaimInspection outdoorAirClaimInspection() const;
      std::vector<std::pair<openstudio::epmodel::ThermalZone, openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>>
        zoneOutdoorAirEntries() const;
      void clearZoneOutdoorAirEntries();
      bool addZoneOutdoorAirEntry(const openstudio::epmodel::ThermalZone& zone,
                                  const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& dsoaSpaceList);

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
