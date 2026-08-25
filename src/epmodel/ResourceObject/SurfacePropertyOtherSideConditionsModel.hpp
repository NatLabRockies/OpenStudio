/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYOTHERSIDECONDITIONSMODEL_HPP
#define EPMODEL_SURFACEPROPERTYOTHERSIDECONDITIONSMODEL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyOtherSideConditionsModel_Impl;
  }

  /** \brief Selects the model used to calculate a surface's other-side conditions.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfacepropertyothersideconditionsmodel,SurfaceProperty:OtherSideConditionsModel}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SurfacePropertyOtherSideConditionsModel</code>.
   * The <code>typeOfModeling()</code> field and its default/reset behavior have
   * the same public meaning in both APIs.
   *
   * \par Known limitations
   * This wrapper exposes only the EnergyPlus modeling-type field; it does not
   * add relationships beyond that object.
   */
  class EPMODEL_API SurfacePropertyOtherSideConditionsModel : public ModelObject
  {
   public:
    explicit SurfacePropertyOtherSideConditionsModel(const Model& model);

    virtual ~SurfacePropertyOtherSideConditionsModel() override = default;
    SurfacePropertyOtherSideConditionsModel(const SurfacePropertyOtherSideConditionsModel& other) = default;
    SurfacePropertyOtherSideConditionsModel(SurfacePropertyOtherSideConditionsModel&& other) = default;
    SurfacePropertyOtherSideConditionsModel& operator=(const SurfacePropertyOtherSideConditionsModel&) = default;
    SurfacePropertyOtherSideConditionsModel& operator=(SurfacePropertyOtherSideConditionsModel&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> typeOfModelingValues();

    std::string typeOfModeling() const;
    bool isTypeOfModelingDefaulted() const;

    bool setTypeOfModeling(const std::string& typeOfModeling);
    void resetTypeOfModeling();

   protected:
    using ImplType = detail::SurfacePropertyOtherSideConditionsModel_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyOtherSideConditionsModel(std::shared_ptr<detail::SurfacePropertyOtherSideConditionsModel_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
