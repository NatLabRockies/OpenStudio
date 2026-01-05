/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_THERMOCHROMICGLAZING_IMPL_HPP
#define MODEL_THERMOCHROMICGLAZING_IMPL_HPP

#include "ModelAPI.hpp"
#include "Glazing.hpp"
#include "Glazing_Impl.hpp"

namespace openstudio {
namespace model {

  class StandardGlazing;
  class ThermochromicGroup;

  namespace detail {

    /** ThermochromicGlazing_Impl is a Glazing_Impl that is the implementation class for ThermochromicGlazing.*/
    class MODEL_API ThermochromicGlazing_Impl : public Glazing_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      ThermochromicGlazing_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      ThermochromicGlazing_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      ThermochromicGlazing_Impl(const ThermochromicGlazing_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~ThermochromicGlazing_Impl() override = default;

      //@}

      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      // Will warn if all the referenced StandardGlazings don't have the same thickness
      virtual double thickness() const override;

      // Will set the thickness of all referenced StandardGlazings
      virtual bool setThickness(double value) override;

      virtual boost::optional<double> getVisibleTransmittance() const override;

      virtual boost::optional<double> interiorVisibleAbsorptance() const override;

      virtual boost::optional<double> exteriorVisibleAbsorptance() const override;

      //@}
      /** @name Getters */
      //@{

      //@}
      /** @name Setters */
      //@{

      //@}
      /** @name Other */
      //@{

      std::vector<ThermochromicGroup> thermochromicGroups() const;

      unsigned int numberofThermochromicGroups() const;

      boost::optional<unsigned> thermochromicGroupIndex(const ThermochromicGroup& thermochromicGroup) const;
      boost::optional<ThermochromicGroup> getThermochromicGroup(unsigned groupIndex) const;

      bool addThermochromicGroup(const ThermochromicGroup& thermochromicGroup);

      // Convenience fucntion that will create a ThermochromicGroup
      bool addThermochromicGroup(const StandardGlazing& standardGlazing, double opticalDataTemperature);

      bool addThermochromicGroups(const std::vector<ThermochromicGroup>& thermochromicGroups);
      bool removeThermochromicGroup(unsigned groupIndex);
      void removeAllThermochromicGroups();

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.ThermochromicGlazing");
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_THERMOCHROMICGLAZING_IMPL_HPP
