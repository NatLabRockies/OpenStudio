/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSCROSSVENTILATION_HPP
#define EPMODEL_ROOMAIRSETTINGSCROSSVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirSettingsCrossVentilation_Impl;
  }

  class EPMODEL_API RoomAirSettingsCrossVentilation : public ModelObject
  {
   public:
    explicit RoomAirSettingsCrossVentilation(const Model& model);

    virtual ~RoomAirSettingsCrossVentilation() override = default;
    RoomAirSettingsCrossVentilation(const RoomAirSettingsCrossVentilation& other) = default;
    RoomAirSettingsCrossVentilation(RoomAirSettingsCrossVentilation&& other) = default;
    RoomAirSettingsCrossVentilation& operator=(const RoomAirSettingsCrossVentilation&) = default;
    RoomAirSettingsCrossVentilation& operator=(RoomAirSettingsCrossVentilation&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> airflowRegionUsedforThermalComfortEvaluationValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class and accessor naming.
    // - Field Mapping: airflowRegionUsedforThermalComfortEvaluation maps directly to EnergyPlus
    //   RoomAirSettings:CrossVentilation / Airflow Region Used for Thermal Comfort Evaluation.
    // - Field Mapping: Zone Name and Gain Distribution Schedule Name are object-list relationship
    //   fields and intentionally excluded from scalar accessors in this scaffold pass.
    // - Field Mapping: Name remains available via ModelObject base name APIs.
    // - TODO(parity): Add typed relationship APIs for excluded fields after scalar saturation.

    /** @name Getters */
    //@{

    boost::optional<std::string> airflowRegionUsedforThermalComfortEvaluation() const;

    //@}

    /** @name Setters */
    //@{

    bool setAirflowRegionUsedforThermalComfortEvaluation(const std::string& airflowRegionUsedforThermalComfortEvaluation);
    void resetAirflowRegionUsedforThermalComfortEvaluation();

    //@}

   protected:
    using ImplType = detail::RoomAirSettingsCrossVentilation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirSettingsCrossVentilation(std::shared_ptr<detail::RoomAirSettingsCrossVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
