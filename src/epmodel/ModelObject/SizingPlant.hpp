/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPLANT_HPP
#define EPMODEL_SIZINGPLANT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class PlantLoop;

  namespace detail {
    class SizingPlant_Impl;
  }

  class EPMODEL_API SizingPlant : public ModelObject
  {
   public:
    explicit SizingPlant(const Model& model, const PlantLoop& plantLoop);

    virtual ~SizingPlant() override = default;
    SizingPlant(const SizingPlant& other) = default;
    SizingPlant(SizingPlant&& other) = default;
    SizingPlant& operator=(const SizingPlant&) = default;
    SizingPlant& operator=(SizingPlant&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> loopTypeValues();
    static std::vector<std::string> sizingOptionValues();
    static std::vector<std::string> coincidentSizingFactorModeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model SizingPlant scalar accessor names/signatures.
    // - Field Mapping: loopType, designLoopExitTemperature, loopDesignTemperatureDifference,
    //   sizingOption, zoneTimestepsinAveragingWindow, and coincidentSizingFactorMode map
    //   directly to E+ Sizing:Plant fields.
    // - Field Mapping: PlantorCondenserLoopName is a relationship field and is intentionally
    //   excluded from scalar accessor coverage.
    // - ForwardTranslator Evidence: ForwardTranslateSizingPlant and ForwardTranslatePlantLoop
    //   confirm direct scalar mappings and the owning PlantLoop relationship.
    // - TODO(parity): Add relationship accessors for PlantorCondenserLoopName in a dedicated
    //   non-scalar parity pass.
    std::string loopType() const;
    bool setLoopType(const std::string& loopType);

    double designLoopExitTemperature() const;
    bool setDesignLoopExitTemperature(double designLoopExitTemperature);

    double loopDesignTemperatureDifference() const;
    bool setLoopDesignTemperatureDifference(double loopDesignTemperatureDifference);

    std::string sizingOption() const;
    bool setSizingOption(const std::string& sizingOption);

    int zoneTimestepsinAveragingWindow() const;
    bool setZoneTimestepsinAveragingWindow(int zoneTimestepsinAveragingWindow);

    std::string coincidentSizingFactorMode() const;
    bool setCoincidentSizingFactorMode(const std::string& coincidentSizingFactorMode);

   protected:
    using ImplType = detail::SizingPlant_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SizingPlant(std::shared_ptr<detail::SizingPlant_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
