/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMHEATINGDX_HPP
#define EPMODEL_COILSYSTEMHEATINGDX_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilSystemHeatingDX_Impl;
  }

  /** \brief Represents <code>CoilSystem:Heating:DX</code>.
   *
   * \par EnergyPlus object
   * Represents \epobject{group-heating-and-cooling-coils.html#coilsystemheatingdx,CoilSystem:Heating:DX}.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for <code>CoilSystem:Heating:DX</code>; this wrapper is new to the EPModel API.
   * The public EPModel surface currently exposes only the EnergyPlus heating-coil object-type selector; availability-schedule and heating-coil relationships remain owner-managed.
   *
   * \par Known limitations
   * Relationship-row mutation and higher-level topology conveniences remain owner-managed or unavailable through this wrapper.
   */
  class EPMODEL_API CoilSystemHeatingDX : public ModelObject
  {
   public:
    explicit CoilSystemHeatingDX(const Model& model);

    virtual ~CoilSystemHeatingDX() override = default;
    CoilSystemHeatingDX(const CoilSystemHeatingDX& other) = default;
    CoilSystemHeatingDX(CoilSystemHeatingDX&& other) = default;
    CoilSystemHeatingDX& operator=(const CoilSystemHeatingDX&) = default;
    CoilSystemHeatingDX& operator=(CoilSystemHeatingDX&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatingCoilObjectTypeValues();
    /** @name HeatingCoilObjectType */
    //@{
    std::string heatingCoilObjectType() const;
    bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);
    //@}

   protected:
    using ImplType = detail::CoilSystemHeatingDX_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilSystemHeatingDX(std::shared_ptr<detail::CoilSystemHeatingDX_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
