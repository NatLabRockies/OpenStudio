/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_OUTPUTCONTROLRESILIENCESUMMARIES_HPP
#define MODEL_OUTPUTCONTROLRESILIENCESUMMARIES_HPP

#include <model/ModelAPI.hpp>
#include "ModelObject.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    class OutputControlResilienceSummaries_Impl;

  }  // namespace detail

  /** OutputControlResilienceSummaries is a ModelObject that wraps the OpenStudio IDD object 'OS:OutputControl:ResilienceSummaries'. */
  class MODEL_API OutputControlResilienceSummaries : public ModelObject
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    virtual ~OutputControlResilienceSummaries() override = default;
    // Default the copy and move operators because the virtual dtor is explicit
    OutputControlResilienceSummaries(const OutputControlResilienceSummaries& other) = default;
    OutputControlResilienceSummaries(OutputControlResilienceSummaries&& other) = default;
    OutputControlResilienceSummaries& operator=(const OutputControlResilienceSummaries&) = default;
    OutputControlResilienceSummaries& operator=(OutputControlResilienceSummaries&&) = default;

    //@}

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
    /** @name Other */
    //@{

    //@}
   protected:
    /// @cond
    using ImplType = detail::OutputControlResilienceSummaries_Impl;

    explicit OutputControlResilienceSummaries(std::shared_ptr<detail::OutputControlResilienceSummaries_Impl> impl);

    friend class detail::OutputControlResilienceSummaries_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    explicit OutputControlResilienceSummaries(Model& model);

    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.OutputControlResilienceSummaries");
  };

  /** \relates OutputControlResilienceSummaries*/
  using OptionalOutputControlResilienceSummaries = boost::optional<OutputControlResilienceSummaries>;

  /** \relates OutputControlResilienceSummaries*/
  using OutputControlResilienceSummariesVector = std::vector<OutputControlResilienceSummaries>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_OUTPUTCONTROLRESILIENCESUMMARIES_HPP
