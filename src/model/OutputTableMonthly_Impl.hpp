/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_OUTPUTTABLEMONTHLY_IMPL_HPP
#define MODEL_OUTPUTTABLEMONTHLY_IMPL_HPP

#include <model/ModelAPI.hpp>
#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace model {

  class MonthlyVariableGroup;

  namespace detail {

    /** OutputTableMonthly_Impl is a ModelObject_Impl that is the implementation class for OutputTableMonthly.*/
    class MODEL_API OutputTableMonthly_Impl : public ModelObject_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      OutputTableMonthly_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      OutputTableMonthly_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      OutputTableMonthly_Impl(const OutputTableMonthly_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~OutputTableMonthly_Impl() override = default;

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      //@}
      /** @name Getters */
      //@{

      int digitsAfterDecimal() const;

      //@}
      /** @name Setters */
      //@{

      bool setDigitsAfterDecimal(int digitsAfterDecimal);

      //@}
      /** @name Other */
      //@{

      // Handle this object's extensible fields.
      std::vector<MonthlyVariableGroup> monthlyVariableGroups() const;

      unsigned int numberofMonthlyVariableGroups() const;

      boost::optional<unsigned> monthlyVariableGroupIndex(const MonthlyVariableGroup& monthlyVariableGroup) const;
      boost::optional<MonthlyVariableGroup> getMonthlyVariableGroup(unsigned groupIndex) const;

      bool addMonthlyVariableGroup(const MonthlyVariableGroup& monthlyVariableGroup);
      bool addMonthlyVariableGroups(const std::vector<MonthlyVariableGroup>& monthlyVariableGroups);
      bool removeMonthlyVariableGroup(unsigned groupIndex);
      void removeAllMonthlyVariableGroups();

      static const std::vector<std::pair<std::string, std::vector<MonthlyVariableGroup>>>& standardReports();
      static const std::vector<std::string>& validStandardReportNames();
      static const std::vector<MonthlyVariableGroup>& getGroupsForStandardReport(const std::string& standardReportName);

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.OutputTableMonthly");
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_OUTPUTTABLEMONTHLY_IMPL_HPP
