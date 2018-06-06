macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

PROJECT(Miner)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

use_cxx11()

ADD_SUBDIRECTORY(Miner)
ADD_SUBDIRECTORY(LRUCache)
ADD_SUBDIRECTORY(Utils)
ADD_SUBDIRECTORY(Simulator)

ADD_EXECUTABLE(CMinerSimulatorTest CMinerSimulatorTest.cpp Simulator/CMinerSimulator.cpp Simulator/Simulator.cpp)
TARGET_LINK_LIBRARIES(CMinerSimulatorTest lru_cache miner_hdfs utils)

ADD_EXECUTABLE(CMinerHDFSTest CMinerHDFSTest.cpp)
TARGET_LINK_LIBRARIES(CMinerHDFSTest lru_cache miner_hdfs)

ADD_EXECUTABLE(CMinerAuthorTest CMinerAuthorTest.cpp)
TARGET_LINK_LIBRARIES(CMinerAuthorTest miner_author utils)

ADD_EXECUTABLE(CMinerMyTest CMinerMyTest.cpp)
TARGET_LINK_LIBRARIES(CMinerMyTest miner_my utils)


ADD_EXECUTABLE(NonPredictSimulatorTest NonPredictSimulatorTest.cpp Simulator/NonPredictSimulator.cpp Simulator/Simulator.cpp)
TARGET_LINK_LIBRARIES(NonPredictSimulatorTest miner_base)

