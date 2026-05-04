/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGCOOLEDBEAM_HPP
#define EPMODEL_COILCOOLINGCOOLEDBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingCooledBeam_Impl;
  }

  class EPMODEL_API CoilCoolingCooledBeam : public StraightComponent
  {
   public:
    explicit CoilCoolingCooledBeam(const Model& model);

    virtual ~CoilCoolingCooledBeam() override = default;
    CoilCoolingCooledBeam(const CoilCoolingCooledBeam& other) = default;
    CoilCoolingCooledBeam(CoilCoolingCooledBeam&& other) = default;
    CoilCoolingCooledBeam& operator=(const CoilCoolingCooledBeam&) = default;
    CoilCoolingCooledBeam& operator=(CoilCoolingCooledBeam&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::CoilCoolingCooledBeam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingCooledBeam(std::shared_ptr<detail::CoilCoolingCooledBeam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
