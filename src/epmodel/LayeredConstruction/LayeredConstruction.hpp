/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LAYEREDCONSTRUCTION_HPP
#define EPMODEL_LAYEREDCONSTRUCTION_HPP

#include "EPModelAPI.hpp"
#include "ConstructionBase/ConstructionBase.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class LayeredConstruction_Impl;
  }

  /** LayeredConstruction is an abstract base class for constructions composed of material layers. */
  class EPMODEL_API LayeredConstruction : public ConstructionBase
  {
   public:
    virtual ~LayeredConstruction() override = default;
    LayeredConstruction(const LayeredConstruction& other) = default;
    LayeredConstruction(LayeredConstruction&& other) = default;
    LayeredConstruction& operator=(const LayeredConstruction&) = default;
    LayeredConstruction& operator=(LayeredConstruction&&) = default;

   protected:
    LayeredConstruction(IddObjectType type, const Model& model);

    using ImplType = detail::LayeredConstruction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit LayeredConstruction(std::shared_ptr<detail::LayeredConstruction_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.LayeredConstruction");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
