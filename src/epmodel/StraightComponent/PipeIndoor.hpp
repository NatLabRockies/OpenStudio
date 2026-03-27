/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEINDOOR_HPP
#define EPMODEL_PIPEINDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PipeIndoor_Impl;
  }

  class EPMODEL_API PipeIndoor : public StraightComponent
  {
   public:
    explicit PipeIndoor(const Model& model);

    virtual ~PipeIndoor() override = default;
    PipeIndoor(const PipeIndoor& other) = default;
    PipeIndoor(PipeIndoor&& other) = default;
    PipeIndoor& operator=(const PipeIndoor&) = default;
    PipeIndoor& operator=(PipeIndoor&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> environmentTypeValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical scalar pipe surface is present, while construction and ambient-relationship helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::PipeIndoor.
    // - Implemented Parity: `environmentType`, `pipeInsideDiameter`, and `pipeLength` preserve the canonical scalar API surface.
    // - Documented Delta: Construction, ambient zone/schedule helpers, and explicit node-link convenience APIs from canonical `openstudio::model::PipeIndoor` are not exposed yet.
    // - Field/Storage Mapping: The preserved scalar APIs map directly to EnergyPlus `Pipe:Indoor` scalar fields used by the forward translator.
    // - Evidence: `src/model/PipeIndoor.hpp` defines the canonical scalar and relationship surface, and `src/energyplus/ForwardTranslator/ForwardTranslatePipeIndoor.cpp` confirms the direct scalar field mapping.
    // - Remaining Parity Work: Add the omitted construction, ambient-condition, and relationship helpers without changing the preserved scalar signatures.

    /** @name Environment Type */
    //@{
    std::string environmentType() const;
    bool setEnvironmentType(const std::string& environmentType);
    //@}

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
    using ImplType = detail::PipeIndoor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PipeIndoor(std::shared_ptr<detail::PipeIndoor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
