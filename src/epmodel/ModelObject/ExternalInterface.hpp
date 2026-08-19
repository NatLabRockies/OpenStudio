/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACE_HPP
#define EPMODEL_EXTERNALINTERFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterface_Impl;
  }

  /** \brief Represents <code>ExternalInterface</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterface,ExternalInterface}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExternalInterface</code>.
   * **Not yet available:** Model typed FMU/component relationships and OpenStudio-only export controls are not exposed unless represented by an EnergyPlus field here.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API ExternalInterface : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~ExternalInterface() override = default;
    ExternalInterface(const ExternalInterface& other) = default;
    ExternalInterface(ExternalInterface&& other) = default;
    ExternalInterface& operator=(const ExternalInterface&) = default;
    ExternalInterface& operator=(ExternalInterface&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> nameofExternalInterfaceValues();
    /** @name Name of External Interface */
    //@{
    std::string nameofExternalInterface() const;
    bool setNameofExternalInterface(const std::string& nameofExternalInterface);
    //@}

   protected:
    explicit ExternalInterface(const Model& model);

    using ImplType = detail::ExternalInterface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterface(std::shared_ptr<detail::ExternalInterface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
