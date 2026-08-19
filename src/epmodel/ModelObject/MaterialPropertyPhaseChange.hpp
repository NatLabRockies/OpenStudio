/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYPHASECHANGE_HPP
#define EPMODEL_MATERIALPROPERTYPHASECHANGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class MaterialPropertyPhaseChange_Impl;
  }

  /** MaterialPropertyPhaseChange is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:PhaseChange'. */
  /** \brief MaterialPropertyPhaseChange.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#materialpropertyphasechange,MaterialProperty:PhaseChange}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::MaterialPropertyPhaseChange</code>. The temperature-coefficient field is exposed. Model's material relationship and temperature/enthalpy extensible rows are not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API MaterialPropertyPhaseChange : public ModelObject
  {
   public:
    explicit MaterialPropertyPhaseChange(const Model& model);

    virtual ~MaterialPropertyPhaseChange() override = default;
    MaterialPropertyPhaseChange(const MaterialPropertyPhaseChange& other) = default;
    MaterialPropertyPhaseChange(MaterialPropertyPhaseChange&& other) = default;
    MaterialPropertyPhaseChange& operator=(const MaterialPropertyPhaseChange&) = default;
    MaterialPropertyPhaseChange& operator=(MaterialPropertyPhaseChange&&) = default;

    static IddObjectType iddObjectType();
    /** Temperature coefficient for thermal conductivity. */
    double temperatureCoefficientforThermalConductivity() const;
    bool isTemperatureCoefficientforThermalConductivityDefaulted() const;
    bool setTemperatureCoefficientforThermalConductivity(double temperatureCoefficientforThermalConductivity);
    void resetTemperatureCoefficientforThermalConductivity();

   protected:
    using ImplType = detail::MaterialPropertyPhaseChange_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit MaterialPropertyPhaseChange(std::shared_ptr<detail::MaterialPropertyPhaseChange_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
