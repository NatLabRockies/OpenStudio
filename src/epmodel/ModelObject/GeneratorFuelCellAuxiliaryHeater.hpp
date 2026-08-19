/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLAUXILIARYHEATER_HPP
#define EPMODEL_GENERATORFUELCELLAUXILIARYHEATER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCellAuxiliaryHeater_Impl;
  }

  /** \brief Represents <code>Generator:FuelCell:AuxiliaryHeater</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#generatorfuelcellauxiliaryheater,Generator:FuelCell:AuxiliaryHeater}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::GeneratorFuelCellAuxiliaryHeater</code>.
   * **Not yet available:** Model parent, node, curve, schedule, and extensible constituent conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * Relationship and extensible data not represented by the public declarations must be maintained by the owning object.
   */
  class EPMODEL_API GeneratorFuelCellAuxiliaryHeater : public ModelObject
  {
   public:
    explicit GeneratorFuelCellAuxiliaryHeater(const Model& model);

    virtual ~GeneratorFuelCellAuxiliaryHeater() override = default;
    GeneratorFuelCellAuxiliaryHeater(const GeneratorFuelCellAuxiliaryHeater& other) = default;
    GeneratorFuelCellAuxiliaryHeater(GeneratorFuelCellAuxiliaryHeater&& other) = default;
    GeneratorFuelCellAuxiliaryHeater& operator=(const GeneratorFuelCellAuxiliaryHeater&) = default;
    GeneratorFuelCellAuxiliaryHeater& operator=(GeneratorFuelCellAuxiliaryHeater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> skinLossDestinationValues();
    static std::vector<std::string> heatingCapacityUnitsValues();
    double excessAirRatio() const;
    bool setExcessAirRatio(double excessAirRatio);
    void resetExcessAirRatio();

    double ancillaryPowerConstantTerm() const;
    bool setAncillaryPowerConstantTerm(double ancillaryPowerConstantTerm);
    void resetAncillaryPowerConstantTerm();

    double ancillaryPowerLinearTerm() const;
    bool setAncillaryPowerLinearTerm(double ancillaryPowerLinearTerm);
    void resetAncillaryPowerLinearTerm();

    double skinLossUFactorTimesAreaValue() const;
    bool setSkinLossUFactorTimesAreaValue(double skinLossUFactorTimesAreaValue);
    void resetSkinLossUFactorTimesAreaValue();

    std::string skinLossDestination() const;
    bool setSkinLossDestination(const std::string& skinLossDestination);
    void resetSkinLossDestination();

    std::string heatingCapacityUnits() const;
    bool setHeatingCapacityUnits(const std::string& heatingCapacityUnits);
    void resetHeatingCapacityUnits();

    double maximumHeatingCapacityinWatts() const;
    bool setMaximumHeatingCapacityinWatts(double maximumHeatingCapacityinWatts);
    void resetMaximumHeatingCapacityinWatts();

    double minimumHeatingCapacityinWatts() const;
    bool setMinimumHeatingCapacityinWatts(double minimumHeatingCapacityinWatts);
    void resetMinimumHeatingCapacityinWatts();

    double maximumHeatingCapacityinKmolperSecond() const;
    bool setMaximumHeatingCapacityinKmolperSecond(double maximumHeatingCapacityinKmolperSecond);
    void resetMaximumHeatingCapacityinKmolperSecond();

    double minimumHeatingCapacityinKmolperSecond() const;
    bool setMinimumHeatingCapacityinKmolperSecond(double minimumHeatingCapacityinKmolperSecond);
    void resetMinimumHeatingCapacityinKmolperSecond();

   protected:
    using ImplType = detail::GeneratorFuelCellAuxiliaryHeater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellAuxiliaryHeater(std::shared_ptr<detail::GeneratorFuelCellAuxiliaryHeater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
