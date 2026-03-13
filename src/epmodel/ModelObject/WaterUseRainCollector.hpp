/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSERAINCOLLECTOR_HPP
#define EPMODEL_WATERUSERAINCOLLECTOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WaterUseRainCollector_Impl;
  }

  class EPMODEL_API WaterUseRainCollector : public ModelObject
  {
   public:
    explicit WaterUseRainCollector(const Model& model);

    virtual ~WaterUseRainCollector() override = default;
    WaterUseRainCollector(const WaterUseRainCollector& other) = default;
    WaterUseRainCollector(WaterUseRainCollector&& other) = default;
    WaterUseRainCollector& operator=(const WaterUseRainCollector&) = default;
    WaterUseRainCollector& operator=(WaterUseRainCollector&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> lossFactorModeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type preserves IDD-derived naming for WaterUse:RainCollector.
    // - Field Mapping: Scalar APIs map directly to WaterUse:RainCollector fields via WaterUse_RainCollectorFields (Loss Factor Mode, Collection Loss Factor, Maximum Collection Rate).
    // - Field Mapping: Storage Tank Name, Collection Loss Factor Schedule Name, and Collection Surface Name remain object-list relationships and are excluded from scalar accessors.
    // - TODO(parity): Add relationship helpers after scalar saturation without shifting scalar signatures.

    // Loss Factor Mode
    boost::optional<std::string> lossFactorMode() const;
    bool setLossFactorMode(const std::string& lossFactorMode);

    // Collection Loss Factor
    boost::optional<double> collectionLossFactor() const;
    bool setCollectionLossFactor(double collectionLossFactor);

    // Maximum Collection Rate
    boost::optional<double> maximumCollectionRate() const;
    bool setMaximumCollectionRate(double maximumCollectionRate);

   protected:
    using ImplType = detail::WaterUseRainCollector_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterUseRainCollector(std::shared_ptr<detail::WaterUseRainCollector_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
