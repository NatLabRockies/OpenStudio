/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTTOWER_HPP
#define EPMODEL_HVACTEMPLATEPLANTTOWER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplatePlantTower_Impl;
  }

  class EPMODEL_API HVACTemplatePlantTower : public ModelObject
  {
   public:
    explicit HVACTemplatePlantTower(const Model& model);

    virtual ~HVACTemplatePlantTower() override = default;
    HVACTemplatePlantTower(const HVACTemplatePlantTower& other) = default;
    HVACTemplatePlantTower(HVACTemplatePlantTower&& other) = default;
    HVACTemplatePlantTower& operator=(const HVACTemplatePlantTower&) = default;
    HVACTemplatePlantTower& operator=(HVACTemplatePlantTower&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> towerTypeValues();
    static std::vector<std::string> templatePlantLoopTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:Tower non-name scalar fields.
    // - Field Mapping: No object-list/reference/node fields are exposed in this scalar scaffold.
    // - TODO(parity): Add object-reference linkage behavior in a later parity pass.
    /** @name Tower type */
    //@{
    std::string towerType() const;
    bool setTowerType(const std::string& towerType);
    //@}

    /** @name High speed nominal capacity */
    //@{
    boost::optional<double> highSpeedNominalCapacity() const;
    bool isHighSpeedNominalCapacityDefaulted() const;
    bool isHighSpeedNominalCapacityAutosized() const;
    bool setHighSpeedNominalCapacity(double highSpeedNominalCapacity);
    void resetHighSpeedNominalCapacity();
    void autosizeHighSpeedNominalCapacity();
    //@}

    /** @name High speed fan power */
    //@{
    boost::optional<double> highSpeedFanPower() const;
    bool isHighSpeedFanPowerDefaulted() const;
    bool isHighSpeedFanPowerAutosized() const;
    bool setHighSpeedFanPower(double highSpeedFanPower);
    void resetHighSpeedFanPower();
    void autosizeHighSpeedFanPower();
    //@}

    /** @name Low speed nominal capacity */
    //@{
    boost::optional<double> lowSpeedNominalCapacity() const;
    bool isLowSpeedNominalCapacityDefaulted() const;
    bool isLowSpeedNominalCapacityAutosized() const;
    bool setLowSpeedNominalCapacity(double lowSpeedNominalCapacity);
    void resetLowSpeedNominalCapacity();
    void autosizeLowSpeedNominalCapacity();
    //@}

    /** @name Low speed fan power */
    //@{
    boost::optional<double> lowSpeedFanPower() const;
    bool isLowSpeedFanPowerDefaulted() const;
    bool isLowSpeedFanPowerAutosized() const;
    bool setLowSpeedFanPower(double lowSpeedFanPower);
    void resetLowSpeedFanPower();
    void autosizeLowSpeedFanPower();
    //@}

    /** @name Free convection capacity */
    //@{
    boost::optional<double> freeConvectionCapacity() const;
    bool isFreeConvectionCapacityDefaulted() const;
    bool isFreeConvectionCapacityAutosized() const;
    bool setFreeConvectionCapacity(double freeConvectionCapacity);
    void resetFreeConvectionCapacity();
    void autosizeFreeConvectionCapacity();
    //@}

    /** @name Priority */
    //@{
    boost::optional<std::string> priority() const;
    bool setPriority(const std::string& priority);
    void resetPriority();
    //@}

    /** @name Sizing factor */
    //@{
    double sizingFactor() const;
    bool isSizingFactorDefaulted() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();
    //@}

    /** @name Template plant loop type */
    //@{
    boost::optional<std::string> templatePlantLoopType() const;
    bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);
    void resetTemplatePlantLoopType();
    //@}

   protected:
    using ImplType = detail::HVACTemplatePlantTower_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplatePlantTower(std::shared_ptr<detail::HVACTemplatePlantTower_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
