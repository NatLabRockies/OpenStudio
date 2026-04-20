/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKZONECONTROLPRESSURECONTROLLER_HPP
#define EPMODEL_AIRFLOWNETWORKZONECONTROLPRESSURECONTROLLER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkZoneControlPressureController_Impl;
  }

  class EPMODEL_API AirflowNetworkZoneControlPressureController : public ModelObject
  {
   public:
    explicit AirflowNetworkZoneControlPressureController(const Model& model);

    virtual ~AirflowNetworkZoneControlPressureController() override = default;
    AirflowNetworkZoneControlPressureController(const AirflowNetworkZoneControlPressureController& other) = default;
    AirflowNetworkZoneControlPressureController(AirflowNetworkZoneControlPressureController&& other) = default;
    AirflowNetworkZoneControlPressureController& operator=(const AirflowNetworkZoneControlPressureController&) = default;
    AirflowNetworkZoneControlPressureController& operator=(AirflowNetworkZoneControlPressureController&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: controlObjectType maps directly to EnergyPlus
    //   AirflowNetwork:ZoneControl:PressureController / Control Object Type.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Control Zone Name, Control Object Name, Pressure Control Availability Schedule Name,
    //   and Pressure Setpoint Schedule Name are relationship-like object-list fields and intentionally excluded
    //   from scalar accessors.
    // - TODO(parity): Add relationship APIs for excluded object-list links in a follow-up parity pass.

    /** @name Getters */
    //@{
    std::string controlObjectType() const;
    //@}

    /** @name Setters */
    //@{
    bool setControlObjectType(const std::string& controlObjectType);
    //@}

   protected:
    using ImplType = detail::AirflowNetworkZoneControlPressureController_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkZoneControlPressureController(std::shared_ptr<detail::AirflowNetworkZoneControlPressureController_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
