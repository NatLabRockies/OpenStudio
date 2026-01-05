/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_THERMOCHROMICGLAZING_HPP
#define MODEL_THERMOCHROMICGLAZING_HPP

#include "ModelAPI.hpp"
#include "Glazing.hpp"
#include "StandardGlazing.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    class ThermochromicGlazing_Impl;

  }  // namespace detail

  /** This class implements a Thermochromic Group */
  class MODEL_API ThermochromicGroup
  {
   public:
    /* Only accepts ModelObjects that are of type Surface, Subsurface or InternalMass, will throw otherwise */
    ThermochromicGroup(const StandardGlazing& standardGlazing, double opticalDataTemperature);

    StandardGlazing standardGlazing() const;
    double opticalDataTemperature() const;

    // Equality is defined as having the same StandardGlazing **OR** has having equal opticalDataTemperature with epsilon tolerance
    // Meaning we enforce both unitcity of StandardGlazing and opticalDataTemperature
    bool operator==(const ThermochromicGroup& other) const;
    bool operator!=(const ThermochromicGroup& other) const;

    // Sort order is defined by the opticalDataTemperature only, used in FT to ensure that the groups are sorted by temperature
    bool operator<(const ThermochromicGroup& other) const;
    bool operator>(const ThermochromicGroup& other) const;
    bool operator<=(const ThermochromicGroup& other) const;
    bool operator>=(const ThermochromicGroup& other) const;

   private:
    // From
    StandardGlazing m_standardGlazing;
    double m_opticalDataTemperature;
    REGISTER_LOGGER("openstudio.model.ThermochromicGroup");
  };

  // Overload operator<<
  MODEL_API std::ostream& operator<<(std::ostream& out, const openstudio::model::ThermochromicGroup& thermochromicGroup);

  /** ThermochromicGlazing is a Glazing that wraps the OpenStudio IDD object 'OS:WindowMaterial:GlazingGroup:Thermochromic'. */
  class MODEL_API ThermochromicGlazing : public Glazing
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit ThermochromicGlazing(const Model& model);

    virtual ~ThermochromicGlazing() override = default;
    // Default the copy and move operators because the virtual dtor is explicit
    ThermochromicGlazing(const ThermochromicGlazing& other) = default;
    ThermochromicGlazing(ThermochromicGlazing&& other) = default;
    ThermochromicGlazing& operator=(const ThermochromicGlazing&) = default;
    ThermochromicGlazing& operator=(ThermochromicGlazing&&) = default;

    //@}

    static IddObjectType iddObjectType();

    /** @name Getters */
    //@{

    //@}
    /** @name Setters */
    //@{

    //@}
    /** @name Other */
    //@{

    // Handle this object's extensible fields.

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
    /// @cond
    using ImplType = detail::ThermochromicGlazing_Impl;

    explicit ThermochromicGlazing(std::shared_ptr<detail::ThermochromicGlazing_Impl> impl);

    friend class detail::ThermochromicGlazing_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.ThermochromicGlazing");
  };

  /** \relates ThermochromicGlazing*/
  using OptionalThermochromicGlazing = boost::optional<ThermochromicGlazing>;

  /** \relates ThermochromicGlazing*/
  using ThermochromicGlazingVector = std::vector<ThermochromicGlazing>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_THERMOCHROMICGLAZING_HPP
