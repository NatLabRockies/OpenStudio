/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONVERGENCELIMITS_HPP
#define EPMODEL_CONVERGENCELIMITS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ConvergenceLimits_Impl;
  }

  class EPMODEL_API ConvergenceLimits : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~ConvergenceLimits() override = default;
    ConvergenceLimits(const ConvergenceLimits& other) = default;
    ConvergenceLimits(ConvergenceLimits&& other) = default;
    ConvergenceLimits& operator=(const ConvergenceLimits&) = default;
    ConvergenceLimits& operator=(ConvergenceLimits&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model ConvergenceLimits scalar accessor names/signatures.
    // - Field Mapping: minimumSystemTimestep and *Plant/*HVAC iteration APIs map directly to E+ ConvergenceLimits fields.
    // - Field Mapping: minimumSystemTimestep constructor default mirrors ForwardTranslator fallback behavior for blank values.
    // - TODO(parity): Keep relationship APIs out of scope for this scalar-only scaffold pass.

    boost::optional<int> minimumSystemTimestep() const;
    bool setMinimumSystemTimestep(int minimumSystemTimestep);
    void resetMinimumSystemTimestep();

    int maximumHVACIterations() const;
    bool isMaximumHVACIterationsDefaulted() const;
    bool setMaximumHVACIterations(int maximumHVACIterations);
    void resetMaximumHVACIterations();

    int minimumPlantIterations() const;
    bool isMinimumPlantIterationsDefaulted() const;
    bool setMinimumPlantIterations(int minimumPlantIterations);
    void resetMinimumPlantIterations();

    int maximumPlantIterations() const;
    bool isMaximumPlantIterationsDefaulted() const;
    bool setMaximumPlantIterations(int maximumPlantIterations);
    void resetMaximumPlantIterations();

   protected:
    explicit ConvergenceLimits(const Model& model);

    using ImplType = detail::ConvergenceLimits_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ConvergenceLimits(std::shared_ptr<detail::ConvergenceLimits_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
