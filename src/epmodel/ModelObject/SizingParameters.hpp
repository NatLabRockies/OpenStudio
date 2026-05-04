/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPARAMETERS_HPP
#define EPMODEL_SIZINGPARAMETERS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SizingParameters_Impl;
  }

  class EPMODEL_API SizingParameters : public ModelObject
  {
   public:
    virtual ~SizingParameters() override = default;
    SizingParameters(const SizingParameters& other) = default;
    SizingParameters(SizingParameters&& other) = default;
    SizingParameters& operator=(const SizingParameters&) = default;
    SizingParameters& operator=(SizingParameters&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model SizingParameters scalar accessor names/signatures.
    // - Field Mapping: heatingSizingFactor, coolingSizingFactor, and timestepsinAveragingWindow map directly to E+ Sizing:Parameters fields.
    // - Field Mapping: ForwardTranslator evidence confirms direct mapping for these three scalar fields.
    // - API: Sizing factor default values follow E+ Sizing:Parameters IDD defaults in epmodel.
    // - TODO(parity): Keep scalar-only scope for this pass; relationship/object-link behavior is out of scope.
    double heatingSizingFactor() const;
    bool isHeatingSizingFactorDefaulted() const;
    bool setHeatingSizingFactor(double heatingSizingFactor);
    void resetHeatingSizingFactor();

    double coolingSizingFactor() const;
    bool isCoolingSizingFactorDefaulted() const;
    bool setCoolingSizingFactor(double coolingSizingFactor);
    void resetCoolingSizingFactor();

    boost::optional<int> timestepsinAveragingWindow() const;
    bool setTimestepsinAveragingWindow(int timestepsinAveragingWindow);
    void resetTimestepsinAveragingWindow();

   protected:
    explicit SizingParameters(const Model& model);

    using ImplType = detail::SizingParameters_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SizingParameters(std::shared_ptr<detail::SizingParameters_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
