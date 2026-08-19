/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLWATERSUPPLY_HPP
#define EPMODEL_GENERATORFUELCELLWATERSUPPLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCellWaterSupply_Impl;
  }

  /** \brief Represents <code>Generator:FuelCell:WaterSupply</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#generatorfuelcellwatersupply,Generator:FuelCell:WaterSupply}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::GeneratorFuelCellWaterSupply</code>.
   * **Not yet available:** Model parent, node, curve, schedule, and extensible constituent conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * Relationship and extensible data not represented by the public declarations must be maintained by the owning object.
   */
  class EPMODEL_API GeneratorFuelCellWaterSupply : public ModelObject
  {
   public:
    explicit GeneratorFuelCellWaterSupply(const Model& model);

    virtual ~GeneratorFuelCellWaterSupply() override = default;
    GeneratorFuelCellWaterSupply(const GeneratorFuelCellWaterSupply& other) = default;
    GeneratorFuelCellWaterSupply(GeneratorFuelCellWaterSupply&& other) = default;
    GeneratorFuelCellWaterSupply& operator=(const GeneratorFuelCellWaterSupply&) = default;
    GeneratorFuelCellWaterSupply& operator=(GeneratorFuelCellWaterSupply&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> waterTemperatureModelingModeValues();
    double pumpHeatLossFactor() const;
    bool setPumpHeatLossFactor(double pumpHeatLossFactor);
    void resetPumpHeatLossFactor();

    std::string waterTemperatureModelingMode() const;
    bool setWaterTemperatureModelingMode(const std::string& waterTemperatureModelingMode);
    void resetWaterTemperatureModelingMode();

   protected:
    using ImplType = detail::GeneratorFuelCellWaterSupply_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellWaterSupply(std::shared_ptr<detail::GeneratorFuelCellWaterSupply_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
