/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGFOURPIPEBEAM_HPP
#define EPMODEL_COILCOOLINGFOURPIPEBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingFourPipeBeam_Impl;
  }

  class EPMODEL_API CoilCoolingFourPipeBeam : public StraightComponent
  {
   public:
    explicit CoilCoolingFourPipeBeam(const Model& model);

    virtual ~CoilCoolingFourPipeBeam() override = default;
    CoilCoolingFourPipeBeam(const CoilCoolingFourPipeBeam& other) = default;
    CoilCoolingFourPipeBeam(CoilCoolingFourPipeBeam&& other) = default;
    CoilCoolingFourPipeBeam& operator=(const CoilCoolingFourPipeBeam&) = default;
    CoilCoolingFourPipeBeam& operator=(CoilCoolingFourPipeBeam&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::CoilCoolingFourPipeBeam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingFourPipeBeam(std::shared_ptr<detail::CoilCoolingFourPipeBeam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
