/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGFOURPIPEBEAM_HPP
#define EPMODEL_COILHEATINGFOURPIPEBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilHeatingFourPipeBeam_Impl;
  }

  class EPMODEL_API CoilHeatingFourPipeBeam : public StraightComponent
  {
   public:
    explicit CoilHeatingFourPipeBeam(const Model& model);

    virtual ~CoilHeatingFourPipeBeam() override = default;
    CoilHeatingFourPipeBeam(const CoilHeatingFourPipeBeam& other) = default;
    CoilHeatingFourPipeBeam(CoilHeatingFourPipeBeam&& other) = default;
    CoilHeatingFourPipeBeam& operator=(const CoilHeatingFourPipeBeam&) = default;
    CoilHeatingFourPipeBeam& operator=(CoilHeatingFourPipeBeam&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::CoilHeatingFourPipeBeam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingFourPipeBeam(std::shared_ptr<detail::CoilHeatingFourPipeBeam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
