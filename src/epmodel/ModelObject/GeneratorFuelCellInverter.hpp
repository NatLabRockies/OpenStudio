/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLINVERTER_HPP
#define EPMODEL_GENERATORFUELCELLINVERTER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCellInverter_Impl;
  }

  /** \brief Represents <code>Generator:FuelCell:Inverter</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#generatorfuelcellinverter,Generator:FuelCell:Inverter}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::GeneratorFuelCellInverter</code>.
   * **Not yet available:** Model parent, node, curve, schedule, and extensible constituent conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * Relationship and extensible data not represented by the public declarations must be maintained by the owning object.
   */
  class EPMODEL_API GeneratorFuelCellInverter : public ModelObject
  {
   public:
    explicit GeneratorFuelCellInverter(const Model& model);

    virtual ~GeneratorFuelCellInverter() override = default;
    GeneratorFuelCellInverter(const GeneratorFuelCellInverter& other) = default;
    GeneratorFuelCellInverter(GeneratorFuelCellInverter&& other) = default;
    GeneratorFuelCellInverter& operator=(const GeneratorFuelCellInverter&) = default;
    GeneratorFuelCellInverter& operator=(GeneratorFuelCellInverter&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> inverterEfficiencyCalculationModeValues();
    std::string inverterEfficiencyCalculationMode() const;
    bool setInverterEfficiencyCalculationMode(const std::string& inverterEfficiencyCalculationMode);
    void resetInverterEfficiencyCalculationMode();

    double inverterEfficiency() const;
    bool setInverterEfficiency(double inverterEfficiency);
    void resetInverterEfficiency();

   protected:
    using ImplType = detail::GeneratorFuelCellInverter_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellInverter(std::shared_ptr<detail::GeneratorFuelCellInverter_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
