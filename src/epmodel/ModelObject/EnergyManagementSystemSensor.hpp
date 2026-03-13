/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMSENSOR_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMSENSOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemSensor_Impl;
  }

  class EPMODEL_API EnergyManagementSystemSensor : public ModelObject
  {
   public:
    explicit EnergyManagementSystemSensor(const Model& model);

    virtual ~EnergyManagementSystemSensor() override = default;
    EnergyManagementSystemSensor(const EnergyManagementSystemSensor& other) = default;
    EnergyManagementSystemSensor(EnergyManagementSystemSensor&& other) = default;
    EnergyManagementSystemSensor& operator=(const EnergyManagementSystemSensor&) = default;
    EnergyManagementSystemSensor& operator=(EnergyManagementSystemSensor&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::EnergyManagementSystemSensor scalar accessor names/signatures.
    // - Field Mapping: keyName -> EnergyPlus EnergyManagementSystem:Sensor, Output Variable or Output Meter Index Key Name.
    // - Field Mapping: outputVariableOrMeterName -> EnergyPlus EnergyManagementSystem:Sensor, Output Variable or Output Meter Name.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemSensor.cpp writes these fields directly.
    // - TODO(parity): Add outputVariable/outputMeter relationship APIs incrementally without changing these scalar signatures.

    /** @name Key name accessors */
    //@{
    boost::optional<std::string> keyName() const;
    bool setKeyName(const std::string& keyName);
    void resetKeyName();
    //@}

    /** @name Output variable or meter name accessors */
    //@{
    std::string outputVariableOrMeterName() const;
    bool setOutputVariableOrMeterName(const std::string& outputVariableOrMeterName);
    //@}

   protected:
    using ImplType = detail::EnergyManagementSystemSensor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemSensor(std::shared_ptr<detail::EnergyManagementSystemSensor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
