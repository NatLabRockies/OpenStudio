/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATBALANCEALGORITHM_HPP
#define EPMODEL_HEATBALANCEALGORITHM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatBalanceAlgorithm_Impl;
  }

  class EPMODEL_API HeatBalanceAlgorithm : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~HeatBalanceAlgorithm() override = default;
    HeatBalanceAlgorithm(const HeatBalanceAlgorithm& other) = default;
    HeatBalanceAlgorithm(HeatBalanceAlgorithm&& other) = default;
    HeatBalanceAlgorithm& operator=(const HeatBalanceAlgorithm&) = default;
    HeatBalanceAlgorithm& operator=(HeatBalanceAlgorithm&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> algorithmValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model HeatBalanceAlgorithm scalar accessor names/signatures.
    // - Field Mapping: algorithm and convection/temperature scalar APIs map directly to E+ HeatBalanceAlgorithm fields.
    // - Field Mapping: ForwardTranslateHeatBalanceAlgorithm confirms direct pass-through for algorithm and numeric scalar fields.
    // - Field Mapping: constructor defaults for algorithm and surfaceTemperatureUpperLimit mirror existing model behavior.
    // - TODO(parity): Keep non-scalar relationship behavior out of scope for this scaffold pass.
    std::string algorithm() const;
    bool isAlgorithmDefaulted() const;
    bool setAlgorithm(const std::string& algorithm);
    void resetAlgorithm();

    double surfaceTemperatureUpperLimit() const;
    bool isSurfaceTemperatureUpperLimitDefaulted() const;
    bool setSurfaceTemperatureUpperLimit(double surfaceTemperatureUpperLimit);
    void resetSurfaceTemperatureUpperLimit();

    double minimumSurfaceConvectionHeatTransferCoefficientValue() const;
    bool isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const;
    bool setMinimumSurfaceConvectionHeatTransferCoefficientValue(double minimumSurfaceConvectionHeatTransferCoefficientValue);
    void resetMinimumSurfaceConvectionHeatTransferCoefficientValue();

    double maximumSurfaceConvectionHeatTransferCoefficientValue() const;
    bool isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const;
    bool setMaximumSurfaceConvectionHeatTransferCoefficientValue(double maximumSurfaceConvectionHeatTransferCoefficientValue);
    void resetMaximumSurfaceConvectionHeatTransferCoefficientValue();

   protected:
    explicit HeatBalanceAlgorithm(const Model& model);

    using ImplType = detail::HeatBalanceAlgorithm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatBalanceAlgorithm(std::shared_ptr<detail::HeatBalanceAlgorithm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
