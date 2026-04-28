/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/WindowsCalculationEngine.hpp"
#include "scaffolds/WindowsCalculationEngine_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/WindowsCalculationEngine_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {
  WindowsCalculationEngine::WindowsCalculationEngine(const Model& model) : ModelObject(WindowsCalculationEngine::iddObjectType(), model) {}

  WindowsCalculationEngine::WindowsCalculationEngine(std::shared_ptr<detail::WindowsCalculationEngine_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WindowsCalculationEngine::iddObjectType() {
    return IddObjectType::WindowsCalculationEngine;
  }

  std::vector<std::string> WindowsCalculationEngine::windowsEngineValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowsCalculationEngineFields::Windowsengine);
  }

  std::string WindowsCalculationEngine::windowsEngine() const {
    return getImpl<detail::WindowsCalculationEngine_Impl>()->windowsEngine();
  }

  bool WindowsCalculationEngine::isWindowsEngineDefaulted() const {
    return getImpl<detail::WindowsCalculationEngine_Impl>()->isWindowsEngineDefaulted();
  }

  bool WindowsCalculationEngine::setWindowsEngine(const std::string& windowsEngine) {
    return getImpl<detail::WindowsCalculationEngine_Impl>()->setWindowsEngine(windowsEngine);
  }

  void WindowsCalculationEngine::resetWindowsEngine() {
    getImpl<detail::WindowsCalculationEngine_Impl>()->resetWindowsEngine();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string WindowsCalculationEngine_Impl::windowsEngine() const {
      const auto value = getString(openstudio::WindowsCalculationEngineFields::Windowsengine, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowsCalculationEngine_Impl::isWindowsEngineDefaulted() const {
      return isEmpty(openstudio::WindowsCalculationEngineFields::Windowsengine);
    }

    bool WindowsCalculationEngine_Impl::setWindowsEngine(const std::string& windowsEngine) {
      return setString(openstudio::WindowsCalculationEngineFields::Windowsengine, windowsEngine);
    }

    void WindowsCalculationEngine_Impl::resetWindowsEngine() {
      OS_ASSERT(setString(openstudio::WindowsCalculationEngineFields::Windowsengine, ""));
    }

    std::vector<std::string> WindowsCalculationEngine_Impl::windowsEngineValues() const {
      return WindowsCalculationEngine::windowsEngineValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
