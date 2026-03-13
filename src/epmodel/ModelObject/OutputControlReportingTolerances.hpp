/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLREPORTINGTOLERANCES_HPP
#define EPMODEL_OUTPUTCONTROLREPORTINGTOLERANCES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputControlReportingTolerances_Impl;
  }

  class EPMODEL_API OutputControlReportingTolerances : public ModelObject
  {
   public:
    explicit OutputControlReportingTolerances(const Model& model);

    virtual ~OutputControlReportingTolerances() override = default;
    OutputControlReportingTolerances(const OutputControlReportingTolerances& other) = default;
    OutputControlReportingTolerances(OutputControlReportingTolerances&& other) = default;
    OutputControlReportingTolerances& operator=(const OutputControlReportingTolerances&) = default;
    OutputControlReportingTolerances& operator=(OutputControlReportingTolerances&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputControlReportingTolerances accessor names/signatures.
    // - Field Mapping: toleranceforTimeHeatingSetpointNotMet and toleranceforTimeCoolingSetpointNotMet map directly to
    //   E+ OutputControl:ReportingTolerances scalar fields.
    // - ForwardTranslator evidence: model ForwardTranslateOutputControlReportingTolerances.cpp uses these same scalar APIs
    //   and maps directly to the same EnergyPlus field names.
    // - TODO(parity): Keep scalar API stable while adding broader parity behavior in future passes.
    double toleranceforTimeHeatingSetpointNotMet() const;
    bool isToleranceforTimeHeatingSetpointNotMetDefaulted() const;
    bool setToleranceforTimeHeatingSetpointNotMet(double toleranceforTimeHeatingSetpointNotMet);
    void resetToleranceforTimeHeatingSetpointNotMet();

    double toleranceforTimeCoolingSetpointNotMet() const;
    bool isToleranceforTimeCoolingSetpointNotMetDefaulted() const;
    bool setToleranceforTimeCoolingSetpointNotMet(double toleranceforTimeCoolingSetpointNotMet);
    void resetToleranceforTimeCoolingSetpointNotMet();

   protected:
    using ImplType = detail::OutputControlReportingTolerances_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputControlReportingTolerances(std::shared_ptr<detail::OutputControlReportingTolerances_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
