/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMTRENDVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMTRENDVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemTrendVariable_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:TrendVariable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemtrendvariable,EnergyManagementSystem:TrendVariable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemTrendVariable</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemTrendVariable : public ModelObject
  {
   public:
    explicit EnergyManagementSystemTrendVariable(const Model& model, const std::string& eMSVariableName);

    virtual ~EnergyManagementSystemTrendVariable() override = default;
    EnergyManagementSystemTrendVariable(const EnergyManagementSystemTrendVariable& other) = default;
    EnergyManagementSystemTrendVariable(EnergyManagementSystemTrendVariable&& other) = default;
    EnergyManagementSystemTrendVariable& operator=(const EnergyManagementSystemTrendVariable&) = default;
    EnergyManagementSystemTrendVariable& operator=(EnergyManagementSystemTrendVariable&&) = default;

    static IddObjectType iddObjectType();
    std::string emsVariableName() const;
    bool setEMSVariableName(const std::string& eMSVariableName);

    int numberOfTimestepsToBeLogged() const;
    bool setNumberOfTimestepsToBeLogged(int numberofTimestepstobeLogged);

   protected:
    using ImplType = detail::EnergyManagementSystemTrendVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemTrendVariable(std::shared_ptr<detail::EnergyManagementSystemTrendVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
