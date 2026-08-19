/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

/** \file
 *  \brief Main page for the OpenStudio EnergyPlus-aligned model (epmodel) namespace.
 */

/** \mainpage OpenStudio EPModel C++ API
 *
 * \section epmodel_overview EPModel and OpenStudio 4.0
 *
 * OpenStudio 4.0 begins a major transition from the legacy
 * <code>openstudio::model::Model</code> representation to
 * \ref openstudio::epmodel::Model "openstudio::epmodel::Model". EPModel is the
 * EnergyPlus-backed implementation of the OpenStudio Model API. It allows
 * applications and measures to work directly with the model that EnergyPlus
 * simulates.
 *
 * The separate <code>openstudio::epmodel</code> namespace lets the two
 * implementations coexist while compatibility work is underway. It is a
 * development boundary, not the intended final API. The objective is for the
 * EnergyPlus-backed implementation to become the OpenStudio Model
 * implementation without requiring users to select a separate model API.
 *
 * \section epmodel_changes What EPModel changes
 *
 * - **EnergyPlus is the native model representation.** EPModel loads and saves
 *   IDF rather than OSM.
 * - **The OpenStudio Model API is the target.** EPModel implements that API
 *   directly over EnergyPlus objects instead of defining a parallel API.
 * - **Measures operate directly on EPModel.** Python and Ruby measures can
 *   create and edit EnergyPlus models without a separate OSM model as the
 *   persistent source of truth.
 * - **Existing OSMs have an ingress path.** OpenStudio version-translates an
 *   OSM, forward-translates it to IDF, and loads the result as an EPModel before
 *   measures run.
 *
 * \section epmodel_trying Trying EPModel
 *
 * The installed SDK includes workflows under
 * <code>&lt;openstudio-install&gt;/Examples/epmodel</code>. They demonstrate three
 * starting points: creating a new building, modifying an existing EnergyPlus
 * reference building, and converting an existing OSM before continuing with
 * an IDF-backed workflow.
 *
 * \section epmodel_status Current status and this reference
 *
 * EPModel is under active development and does not yet provide complete API
 * compatibility with <code>openstudio::model::Model</code>. Existing measures
 * and applications should be tested with EPModel.
 *
 * The classes in this reference are the reviewed, user-facing API. Generated
 * scaffold wrappers provide typed access to nearly all other EnergyPlus IDD
 * object types while their public APIs are developed. Objects without a
 * specialized wrapper remain available through
 * <code>openstudio::WorkspaceObject</code>.
 *
 * Each class page identifies the EnergyPlus object or objects involved and
 * records important behavior, known limitations, and user-visible differences
 * from the OpenStudio Model API. Start with \ref openstudio::epmodel::Model
 * "Model" and \ref openstudio::epmodel::ModelObject "ModelObject", or use
 * **Classes** above to browse the API using its source-tree organization.
 */
