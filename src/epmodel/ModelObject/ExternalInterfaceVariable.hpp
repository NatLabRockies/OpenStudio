/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceVariable_Impl;
  }

  /** \brief Represents <code>ExternalInterface:Variable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfacevariable,ExternalInterface:Variable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExternalInterfaceVariable</code>.
   * **Not yet available:** Model typed FMU/component relationships and OpenStudio-only export controls are not exposed unless represented by an EnergyPlus field here.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API ExternalInterfaceVariable : public ModelObject
  {
   public:
    explicit ExternalInterfaceVariable(const Model& model, const std::string& variableName, double initialValue);

    virtual ~ExternalInterfaceVariable() override = default;
    ExternalInterfaceVariable(const ExternalInterfaceVariable& other) = default;
    ExternalInterfaceVariable(ExternalInterfaceVariable&& other) = default;
    ExternalInterfaceVariable& operator=(const ExternalInterfaceVariable&) = default;
    ExternalInterfaceVariable& operator=(ExternalInterfaceVariable&&) = default;

    static IddObjectType iddObjectType();
    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceVariable(std::shared_ptr<detail::ExternalInterfaceVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
