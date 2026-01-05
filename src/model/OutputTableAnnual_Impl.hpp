/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_OUTPUTTABLEANNUAL_IMPL_HPP
#define MODEL_OUTPUTTABLEANNUAL_IMPL_HPP

#include <model/ModelAPI.hpp>
#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace model {

  class AnnualVariableGroup;
  class Schedule;

  namespace detail {

    /** OutputTableAnnual_Impl is a ModelObject_Impl that is the implementation class for OutputTableAnnual.*/
    class MODEL_API OutputTableAnnual_Impl : public ModelObject_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      OutputTableAnnual_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      OutputTableAnnual_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      OutputTableAnnual_Impl(const OutputTableAnnual_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~OutputTableAnnual_Impl() override = default;

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

      //@}
      /** @name Getters */
      //@{

      boost::optional<std::string> filter() const;

      boost::optional<Schedule> schedule() const;

      //@}
      /** @name Setters */
      //@{

      bool setFilter(const std::string& filter);

      void resetFilter();

      bool setSchedule(Schedule& schedule);

      void resetSchedule();

      //@}
      /** @name Other */
      //@{

      // Handle this object's extensible fields.
      std::vector<AnnualVariableGroup> annualVariableGroups() const;

      unsigned int numberofAnnualVariableGroups() const;

      boost::optional<unsigned> annualVariableGroupIndex(const AnnualVariableGroup& annualVariableGroup) const;
      boost::optional<AnnualVariableGroup> getAnnualVariableGroup(unsigned groupIndex) const;

      bool addAnnualVariableGroup(const AnnualVariableGroup& annualVariableGroup);
      bool addAnnualVariableGroups(const std::vector<AnnualVariableGroup>& annualVariableGroups);
      bool removeAnnualVariableGroup(unsigned groupIndex);
      void removeAllAnnualVariableGroups();

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.OutputTableAnnual");
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_OUTPUTTABLEANNUAL_IMPL_HPP
