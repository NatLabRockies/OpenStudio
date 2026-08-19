/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLRESILIENCESUMMARIES_HPP
#define EPMODEL_OUTPUTCONTROLRESILIENCESUMMARIES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputControlResilienceSummaries_Impl;
  }

  /** \brief OutputControlResilienceSummaries.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#OutputControlResilienceSummaries,OutputControl:ResilienceSummaries}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputControlResilienceSummaries</code>. The heat-index algorithm field and its valid-value helpers are exposed.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputControlResilienceSummaries : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputControlResilienceSummaries() override = default;
    OutputControlResilienceSummaries(const OutputControlResilienceSummaries& other) = default;
    OutputControlResilienceSummaries(OutputControlResilienceSummaries&& other) = default;
    OutputControlResilienceSummaries& operator=(const OutputControlResilienceSummaries&) = default;
    OutputControlResilienceSummaries& operator=(OutputControlResilienceSummaries&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatIndexAlgorithmValues();
    static std::vector<std::string> validHeatIndexAlgorithmValues();

    /** @name Getters */
    //@{
    std::string heatIndexAlgorithm() const;
    //@}

    /** @name Setters */
    //@{
    bool setHeatIndexAlgorithm(const std::string& heatIndexAlgorithm);
    //@}

   protected:
    explicit OutputControlResilienceSummaries(const Model& model);

    using ImplType = detail::OutputControlResilienceSummaries_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputControlResilienceSummaries(std::shared_ptr<detail::OutputControlResilienceSummaries_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
