/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"

#include "../../model/Model.hpp"

#include "../../model/DesignSpecificationOutdoorAir.hpp"
#include "../../model/DesignSpecificationOutdoorAir_Impl.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Space.hpp"
#include "../../model/ThermalZone.hpp"

#include "../../utilities/core/Logger.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/plot/ProgressBar.hpp"

#include <utilities/idd/DesignSpecification_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/DesignSpecification_OutdoorAir_SpaceList_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  namespace detail {
    boost::optional<IdfObject> translateDesignSpecificationOutdoorAir(DesignSpecificationOutdoorAir& modelObject) {
      boost::optional<std::string> s;
      boost::optional<double> value;

      IdfObject idfObject(IddObjectType::DesignSpecification_OutdoorAir);

      idfObject.setString(DesignSpecification_OutdoorAirFields::Name, modelObject.name().get());

      std::string outdoorAirMethod = modelObject.outdoorAirMethod();
      idfObject.setString(DesignSpecification_OutdoorAirFields::OutdoorAirMethod, outdoorAirMethod);

      double flowPerPerson = modelObject.outdoorAirFlowperPerson();
      double flowPerArea = modelObject.outdoorAirFlowperFloorArea();
      double flowPerZone = modelObject.outdoorAirFlowRate();
      double ach = modelObject.outdoorAirFlowAirChangesperHour();

      if (istringEqual(outdoorAirMethod, "Sum") || istringEqual(outdoorAirMethod, "Maximum")) {

        idfObject.setDouble(DesignSpecification_OutdoorAirFields::OutdoorAirFlowperPerson, flowPerPerson);
        idfObject.setDouble(DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZoneFloorArea, flowPerArea);
        idfObject.setDouble(DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZone, flowPerZone);
        idfObject.setDouble(DesignSpecification_OutdoorAirFields::OutdoorAirFlowAirChangesperHour, ach);

      } else {
        LOG_FREE(Error, "openstudio.energyplus.ForwardTranslator",
                 "Unknown OutdoorAirMethod '" << outdoorAirMethod << "' specified for OS:DesignSpecification:OutdoorAir named '"
                                              << modelObject.name().get() << "'");
        return boost::none;
      }

      boost::optional<Schedule> schedule = modelObject.outdoorAirFlowRateFractionSchedule();
      if (schedule) {
        idfObject.setString(DesignSpecification_OutdoorAirFields::OutdoorAirScheduleName, schedule->name().get());
      }

      return idfObject;
    }
  }  // namespace detail

  boost::optional<IdfObject> ForwardTranslator::getOrCreateThermalZoneDSOA(const model::ThermalZone& z) {

    auto objInMapIt = m_zoneDSOAsMap.find(z.handle());
    if (objInMapIt != m_zoneDSOAsMap.end()) {
      return objInMapIt->second;
    }

    auto translateAndMapDSOA = [this](DesignSpecificationOutdoorAir& dsoa) -> boost::optional<IdfObject> {
      auto objInMapIt = m_map.find(dsoa.handle());
      if (objInMapIt != m_map.end()) {
        return objInMapIt->second;
      }

      auto idf_dsoa_ = detail::translateDesignSpecificationOutdoorAir(dsoa);

      if (idf_dsoa_) {
        m_idfObjects.push_back(*idf_dsoa_);
        m_map.emplace(dsoa.handle(), *idf_dsoa_);

        if (m_progressBar) {
          m_progressBar->setValue((int)m_map.size());
        }
      }
      return idf_dsoa_;
    };

    auto spaces = z.spacesWithDesignSpecificationOutdoorAir();
    if (spaces.empty()) {
      m_zoneDSOAsMap.emplace(z.handle(), boost::none);
      return boost::none;
    }

    OptionalIdfObject result;

    if (m_forwardTranslatorOptions.excludeSpaceTranslation() || spaces.size() == 1) {
      // Spaces, and therefore DSOAs have been combined already
      auto dsoa = spaces.front().designSpecificationOutdoorAir().get();
      result = translateAndMapDSOA(dsoa);
    } else {

      // DSOA:SpaceList
      IdfObject dsoa_sp(IddObjectType::DesignSpecification_OutdoorAir_SpaceList);
      dsoa_sp.setName(z.nameString() + " DSOA Space List");

      // sort by space name so we ensure consistency/reproducibility
      std::sort(spaces.begin(), spaces.end(), WorkspaceObjectNameLess());
      for (const auto& s : spaces) {
        auto dsoa = *(s.designSpecificationOutdoorAir());
        if (auto dsoa_ = translateAndMapDSOA(dsoa)) {
          dsoa_sp.pushExtensibleGroup({s.nameString(), dsoa_->nameString()});
        }
      }

      m_idfObjects.push_back(dsoa_sp);
      result = dsoa_sp;
    }

    if (result) {
      m_zoneDSOAsMap.emplace(z.handle(), result);
    } else {
      m_zoneDSOAsMap.emplace(z.handle(), boost::none);
    }

    return result;
  }

}  // namespace energyplus

}  // namespace openstudio
