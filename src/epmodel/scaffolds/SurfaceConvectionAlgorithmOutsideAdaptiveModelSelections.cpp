/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections.hpp"
#include "SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelections_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections(const Model& model)
    : ModelObject(SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::iddObjectType(), model) {}

  SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections(
    std::shared_ptr<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::iddObjectType() {
    return IddObjectType::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelections;
  }

  // ===== Public API delegating to Impl =====

  // Wind Convection
  std::vector<std::string> SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::windConvectionWindwardVerticalWallEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionWindwardVerticalWallEquationSource);
  }

  std::string SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::windConvectionWindwardVerticalWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->windConvectionWindwardVerticalWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::setWindConvectionWindwardVerticalWallEquationSource(
    const std::string& windConvectionWindwardVerticalWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->setWindConvectionWindwardVerticalWallEquationSource(
      windConvectionWindwardVerticalWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::isWindConvectionWindwardVerticalWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()
      ->isWindConvectionWindwardVerticalWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::resetWindConvectionWindwardVerticalWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->resetWindConvectionWindwardVerticalWallEquationSource();
  }

  std::vector<std::string> SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::windConvectionLeewardVerticalWallEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionLeewardVerticalWallEquationSource);
  }

  std::string SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::windConvectionLeewardVerticalWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->windConvectionLeewardVerticalWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::setWindConvectionLeewardVerticalWallEquationSource(
    const std::string& windConvectionLeewardVerticalWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->setWindConvectionLeewardVerticalWallEquationSource(
      windConvectionLeewardVerticalWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::isWindConvectionLeewardVerticalWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()
      ->isWindConvectionLeewardVerticalWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::resetWindConvectionLeewardVerticalWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->resetWindConvectionLeewardVerticalWallEquationSource();
  }

  std::vector<std::string> SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::windConvectionHorizontalRoofEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::WindConvectionHorizontalRoofEquationSource);
  }

  std::string SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::windConvectionHorizontalRoofEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->windConvectionHorizontalRoofEquationSource();
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::setWindConvectionHorizontalRoofEquationSource(
    const std::string& windConvectionHorizontalRoofEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->setWindConvectionHorizontalRoofEquationSource(
      windConvectionHorizontalRoofEquationSource);
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::isWindConvectionHorizontalRoofEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->isWindConvectionHorizontalRoofEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::resetWindConvectionHorizontalRoofEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->resetWindConvectionHorizontalRoofEquationSource();
  }

  // Natural Convection
  std::vector<std::string> SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::naturalConvectionVerticalWallEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionVerticalWallEquationSource);
  }

  std::string SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::naturalConvectionVerticalWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->naturalConvectionVerticalWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::setNaturalConvectionVerticalWallEquationSource(
    const std::string& naturalConvectionVerticalWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->setNaturalConvectionVerticalWallEquationSource(
      naturalConvectionVerticalWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::isNaturalConvectionVerticalWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->isNaturalConvectionVerticalWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::resetNaturalConvectionVerticalWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->resetNaturalConvectionVerticalWallEquationSource();
  }

  std::vector<std::string> SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::naturalConvectionStableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionStableHorizontalEquationSource);
  }

  std::string SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::naturalConvectionStableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->naturalConvectionStableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::setNaturalConvectionStableHorizontalEquationSource(
    const std::string& naturalConvectionStableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->setNaturalConvectionStableHorizontalEquationSource(
      naturalConvectionStableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::isNaturalConvectionStableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()
      ->isNaturalConvectionStableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::resetNaturalConvectionStableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->resetNaturalConvectionStableHorizontalEquationSource();
  }

  std::vector<std::string> SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::naturalConvectionUnstableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields::NaturalConvectionUnstableHorizontalEquationSource);
  }

  std::string SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::naturalConvectionUnstableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->naturalConvectionUnstableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::setNaturalConvectionUnstableHorizontalEquationSource(
    const std::string& naturalConvectionUnstableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->setNaturalConvectionUnstableHorizontalEquationSource(
      naturalConvectionUnstableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::isNaturalConvectionUnstableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()
      ->isNaturalConvectionUnstableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::resetNaturalConvectionUnstableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>()->resetNaturalConvectionUnstableHorizontalEquationSource();
  }

}  // namespace epmodel
}  // namespace openstudio

// ===== Impl definitions =====

namespace openstudio {
namespace epmodel {
  namespace detail {

    using F = openstudio::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelectionsFields;

// Macro to reduce boilerplate for choice fields with default
#define CHOICE_GETTER(FieldName, FieldEnum)                                                      \
  std::string SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl::FieldName() const { \
    const auto value = getString(F::FieldEnum, true);                                            \
    OS_ASSERT(value);                                                                            \
    return *value;                                                                               \
  }

#define CHOICE_SETTER(FieldName, FieldEnum)                                                                    \
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl::set##FieldName(const std::string& val) { \
    return setString(F::FieldEnum, val);                                                                       \
  }

#define CHOICE_ISDEFAULTED(FieldName, FieldEnum)                                                         \
  bool SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl::is##FieldName##Defaulted() const { \
    return isEmpty(F::FieldEnum);                                                                        \
  }

#define CHOICE_RESET(FieldName, FieldEnum)                                                 \
  void SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl::reset##FieldName() { \
    OS_ASSERT(setString(F::FieldEnum, ""));                                                \
  }

#define CHOICE_VALUES(fieldName, FieldEnum)                                                                           \
  std::vector<std::string> SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl::fieldName##Values() const { \
    return openstudio::epmodel::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::fieldName##Values();        \
  }

#define CHOICE_FIELD(FieldName, fieldName, FieldEnum) \
  CHOICE_GETTER(fieldName, FieldEnum)                 \
  CHOICE_SETTER(FieldName, FieldEnum)                 \
  CHOICE_ISDEFAULTED(FieldName, FieldEnum)            \
  CHOICE_RESET(FieldName, FieldEnum)                  \
  CHOICE_VALUES(fieldName, FieldEnum)

    // Wind Convection
    CHOICE_FIELD(WindConvectionWindwardVerticalWallEquationSource, windConvectionWindwardVerticalWallEquationSource,
                 WindConvectionWindwardVerticalWallEquationSource)
    CHOICE_FIELD(WindConvectionLeewardVerticalWallEquationSource, windConvectionLeewardVerticalWallEquationSource,
                 WindConvectionLeewardVerticalWallEquationSource)
    CHOICE_FIELD(WindConvectionHorizontalRoofEquationSource, windConvectionHorizontalRoofEquationSource, WindConvectionHorizontalRoofEquationSource)

    // Natural Convection
    CHOICE_FIELD(NaturalConvectionVerticalWallEquationSource, naturalConvectionVerticalWallEquationSource,
                 NaturalConvectionVerticalWallEquationSource)
    CHOICE_FIELD(NaturalConvectionStableHorizontalEquationSource, naturalConvectionStableHorizontalEquationSource,
                 NaturalConvectionStableHorizontalEquationSource)
    CHOICE_FIELD(NaturalConvectionUnstableHorizontalEquationSource, naturalConvectionUnstableHorizontalEquationSource,
                 NaturalConvectionUnstableHorizontalEquationSource)

#undef CHOICE_GETTER
#undef CHOICE_SETTER
#undef CHOICE_ISDEFAULTED
#undef CHOICE_RESET
#undef CHOICE_VALUES
#undef CHOICE_FIELD

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
