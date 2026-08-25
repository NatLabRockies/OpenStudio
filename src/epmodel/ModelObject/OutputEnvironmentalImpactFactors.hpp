/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTENVIRONMENTALIMPACTFACTORS_HPP
#define EPMODEL_OUTPUTENVIRONMENTALIMPACTFACTORS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputEnvironmentalImpactFactors_Impl;
  }

  /** \brief OutputEnvironmentalImpactFactors.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputenvironmentalimpactfactors,Output:EnvironmentalImpactFactors}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputEnvironmentalImpactFactors</code>. The reporting-frequency field maps directly to EnergyPlus.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputEnvironmentalImpactFactors : public ModelObject
  {
   public:
    explicit OutputEnvironmentalImpactFactors(const Model& model);

    virtual ~OutputEnvironmentalImpactFactors() override = default;
    OutputEnvironmentalImpactFactors(const OutputEnvironmentalImpactFactors& other) = default;
    OutputEnvironmentalImpactFactors(OutputEnvironmentalImpactFactors&& other) = default;
    OutputEnvironmentalImpactFactors& operator=(const OutputEnvironmentalImpactFactors&) = default;
    OutputEnvironmentalImpactFactors& operator=(OutputEnvironmentalImpactFactors&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> reportingFrequencyValues();
    /** @name Reporting frequency scalar */
    //@{
    std::string reportingFrequency() const;

    bool setReportingFrequency(const std::string& reportingFrequency);
    //@}

   protected:
    using ImplType = detail::OutputEnvironmentalImpactFactors_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputEnvironmentalImpactFactors(std::shared_ptr<detail::OutputEnvironmentalImpactFactors_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
