/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLELECTRICALSTORAGE_HPP
#define EPMODEL_GENERATORFUELCELLELECTRICALSTORAGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCellElectricalStorage_Impl;
  }

  /** \brief Represents <code>Generator:FuelCell:ElectricalStorage</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#generatorfuelcellelectricalstorage,Generator:FuelCell:ElectricalStorage}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::GeneratorFuelCellElectricalStorage</code>.
   * **Not yet available:** Model parent, node, curve, schedule, and extensible constituent conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * Relationship and extensible data not represented by the public declarations must be maintained by the owning object.
   */
  class EPMODEL_API GeneratorFuelCellElectricalStorage : public ModelObject
  {
   public:
    explicit GeneratorFuelCellElectricalStorage(const Model& model);

    virtual ~GeneratorFuelCellElectricalStorage() override = default;
    GeneratorFuelCellElectricalStorage(const GeneratorFuelCellElectricalStorage& other) = default;
    GeneratorFuelCellElectricalStorage(GeneratorFuelCellElectricalStorage&& other) = default;
    GeneratorFuelCellElectricalStorage& operator=(const GeneratorFuelCellElectricalStorage&) = default;
    GeneratorFuelCellElectricalStorage& operator=(GeneratorFuelCellElectricalStorage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> choiceofModelValues();
    std::string choiceofModel() const;
    bool setChoiceofModel(const std::string& choiceofModel);
    void resetChoiceofModel();

    double nominalChargingEnergeticEfficiency() const;
    bool setNominalChargingEnergeticEfficiency(double nominalChargingEnergeticEfficiency);
    void resetNominalChargingEnergeticEfficiency();

    double nominalDischargingEnergeticEfficiency() const;
    bool setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency);
    void resetNominalDischargingEnergeticEfficiency();

    double simpleMaximumCapacity() const;
    bool setSimpleMaximumCapacity(double simpleMaximumCapacity);
    void resetSimpleMaximumCapacity();

    double simpleMaximumPowerDraw() const;
    bool setSimpleMaximumPowerDraw(double simpleMaximumPowerDraw);
    void resetSimpleMaximumPowerDraw();

    double simpleMaximumPowerStore() const;
    bool setSimpleMaximumPowerStore(double simpleMaximumPowerStore);
    void resetSimpleMaximumPowerStore();

    double initialChargeState() const;
    bool setInitialChargeState(double initialChargeState);
    void resetInitialChargeState();

   protected:
    using ImplType = detail::GeneratorFuelCellElectricalStorage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellElectricalStorage(std::shared_ptr<detail::GeneratorFuelCellElectricalStorage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
