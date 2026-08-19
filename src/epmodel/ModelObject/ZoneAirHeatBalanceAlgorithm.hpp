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

  /** \brief ZoneAirHeatBalanceAlgorithm.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#zoneairheatbalancealgorithm,ZoneAirHeatBalanceAlgorithm}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneAirHeatBalanceAlgorithm</code>. The algorithm and heat-balance switches map directly to EnergyPlus. Simulation-control relationships are not exposed.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ZoneAirHeatBalanceAlgorithm : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~ZoneAirHeatBalanceAlgorithm() override = default;
    ZoneAirHeatBalanceAlgorithm(const ZoneAirHeatBalanceAlgorithm& other) = default;
    ZoneAirHeatBalanceAlgorithm(ZoneAirHeatBalanceAlgorithm&& other) = default;
    ZoneAirHeatBalanceAlgorithm& operator=(const ZoneAirHeatBalanceAlgorithm&) = default;
    ZoneAirHeatBalanceAlgorithm& operator=(ZoneAirHeatBalanceAlgorithm&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> validAlgorithmValues();

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
    explicit ZoneAirHeatBalanceAlgorithm(const Model& model);

    using ImplType = detail::ZoneAirHeatBalanceAlgorithm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneAirHeatBalanceAlgorithm(std::shared_ptr<detail::ZoneAirHeatBalanceAlgorithm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEAIRHEATBALANCEALGORITHM_HPP
