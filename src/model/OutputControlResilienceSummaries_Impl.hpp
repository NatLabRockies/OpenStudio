/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_OUTPUTCONTROLRESILIENCESUMMARIES_IMPL_HPP
#define MODEL_OUTPUTCONTROLRESILIENCESUMMARIES_IMPL_HPP

#include <model/ModelAPI.hpp>
#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    /** OutputControlResilienceSummaries_Impl is a ModelObject_Impl that is the implementation class for OutputControlResilienceSummaries.*/
    class MODEL_API OutputControlResilienceSummaries_Impl : public ModelObject_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      OutputControlResilienceSummaries_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      OutputControlResilienceSummaries_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      OutputControlResilienceSummaries_Impl(const OutputControlResilienceSummaries_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~OutputControlResilienceSummaries_Impl() override = default;

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      //@}
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
     private:
      REGISTER_LOGGER("openstudio.model.OutputControlResilienceSummaries");
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_OUTPUTCONTROLRESILIENCESUMMARIES_IMPL_HPP
