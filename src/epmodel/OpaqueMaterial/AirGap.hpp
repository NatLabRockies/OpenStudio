/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRGAP_HPP
#define EPMODEL_AIRGAP_HPP

#include "EPModelAPI.hpp"
#include "OpaqueMaterial/OpaqueMaterial.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirGap_Impl;
  }

  /** \brief Represents a thermal-resistance air gap.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#materialairgap,Material:AirGap}.
   *
   * \par Important behavior
   * The constructor writes the supplied thermal resistance to the EnergyPlus
   * <code>Thermal Resistance</code> field. The shared opaque-material thermal
   * methods resolve this field rather than a thickness-based material model.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AirGap</code>. The thermal-resistance accessor and
   * setter have the same public meaning.
   *
   * \par Known limitations
   * An air gap has no material thickness or conductivity to derive; its thermal
   * resistance is the defining input.
   */
  class EPMODEL_API AirGap : public OpaqueMaterial
  {
   public:
    explicit AirGap(const Model& model, double thermalResistance = 0.1);

    virtual ~AirGap() override = default;
    AirGap(const AirGap& other) = default;
    AirGap(AirGap&& other) = default;
    AirGap& operator=(const AirGap&) = default;
    AirGap& operator=(AirGap&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::AirGap_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirGap(std::shared_ptr<detail::AirGap_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
