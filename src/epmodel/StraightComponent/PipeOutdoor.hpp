/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEOUTDOOR_HPP
#define EPMODEL_PIPEOUTDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PipeOutdoor_Impl;
  }

  class EPMODEL_API PipeOutdoor : public StraightComponent
  {
   public:
    explicit PipeOutdoor(const Model& model);

    virtual ~PipeOutdoor() override = default;
    PipeOutdoor(const PipeOutdoor& other) = default;
    PipeOutdoor(PipeOutdoor&& other) = default;
    PipeOutdoor& operator=(const PipeOutdoor&) = default;
    PipeOutdoor& operator=(PipeOutdoor&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical scalar pipe surface is present, while construction and ambient-node helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::PipeOutdoor.
    // - Implemented Parity: `pipeInsideDiameter` and `pipeLength` preserve the canonical scalar API surface.
    // - Documented Delta: Construction, ambient outdoor-air node helpers, and explicit node-link convenience APIs from canonical `openstudio::model::PipeOutdoor` are not exposed yet.
    // - Field/Storage Mapping: The preserved scalar APIs map directly to EnergyPlus `Pipe:Outdoor` scalar fields used by the forward translator.
    // - Evidence: `src/model/PipeOutdoor.hpp` defines the canonical scalar and relationship surface, and `src/energyplus/ForwardTranslator/ForwardTranslatePipeOutdoor.cpp` confirms the direct scalar field mapping.
    // - Remaining Parity Work: Add the omitted construction, ambient-node, and relationship helpers without changing the preserved scalar signatures.

    /** @name Pipe Inside Diameter */
    //@{
    double pipeInsideDiameter() const;
    bool setPipeInsideDiameter(double pipeInsideDiameter);
    //@}

    /** @name Pipe Length */
    //@{
    double pipeLength() const;
    bool setPipeLength(double pipeLength);
    //@}

   protected:
    using ImplType = detail::PipeOutdoor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PipeOutdoor(std::shared_ptr<detail::PipeOutdoor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
