/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MEASURE_MODELICAMEASURE_HPP
#define MEASURE_MODELICAMEASURE_HPP

#include "MeasureAPI.hpp"
#include "OSMeasure.hpp"

#include "../modelica/ModelicaFile.hpp"
#include "../utilities/core/Logger.hpp"
#include "../utilities/idf/Workspace.hpp"

namespace openstudio {

namespace model {
  class Model;
}

namespace measure {

  /** ModelicaMeasure is an abstract base class for UserScripts that operate on Modelica Models. */
  class MEASURE_API ModelicaMeasure : public OSMeasure
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    //@}
    /** @name Getters */
    //@{

    /** Returns the arguments for this script. In interactive applications, an OSRunner presents
   *  these arguments to the user to produce an OSArgumentMap of user_arguments that it then passes
   *  to this script's run method. The same basic steps should happen in applications with non-
   *  interactive scripts, but in that case an entity other than an OSRunner may be in charge of
   *  collecting user arguments. The base class implementation returns an empty vector. */
    virtual std::vector<OSArgument> arguments(const openstudio::model::Model& model, const openstudio::Workspace& workspace) const;

    //@}
    /** @name Actions */
    //@{

    /** Run the script on the given model with the given runner and user_arguments. The base class
   *  implementation calls runner.prepareForMeasureRun(*this) and should be called at the
   *  beginning of derived class implementations of this method. (In C++, that call looks like
   *  ModelicaMeasure::run(model, workspace, runner, user_arguments). In Ruby that call looks like
   *  super(model, workspace, runner, user_arguments). */
    virtual bool run(openstudio::modelica::ModelicaFile& modelicaFile, openstudio::model::Model& model, const openstudio::Workspace& workspace,
                     OSRunner& runner, const std::map<std::string, OSArgument>& user_arguments) const;

    //@}
    //
   protected:
    ModelicaMeasure();

   private:
    REGISTER_LOGGER("openstudio.measure.ModelicaMeasure");
  };

}  // namespace measure
}  // namespace openstudio

#endif  // MEASURE_MODELICAMEASURE_HPP
