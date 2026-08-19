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

  /** \brief OutputControlReportingTolerances.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputcontrolreportingtolerances,OutputControl:ReportingTolerances}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputControlReportingTolerances</code>. The two tolerance fields map directly to EnergyPlus.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputControlReportingTolerances : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputControlReportingTolerances() override = default;
    OutputControlReportingTolerances(const OutputControlReportingTolerances& other) = default;
    OutputControlReportingTolerances(OutputControlReportingTolerances&& other) = default;
    OutputControlReportingTolerances& operator=(const OutputControlReportingTolerances&) = default;
    OutputControlReportingTolerances& operator=(OutputControlReportingTolerances&&) = default;

    static IddObjectType iddObjectType();
    double toleranceforTimeHeatingSetpointNotMet() const;
    bool isToleranceforTimeHeatingSetpointNotMetDefaulted() const;
    bool setToleranceforTimeHeatingSetpointNotMet(double toleranceforTimeHeatingSetpointNotMet);
    void resetToleranceforTimeHeatingSetpointNotMet();

    double toleranceforTimeCoolingSetpointNotMet() const;
    bool isToleranceforTimeCoolingSetpointNotMetDefaulted() const;
    bool setToleranceforTimeCoolingSetpointNotMet(double toleranceforTimeCoolingSetpointNotMet);
    void resetToleranceforTimeCoolingSetpointNotMet();

   protected:
    explicit OutputControlReportingTolerances(const Model& model);

    using ImplType = detail::OutputControlReportingTolerances_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputControlReportingTolerances(std::shared_ptr<detail::OutputControlReportingTolerances_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
