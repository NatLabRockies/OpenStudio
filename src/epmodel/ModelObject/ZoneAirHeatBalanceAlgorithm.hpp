/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEAIRHEATBALANCEALGORITHM_HPP
#define EPMODEL_ZONEAIRHEATBALANCEALGORITHM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneAirHeatBalanceAlgorithm_Impl;
  }

  class EPMODEL_API ZoneAirHeatBalanceAlgorithm : public ModelObject
  {
   public:
    explicit ZoneAirHeatBalanceAlgorithm(const Model& model);

    virtual ~ZoneAirHeatBalanceAlgorithm() override = default;
    ZoneAirHeatBalanceAlgorithm(const ZoneAirHeatBalanceAlgorithm& other) = default;
    ZoneAirHeatBalanceAlgorithm(ZoneAirHeatBalanceAlgorithm&& other) = default;
    ZoneAirHeatBalanceAlgorithm& operator=(const ZoneAirHeatBalanceAlgorithm&) = default;
    ZoneAirHeatBalanceAlgorithm& operator=(ZoneAirHeatBalanceAlgorithm&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> validAlgorithmValues();

    // Schema Alignment Notes:
    // - API: preserve openstudio::model scalar accessor names/signatures for Algorithm and the Do Space Heat Balance choices.
    // - Field Mapping: Algorithm, Do Space Heat Balance for Sizing, and Do Space Heat Balance for Simulation map directly to
    //   the EnergyPlus ZoneAirHeatBalanceAlgorithm fields via ForwardTranslateZoneAirHeatBalanceAlgorithm.cpp (Yes/No choices).
    // - TODO(parity): expose SimulationControl relationships after scalar saturation is complete.

    std::string algorithm() const;
    bool isAlgorithmDefaulted() const;
    bool setAlgorithm(const std::string& algorithm);
    void resetAlgorithm();

    bool doSpaceHeatBalanceforSizing() const;
    bool isDoSpaceHeatBalanceforSizingDefaulted() const;
    bool setDoSpaceHeatBalanceforSizing(bool doSpaceHeatBalanceforSizing);
    void resetDoSpaceHeatBalanceforSizing();

    bool doSpaceHeatBalanceforSimulation() const;
    bool isDoSpaceHeatBalanceforSimulationDefaulted() const;
    bool setDoSpaceHeatBalanceforSimulation(bool doSpaceHeatBalanceforSimulation);
    void resetDoSpaceHeatBalanceforSimulation();

   protected:
    using ImplType = detail::ZoneAirHeatBalanceAlgorithm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneAirHeatBalanceAlgorithm(std::shared_ptr<detail::ZoneAirHeatBalanceAlgorithm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEAIRHEATBALANCEALGORITHM_HPP
