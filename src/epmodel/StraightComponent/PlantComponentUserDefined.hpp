/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTCOMPONENTUSERDEFINED_HPP
#define EPMODEL_PLANTCOMPONENTUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantComponentUserDefined_Impl;
  }

  class EPMODEL_API PlantComponentUserDefined : public StraightComponent
  {
   public:
    explicit PlantComponentUserDefined(const Model& model);

    virtual ~PlantComponentUserDefined() override = default;
    PlantComponentUserDefined(const PlantComponentUserDefined& other) = default;
    PlantComponentUserDefined(PlantComponentUserDefined&& other) = default;
    PlantComponentUserDefined& operator=(const PlantComponentUserDefined&) = default;
    PlantComponentUserDefined& operator=(PlantComponentUserDefined&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> plantConnection1LoadingModeValues();
    static std::vector<std::string> plantConnection1LoopFlowRequestModeValues();
    static std::vector<std::string> plantConnection2LoadingModeValues();
    static std::vector<std::string> plantConnection2LoopFlowRequestModeValues();
    static std::vector<std::string> plantConnection3LoadingModeValues();
    static std::vector<std::string> plantConnection3LoopFlowRequestModeValues();
    static std::vector<std::string> plantConnection4LoadingModeValues();
    static std::vector<std::string> plantConnection4LoopFlowRequestModeValues();

    // Schema Alignment Notes:
    // - API: numberOfPlantLoopConnections plus each plantConnection#LoadingMode and loopFlowRequestMode scalar mirrors
    //   PlantComponent:UserDefined fields while deferring EMS program, node, and storage relationships to future passes.
    // - Field Mapping: Node/object-list fields such as Air/Plant connection node names, EMS program calling managers, the
    //   water storage tank references, and ambient zone reference are relationship behavior and intentionally excluded here.
    // - TODO(parity): Extend this class with EMS/zone/storage relationship APIs when the non-scalar scaffold phase begins.
    int numberOfPlantLoopConnections() const;
    bool setNumberOfPlantLoopConnections(int numberOfPlantLoopConnections);

    std::string plantConnection1LoadingMode() const;
    bool setPlantConnection1LoadingMode(const std::string& plantConnection1LoadingMode);

    std::string plantConnection1LoopFlowRequestMode() const;
    bool setPlantConnection1LoopFlowRequestMode(const std::string& plantConnection1LoopFlowRequestMode);

    boost::optional<std::string> plantConnection2LoadingMode() const;
    bool setPlantConnection2LoadingMode(const std::string& plantConnection2LoadingMode);
    void resetPlantConnection2LoadingMode();

    boost::optional<std::string> plantConnection2LoopFlowRequestMode() const;
    bool setPlantConnection2LoopFlowRequestMode(const std::string& plantConnection2LoopFlowRequestMode);
    void resetPlantConnection2LoopFlowRequestMode();

    boost::optional<std::string> plantConnection3LoadingMode() const;
    bool setPlantConnection3LoadingMode(const std::string& plantConnection3LoadingMode);
    void resetPlantConnection3LoadingMode();

    boost::optional<std::string> plantConnection3LoopFlowRequestMode() const;
    bool setPlantConnection3LoopFlowRequestMode(const std::string& plantConnection3LoopFlowRequestMode);
    void resetPlantConnection3LoopFlowRequestMode();

    boost::optional<std::string> plantConnection4LoadingMode() const;
    bool setPlantConnection4LoadingMode(const std::string& plantConnection4LoadingMode);
    void resetPlantConnection4LoadingMode();

    boost::optional<std::string> plantConnection4LoopFlowRequestMode() const;
    bool setPlantConnection4LoopFlowRequestMode(const std::string& plantConnection4LoopFlowRequestMode);
    void resetPlantConnection4LoopFlowRequestMode();

   protected:
    using ImplType = detail::PlantComponentUserDefined_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantComponentUserDefined(std::shared_ptr<detail::PlantComponentUserDefined_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
