file(DOWNLOAD ${url} TLS_VERIFY 1 STATUS status LOG log)
message(STATUS "${status}")
list(GET status 0 code)
if(NOT code EQUAL 0)
  message("${log}")
endif()
