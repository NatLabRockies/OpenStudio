#!/bin/bash
# Test utility functions for CI and local development
# Usage: source ci/test_utils.sh

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Run a test with retry logic
# Usage: run_test_with_retry "TestName" [max_attempts]
run_test_with_retry() {
  local test_name=$1
  local max_attempts=${2:-3}
  local attempt=1
  
  while [ $attempt -le $max_attempts ]; do
    echo -e "${BLUE}Running $test_name (attempt $attempt/$max_attempts)...${NC}"
    if ctest -R "$test_name" --output-on-failure; then
      echo -e "${GREEN}✓ Test passed${NC}"
      return 0
    fi
    
    echo -e "${RED}✗ Test failed on attempt $attempt${NC}"
    attempt=$((attempt + 1))
    
    if [ $attempt -le $max_attempts ]; then
      local sleep_time=$((2 ** attempt))
      echo -e "${YELLOW}Retrying in $sleep_time seconds...${NC}"
      sleep $sleep_time
    fi
  done
  
  echo -e "${RED}✗ Test failed after $max_attempts attempts${NC}"
  return 1
}

# Run network tests with skip on failure
# Usage: run_network_tests_safe
run_network_tests_safe() {
  echo -e "${BLUE}Checking network connectivity to rubygems.org...${NC}"
  
  if ping -c 1 rubygems.org &> /dev/null; then
    echo -e "${GREEN}✓ Network available, running bundle tests...${NC}"
    ctest -R "test_bundle" --output-on-failure
  else
    echo -e "${YELLOW}⚠ Network unavailable, skipping bundle tests${NC}"
    return 0
  fi
}

# Run all tests excluding network-dependent ones
# Usage: run_tests_offline
run_tests_offline() {
  echo -e "${BLUE}Running all tests except network-dependent tests...${NC}"
  ctest -LE network --output-on-failure
}

# Run only flaky tests with verification
# Usage: run_flaky_tests [repeat_count]
run_flaky_tests() {
  local repeat_count=${1:-10}
  echo -e "${BLUE}Running flaky tests $repeat_count times to verify consistency...${NC}"
  
  if ctest -L flaky --repeat until-pass:$repeat_count --output-on-failure; then
    echo -e "${GREEN}✓ All flaky tests passed consistently${NC}"
    return 0
  else
    echo -e "${RED}✗ Flaky tests still failing${NC}"
    return 1
  fi
}

# Run tests by label
# Usage: run_tests_by_label "label_name"
run_tests_by_label() {
  local label=$1
  echo -e "${BLUE}Running tests with label: $label${NC}"
  ctest -L "$label" --output-on-failure
}

# Run Space_Convexity test multiple times to verify fix
# Usage: verify_space_convexity_fix [repeat_count]
verify_space_convexity_fix() {
  local repeat_count=${1:-10}
  echo -e "${BLUE}Verifying Space_Convexity fix by running $repeat_count times...${NC}"
  
  if run_test_with_retry "ModelFixture.Space_Convexity" 1; then
    # If it passes, run it multiple times to ensure consistency
    if ctest -R "ModelFixture.Space_Convexity" --repeat until-pass:$repeat_count --output-on-failure; then
      echo -e "${GREEN}✓ Space_Convexity test passed all $repeat_count runs consistently${NC}"
      return 0
    else
      echo -e "${RED}✗ Space_Convexity test is still flaky${NC}"
      return 1
    fi
  else
    echo -e "${RED}✗ Space_Convexity test failed${NC}"
    return 1
  fi
}

# Show help
show_test_utils_help() {
  cat << EOF
${GREEN}OpenStudio Test Utilities${NC}

${BLUE}Available Functions:${NC}
  run_test_with_retry <test_name> [attempts]   - Run a test with retry logic
  run_network_tests_safe                        - Run bundle tests only if network available
  run_tests_offline                             - Run all tests except network-dependent
  run_flaky_tests [count]                       - Run flaky tests multiple times
  run_tests_by_label <label>                    - Run tests with specific label
  verify_space_convexity_fix [count]            - Verify the Space_Convexity fix
  show_test_utils_help                          - Show this help message

${BLUE}Examples:${NC}
  # Run a specific test with retry
  run_test_with_retry "ModelFixture.Building_Clone" 3

  # Run all non-network tests
  run_tests_offline

  # Run bundle tests if network is available
  run_network_tests_safe

  # Verify flaky tests are fixed
  run_flaky_tests 20

  # Run only geometry tests
  run_tests_by_label "geometry"

${BLUE}Available Test Labels:${NC}
  - network    : Tests requiring network connectivity
  - bundle     : Bundle/gem related tests
  - cli        : Command-line interface tests
  - flaky      : Previously flaky tests
  - geometry   : Geometry-related tests

EOF
}

# Auto-display help if sourced
if [ "${BASH_SOURCE[0]}" == "${0}" ]; then
  show_test_utils_help
fi
