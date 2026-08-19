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

  /** \brief Represents <code>EnergyManagementSystem:Sensor</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemsensor,EnergyManagementSystem:Sensor}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemSensor</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
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
