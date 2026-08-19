/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEADIABATIC_HPP
#define EPMODEL_PIPEADIABATIC_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PipeAdiabatic_Impl;
  }

/** \brief An adiabatic plant pipe.
 *
 * \par EnergyPlus object
 * \epobject{group-node-branch-management.html#pipeadiabatic,Pipe:Adiabatic}
 *
 * \par Important behavior
 * The inherited straight-component inlet/outlet topology maps to Pipe:Adiabatic.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::PipeAdiabatic</code>.
 *
 * \par Known limitations
 * No type-specific scalar API is provided.
 */
  class EPMODEL_API PipeAdiabatic : public StraightComponent
  {
   public:
    explicit PipeAdiabatic(const Model& model);

    virtual ~PipeAdiabatic() override = default;
    PipeAdiabatic(const PipeAdiabatic& other) = default;
    PipeAdiabatic(PipeAdiabatic&& other) = default;
    PipeAdiabatic& operator=(const PipeAdiabatic&) = default;
    PipeAdiabatic& operator=(PipeAdiabatic&&) = default;

    unsigned inletPort() const;
    unsigned outletPort() const;

    static IddObjectType iddObjectType();


   protected:
    using ImplType = detail::PipeAdiabatic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PipeAdiabatic(std::shared_ptr<detail::PipeAdiabatic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
