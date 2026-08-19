/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESNAME_HPP
#define EPMODEL_FLUIDPROPERTIESNAME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FluidPropertiesName_Impl;
  }

  /** \brief Represents <code>FluidProperties:Name</code>.
   *
   * \par EnergyPlus object
   * Represents \epobject{group-fluid-properties.html#fluidpropertiesname,FluidProperties:Name}.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for <code>FluidProperties:Name</code>; this wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * Relationship-row mutation and higher-level topology conveniences remain owner-managed or unavailable through this wrapper.
   */
  class EPMODEL_API FluidPropertiesName : public ModelObject
  {
   public:
    explicit FluidPropertiesName(const Model& model);

    virtual ~FluidPropertiesName() override = default;
    FluidPropertiesName(const FluidPropertiesName& other) = default;
    FluidPropertiesName(FluidPropertiesName&& other) = default;
    FluidPropertiesName& operator=(const FluidPropertiesName&) = default;
    FluidPropertiesName& operator=(FluidPropertiesName&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fluidTypeValues();
    std::string fluidName() const;
    bool setFluidName(const std::string& fluidName);

    std::string fluidType() const;
    bool setFluidType(const std::string& fluidType);

   protected:
    using ImplType = detail::FluidPropertiesName_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FluidPropertiesName(std::shared_ptr<detail::FluidPropertiesName_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
