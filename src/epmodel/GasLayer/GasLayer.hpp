/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GASLAYER_HPP
#define EPMODEL_GASLAYER_HPP

#include "EPModelAPI.hpp"
#include "FenestrationMaterial/FenestrationMaterial.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class GasLayer_Impl;
  }

  /** A GasLayer is a FenestrationMaterial that serves as a base class for gaseous layers in
   *  fenestration LayeredConstructions (e.g. the gas gap between panes of glass). */
  class EPMODEL_API GasLayer : public FenestrationMaterial
  {
   public:
    virtual ~GasLayer() override = default;
    GasLayer(const GasLayer& other) = default;
    GasLayer(GasLayer&& other) = default;
    GasLayer& operator=(const GasLayer&) = default;
    GasLayer& operator=(GasLayer&&) = default;

   protected:
    using ImplType = detail::GasLayer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    GasLayer(IddObjectType type, const Model& model);

    explicit GasLayer(std::shared_ptr<detail::GasLayer_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.GasLayer");
  };

  using OptionalGasLayer = boost::optional<GasLayer>;
  using GasLayerVector = std::vector<GasLayer>;

}  // namespace epmodel
}  // namespace openstudio

#endif
