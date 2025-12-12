########################################################################################################################
#  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
#  See also https://openstudio.net/license
########################################################################################################################

OpenStudio::logFree(OpenStudio::Warn, 'ShowRunnerOutput.rb', 'Deprecated at 3.11.0, use WorkflowStepResult::showOutput() instead')

# Provided for backward compatibility
def show_output(result)
  # Now in C++
  result.showOutput
end
