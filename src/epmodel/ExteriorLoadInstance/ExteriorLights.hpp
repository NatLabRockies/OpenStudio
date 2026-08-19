/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERIORLIGHTS_HPP
#define EPMODEL_EXTERIORLIGHTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExteriorLights_Impl;
  }

  /** \brief Represents the EnergyPlus Exterior:Lights object.
   *
   * \par EnergyPlus object
   * \epobject{group-exterior-energy-use-equipment.html#exteriorlights,Exterior:Lights}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExteriorLights</code>. <b>Not yet available:</b> the Model definition, schedule, and facility relationship methods. EPModel exposes control option, end-use subcategory, and multiplier.
   *
   * \par Known limitations
   * EPModel stores the compatibility multiplier in the EnergyPlus Design Level field; EnergyPlus has no separate multiplier field.
   */
  class EPMODEL_API ExteriorLights : public ModelObject
  {
   public:
    explicit ExteriorLights(const Model& model);

    virtual ~ExteriorLights() override = default;
    ExteriorLights(const ExteriorLights& other) = default;
    ExteriorLights(ExteriorLights&& other) = default;
    ExteriorLights& operator=(const ExteriorLights&) = default;
    ExteriorLights& operator=(ExteriorLights&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlOptionValues();
    static std::vector<std::string> validControlOptionValues();

    std::string controlOption() const;
    bool isControlOptionDefaulted() const;
    bool setControlOption(const std::string& controlOption);
    void resetControlOption();

    double multiplier() const;
    bool isMultiplierDefaulted() const;
    bool setMultiplier(double multiplier);
    void resetMultiplier();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

   protected:
    using ImplType = detail::ExteriorLights_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExteriorLights(std::shared_ptr<detail::ExteriorLights_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
