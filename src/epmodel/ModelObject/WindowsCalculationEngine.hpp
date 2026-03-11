/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWSCALCULATIONENGINE_HPP
#define EPMODEL_WINDOWSCALCULATIONENGINE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowsCalculationEngine_Impl;
  }

  class EPMODEL_API WindowsCalculationEngine : public ModelObject
  {
   public:
    explicit WindowsCalculationEngine(const Model& model);

    virtual ~WindowsCalculationEngine() override = default;
    WindowsCalculationEngine(const WindowsCalculationEngine& other) = default;
    WindowsCalculationEngine(WindowsCalculationEngine&& other) = default;
    WindowsCalculationEngine& operator=(const WindowsCalculationEngine&) = default;
    WindowsCalculationEngine& operator=(WindowsCalculationEngine&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> windowsEngineValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so class and accessor names follow the EnergyPlus IDD naming (WindowsCalculationEngine).
    // - Field Mapping: windowsEngine maps directly to WindowsCalculationEngine/Windows engine (choice field with BuiltInWindowsModel default).
    std::string windowsEngine() const;
    bool isWindowsEngineDefaulted() const;

    bool setWindowsEngine(const std::string& windowsEngine);
    void resetWindowsEngine();

   protected:
    using ImplType = detail::WindowsCalculationEngine_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowsCalculationEngine(std::shared_ptr<detail::WindowsCalculationEngine_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
