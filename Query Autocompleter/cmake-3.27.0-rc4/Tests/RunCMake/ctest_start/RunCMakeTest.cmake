include(RunCTest)

set(CASE_CTEST_START_ARGS "")

function(run_ctest_start CASE_NAME)
  set(CASE_CTEST_START_ARGS "${ARGN}")
  run_ctest(${CASE_NAME})
endfunction()

function(check_tag_contents EXPECTED)
  set(_tag_file "${RunCMake_BINARY_DIR}/${CASE_NAME}-build/Testing/TAG")
  if(EXISTS "${_tag_file}")
    file(READ "${_tag_file}" _tag_contents)
    if(NOT _tag_contents MATCHES "${EXPECTED}")
      set(RunCMake_TEST_FAILED "Testing/TAG file does not match expected value.\nActual TAG file:\n${_tag_contents}\nExpected TAG file:\n${EXPECTED}\n" PARENT_SCOPE)
    endif()
  else()
    set(RunCMake_TEST_FAILED "Testing/TAG file does not exist." PARENT_SCOPE)
  endif()
endfunction()

run_ctest_start(StartQuiet Experimental QUIET)
run_ctest_start(ConfigInSource Experimental)
run_ctest_start(FunctionScope Experimental QUIET)
run_ctest_start(WriteModelToTagExperimental Experimental QUIET)
run_ctest_start(WriteModelToTagContinuous Continuous QUIET)
run_ctest_start(WriteModelToTagNightly Nightly QUIET)
run_ctest_start(WriteModelToTagNoMatchingTrack Continuous TRACK SomeWeirdTrackName QUIET)
run_ctest_start(WriteModelToTagNoMatchingGroup Continuous GROUP SomeWeirdTrackName QUIET)
run_ctest_start(AppendSameModel Continuous APPEND)
run_ctest_start(AppendDifferentModel Experimental APPEND)
run_ctest_start(AppendNoModel APPEND)
run_ctest_start(AppendDifferentTrack TRACK ExperimentalDifferent APPEND)
run_ctest_start(AppendDifferentGroup GROUP ExperimentalDifferent APPEND)
run_ctest_start(NoAppendDifferentTrack Experimental TRACK ExperimentalDifferent)
run_ctest_start(NoAppendDifferentGroup Experimental GROUP ExperimentalDifferent)
run_ctest_start(AppendNoMatchingTrack Continuous APPEND)
run_ctest_start(AppendOldContinuous Continuous APPEND)
run_ctest_start(AppendOldNoModel APPEND)
run_ctest_start(NoModel QUIET)
run_ctest_start(MissingTrackArg Experimental TRACK)
run_ctest_start(MissingGroupArg Experimental GROUP)
run_ctest_start(MissingTrackArgAppend Experimental TRACK APPEND)
run_ctest_start(MissingGroupArgAppend Experimental GROUP APPEND)
run_ctest_start(MissingTrackArgQuiet Experimental TRACK QUIET)
run_ctest_start(MissingGroupArgQuiet Experimental GROUP QUIET)
run_ctest_start(TooManyArgs Experimental
                ${RunCMake_BINARY_DIR}/TooManyArgs-build
                ${RunCMake_BINARY_DIR}/TooManyArgs-build
                ${RunCMake_BINARY_DIR}/TooManyArgs-build)
run_ctest_start(NoStartTimeExperimental Experimental)
run_ctest_start(NoStartTimeNightly Nightly)

function(run_ConfigInBuild)
  set(RunCMake_TEST_BINARY_DIR ${RunCMake_BINARY_DIR}/ConfigInBuild-build)
  set(RunCMake_TEST_NO_CLEAN 1)
  file(REMOVE_RECURSE "${RunCMake_TEST_BINARY_DIR}")
  file(MAKE_DIRECTORY "${RunCMake_TEST_BINARY_DIR}")
  run_ctest_start(ConfigInBuild Experimental)
endfunction()
run_ConfigInBuild()