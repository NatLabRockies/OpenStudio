/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MASSLESSOPAQUEMATERIAL_HPP
#define EPMODEL_MASSLESSOPAQUEMATERIAL_HPP

#include "EPModelAPI.hpp"
#include "OpaqueMaterial/OpaqueMaterial.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class MasslessOpaqueMaterial_Impl;
  }

  /** \brief Represents an opaque material defined by resistance and surface absorptances.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#materialnomass,Material:NoMass}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::MasslessOpaqueMaterial</code>. The roughness,
   * thermal-resistance, and absorptance methods have the same public meaning.
   * Model's material-property relationships for phase change and EMPD are not
   * available.
   *
   * \par Known limitations
   * This wrapper exposes the scalar <code>Material:NoMass</code> fields only;
   * material-property child objects cannot be assigned here.
   */
  class EPMODEL_API MasslessOpaqueMaterial : public OpaqueMaterial
  {
   public:
    explicit MasslessOpaqueMaterial(const Model& model, const std::string& roughness = "Smooth", double thermalResistance = 0.1);

    virtual ~MasslessOpaqueMaterial() override = default;
    MasslessOpaqueMaterial(const MasslessOpaqueMaterial& other) = default;
    MasslessOpaqueMaterial(MasslessOpaqueMaterial&& other) = default;
    MasslessOpaqueMaterial& operator=(const MasslessOpaqueMaterial&) = default;
    MasslessOpaqueMaterial& operator=(MasslessOpaqueMaterial&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> roughnessValues();

    std::string roughness() const;
    bool setRoughness(const std::string& roughness);

    double thermalAbsorptance() const;
    bool isThermalAbsorptanceDefaulted() const;
    bool setThermalAbsorptance(double thermalAbsorptance);
    void resetThermalAbsorptance();

    double solarAbsorptance() const;
    bool isSolarAbsorptanceDefaulted() const;
    bool setSolarAbsorptance(double solarAbsorptance);
    void resetSolarAbsorptance();

    double visibleAbsorptance() const;
    bool isVisibleAbsorptanceDefaulted() const;
    bool setVisibleAbsorptance(double visibleAbsorptance);
    void resetVisibleAbsorptance();

   protected:
    using ImplType = detail::MasslessOpaqueMaterial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit MasslessOpaqueMaterial(std::shared_ptr<detail::MasslessOpaqueMaterial_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
