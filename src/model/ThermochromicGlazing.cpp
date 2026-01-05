/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermochromicGlazing.hpp"
#include "ThermochromicGlazing_Impl.hpp"
#include "StandardGlazing.hpp"
#include "StandardGlazing_Impl.hpp"
#include "ModelExtensibleGroup.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/math/FloatCompare.hpp"

#include <utilities/idd/OS_WindowMaterial_GlazingGroup_Thermochromic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace model {

  // Helper class for the extensible groups
  ThermochromicGroup::ThermochromicGroup(const StandardGlazing& standardGlazing, double opticalDataTemperature)
    : m_standardGlazing(standardGlazing), m_opticalDataTemperature(opticalDataTemperature) {}

  StandardGlazing ThermochromicGroup::standardGlazing() const {
    return m_standardGlazing;
  }

  double ThermochromicGroup::opticalDataTemperature() const {
    return m_opticalDataTemperature;
  }

  bool ThermochromicGroup::operator==(const ThermochromicGroup& other) const {
    return (standardGlazing() == other.standardGlazing()) || openstudio::equal(opticalDataTemperature(), other.opticalDataTemperature());
  }

  bool ThermochromicGroup::operator!=(const ThermochromicGroup& other) const {
    return (!operator==(other));
  }

  bool ThermochromicGroup::operator<(const ThermochromicGroup& other) const {
    return opticalDataTemperature() < other.opticalDataTemperature();
  }

  bool ThermochromicGroup::operator>(const ThermochromicGroup& other) const {
    return opticalDataTemperature() > other.opticalDataTemperature();
  }

  bool ThermochromicGroup::operator<=(const ThermochromicGroup& other) const {
    return opticalDataTemperature() <= other.opticalDataTemperature();
  }

  bool ThermochromicGroup::operator>=(const ThermochromicGroup& other) const {
    return opticalDataTemperature() >= other.opticalDataTemperature();
  }

  std::ostream& operator<<(std::ostream& out, const openstudio::model::ThermochromicGroup& thermochromicGroup) {
    out << "(StandardGlazing = '" << thermochromicGroup.standardGlazing().nameString()
        << "', Optional Data Temperature = " << thermochromicGroup.opticalDataTemperature() << ")";
    return out;
  }

  namespace detail {

    ThermochromicGlazing_Impl::ThermochromicGlazing_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : Glazing_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == ThermochromicGlazing::iddObjectType());
    }

    ThermochromicGlazing_Impl::ThermochromicGlazing_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : Glazing_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == ThermochromicGlazing::iddObjectType());
    }

    ThermochromicGlazing_Impl::ThermochromicGlazing_Impl(const ThermochromicGlazing_Impl& other, Model_Impl* model, bool keepHandle)
      : Glazing_Impl(other, model, keepHandle) {}

    IddObjectType ThermochromicGlazing_Impl::iddObjectType() const {
      return ThermochromicGlazing::iddObjectType();
    }

    const std::vector<std::string>& ThermochromicGlazing_Impl::outputVariableNames() const {
      // TODO: Technically, this is not on this object, but on the Glazed Surface that uses the Construction that references this ThermochromicGlazing
      // Add it to SubSurface?
      static const std::vector<std::string> result{"Surface Window Thermochromic Layer Temperature",
                                                   "Surface Window Thermochromic Layer Property Specification Temperature"};
      return result;
    }

    unsigned int ThermochromicGlazing_Impl::numberofThermochromicGroups() const {
      return numExtensibleGroups();
    }

    std::vector<ThermochromicGroup> ThermochromicGlazing_Impl::thermochromicGroups() const {
      std::vector<ThermochromicGroup> result;

      for (unsigned i = 0; i < numberofThermochromicGroups(); ++i) {

        boost::optional<ThermochromicGroup> group_ = getThermochromicGroup(i);

        // getThermochromicGroup is responsible for handling error and issuing Error log messages.
        // Here we add it to the result array if it worked, and if it didn't, we keep going
        // We just issue a message about index so user can delete it easily
        if (group_) {
          result.push_back(std::move(*group_));
        } else {
          LOG(Error, briefDescription() << " has an invalid ThermochromicGroup group at index " << i);
        }
      }

      return result;
    }

    boost::optional<unsigned> ThermochromicGlazing_Impl::thermochromicGroupIndex(const ThermochromicGroup& thermochromicGroup) const {
      const std::vector<ThermochromicGroup> groups = thermochromicGroups();
      auto it = std::find(groups.cbegin(), groups.cend(), thermochromicGroup);
      if (it != groups.end()) {
        return static_cast<unsigned>(std::distance(groups.cbegin(), it));
      }
      return boost::none;
    }

    boost::optional<ThermochromicGroup> ThermochromicGlazing_Impl::getThermochromicGroup(unsigned groupIndex) const {
      if (groupIndex >= numberofThermochromicGroups()) {
        LOG(Error, "Asked to get ThermochromicGroup with index " << groupIndex << ", but " << briefDescription() << " has just "
                                                                 << numberofThermochromicGroups() << " ThermochromicGroups.");
        return boost::none;
      }
      auto group = getExtensibleGroup(groupIndex).cast<ModelExtensibleGroup>();

      boost::optional<StandardGlazing> standardGlazing_ =
        group.getModelObjectTarget<StandardGlazing>(OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::WindowMaterialGlazingName);

      boost::optional<double> opticalDataTemperature_ =
        group.getDouble(OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::OpticalDataTemperature);

      if (!standardGlazing_) {
        LOG(Error, "Could not retrieve StandardGlazing (WindowMaterialGlazingName) for extensible group " << group.groupIndex() << ".");
        return boost::none;
      }
      if (!opticalDataTemperature_) {
        LOG(Error, "Could not retrieve OpticalDataTemperature for extensible group " << group.groupIndex() << ".");
        return boost::none;
      }

      return {ThermochromicGroup(*standardGlazing_, *opticalDataTemperature_)};
    }

    bool ThermochromicGlazing_Impl::addThermochromicGroup(const ThermochromicGroup& thermochromicGroup) {

      // Check if ThermochromicGroup already exists
      boost::optional<unsigned> existingIndex_ = thermochromicGroupIndex(thermochromicGroup);
      if (existingIndex_) {
        boost::optional<ThermochromicGroup> group_ = getThermochromicGroup(*existingIndex_);
        OS_ASSERT(group_);
        LOG(Warn, "For " << briefDescription() << ", ThermochromicGroup already exists, will be modified in place from " << group_.get() << " to "
                         << thermochromicGroup << ".");
      }

      // If existing, get it, otherwise Push an extensible group. ModelExtensibleGroup cannot be default-constructed, so use a ternary operator
      // Given that we will potentially push many extensible groups
      // we will suffer from going through the internal checks in WorkspaceObject, especially in setPointer,
      // and performance will be roughly O(n^2) when adding groups.
      // So to improve the performance we pushExtensible group without validity check, and call setPointer without validity check (`isValid`)
      std::vector<std::string> temp;
      ModelExtensibleGroup eg = (existingIndex_ ? getExtensibleGroup(existingIndex_.get()).cast<ModelExtensibleGroup>()
                                                : pushExtensibleGroup(temp, false).cast<ModelExtensibleGroup>());

      bool result = eg.setPointer(OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::WindowMaterialGlazingName,
                                  thermochromicGroup.standardGlazing().handle());
      result |= eg.setDouble(OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::OpticalDataTemperature,
                             thermochromicGroup.opticalDataTemperature());
      if (!result) {
        // Something went wrong
        // So erase the new extensible group
        getObject<ModelObject>().eraseExtensibleGroup(eg.groupIndex());
        result = false;
      }
      return result;
    }

    bool ThermochromicGlazing_Impl::addThermochromicGroup(const StandardGlazing& standardGlazing, double opticalDataTemperature) {
      return addThermochromicGroup(ThermochromicGroup{standardGlazing, opticalDataTemperature});
    }

    bool ThermochromicGlazing_Impl::addThermochromicGroups(const std::vector<ThermochromicGroup>& thermochromicGroups) {
      bool result = true;

      for (const auto& thermochromicGroup : thermochromicGroups) {
        bool thisResult = addThermochromicGroup(thermochromicGroup);
        if (!thisResult) {
          LOG(Error, "Could not add ThermochromicGroup " << thermochromicGroup << " to " << briefDescription() << ". Continuing with others.");
          // OS_ASSERT(false);
          result = false;
        }
      }

      return result;
    }

    bool ThermochromicGlazing_Impl::removeThermochromicGroup(unsigned groupIndex) {
      bool result = false;

      unsigned int num = numberofThermochromicGroups();
      if (groupIndex < num) {
        getObject<ModelObject>().eraseExtensibleGroup(groupIndex);
        result = true;
      }
      return result;
    }

    void ThermochromicGlazing_Impl::removeAllThermochromicGroups() {
      getObject<ModelObject>().clearExtensibleGroups();
    }

    boost::optional<double> ThermochromicGlazing_Impl::getVisibleTransmittance() const {
      LOG_AND_THROW("Visible transmittance not yet supported for ThermochromicGlazings.");
    }

    boost::optional<double> ThermochromicGlazing_Impl::interiorVisibleAbsorptance() const {
      LOG_AND_THROW("Interior Visible Absorptance not yet supported for ThermochromicGlazings.");
    }

    boost::optional<double> ThermochromicGlazing_Impl::exteriorVisibleAbsorptance() const {
      LOG_AND_THROW("Exterior Visible Absorptance not yet supported for ThermochromicGlazings.");
    }

    double ThermochromicGlazing_Impl::thickness() const {
      double result = 0.0;  // running average
      unsigned n = 0;
      bool warned = false;
      for (const auto& group : thermochromicGroups()) {
        double glazingThickness = group.standardGlazing().thickness();
        if (n == 0) {
          result = glazingThickness;
        } else {
          // keep running average
          if (!warned && !equal(glazingThickness, result)) {
            LOG(Warn, "Thermochromic group '" << nameString() << "' contains glazings of different thicknesses.");
            warned = true;
          }
          result = (result * static_cast<double>(n) + glazingThickness) / static_cast<double>(n + 1);
        }
        ++n;
      }
      return result;
    }

    bool ThermochromicGlazing_Impl::setThickness(double value) {
      auto groups = thermochromicGroups();
      std::vector<double> rollbackValues;
      for (unsigned i = 0, n = groups.size(); i < n; ++i) {
        auto standardGlazing = groups[i].standardGlazing();
        rollbackValues.push_back(standardGlazing.thickness());
        bool ok = standardGlazing.setThickness(value);
        if (!ok) {
          // rollback previous values
          for (int j = i - 1; j >= 0; --j) {
            standardGlazing.setThickness(rollbackValues[j]);
          }
          return false;
        }
      }
      return true;
    }

  }  // namespace detail

  ThermochromicGlazing::ThermochromicGlazing(const Model& model) : Glazing(ThermochromicGlazing::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ThermochromicGlazing_Impl>());
  }

  IddObjectType ThermochromicGlazing::iddObjectType() {
    return {IddObjectType::OS_WindowMaterial_GlazingGroup_Thermochromic};
  }

  std::vector<ThermochromicGroup> ThermochromicGlazing::thermochromicGroups() const {
    return getImpl<detail::ThermochromicGlazing_Impl>()->thermochromicGroups();
  }

  unsigned int ThermochromicGlazing::numberofThermochromicGroups() const {
    return getImpl<detail::ThermochromicGlazing_Impl>()->numberofThermochromicGroups();
  }

  boost::optional<unsigned> ThermochromicGlazing::thermochromicGroupIndex(const ThermochromicGroup& thermochromicGroup) const {
    return getImpl<detail::ThermochromicGlazing_Impl>()->thermochromicGroupIndex(thermochromicGroup);
  }

  boost::optional<ThermochromicGroup> ThermochromicGlazing::getThermochromicGroup(unsigned groupIndex) const {
    return getImpl<detail::ThermochromicGlazing_Impl>()->getThermochromicGroup(groupIndex);
  }

  bool ThermochromicGlazing::addThermochromicGroup(const ThermochromicGroup& thermochromicGroup) {
    return getImpl<detail::ThermochromicGlazing_Impl>()->addThermochromicGroup(thermochromicGroup);
  }

  bool ThermochromicGlazing::addThermochromicGroup(const StandardGlazing& standardGlazing, double opticalDataTemperature) {
    return getImpl<detail::ThermochromicGlazing_Impl>()->addThermochromicGroup(standardGlazing, opticalDataTemperature);
  }

  bool ThermochromicGlazing::addThermochromicGroups(const std::vector<ThermochromicGroup>& thermochromicGroups) {
    return getImpl<detail::ThermochromicGlazing_Impl>()->addThermochromicGroups(thermochromicGroups);
  }

  bool ThermochromicGlazing::removeThermochromicGroup(unsigned groupIndex) {
    return getImpl<detail::ThermochromicGlazing_Impl>()->removeThermochromicGroup(groupIndex);
  }

  void ThermochromicGlazing::removeAllThermochromicGroups() {
    getImpl<detail::ThermochromicGlazing_Impl>()->removeAllThermochromicGroups();
  }

  /// @cond
  ThermochromicGlazing::ThermochromicGlazing(std::shared_ptr<detail::ThermochromicGlazing_Impl> impl) : Glazing(std::move(impl)) {}
  /// @endcond

}  // namespace model
}  // namespace openstudio
