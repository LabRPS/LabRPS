if(MSVC)
    add_definitions(-DFCAppSeismicLabTools -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
else(MSVC)
    add_definitions(-DHAVE_LIMITS_H -DHAVE_CONFIG_H)
endif(MSVC)

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_BINARY_DIR}/..
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(SeismicLabTools_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND SeismicLabTools_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND SeismicLabTools_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(coherence/LohAndLinCoherencePy)
generate_from_xml(coherence/HarichandranVanmarckeCoherencePy)
generate_from_xml(coherence/AbrahamsonCoherencePy)
generate_from_xml(spectrum/CloughPenzienSpectrumPy)
generate_from_xml(spectrum/KanaiTajimiSpectrumPy)
generate_from_xml(spectrum/HuZhouSpectrumPy)
generate_from_xml(spectrum/SeismicGroundMotionSpectrumPy)
generate_from_xml(wavePassageEffect/WavePassageEffectPy)
generate_from_xml(modulation/ExponentialModulationPy)
generate_from_xml(modulation/ConstantModulationPy)
generate_from_xml(modulation/TrapezoidalModulationPy)
generate_from_xml(modulation/JenningsEtAl1968ModulationPy)
generate_from_xml(modulation/SaragoniHart1974ModulationPy)
generate_from_xml(modulation/BogdanoffGoldbergBernardModulationPy)
generate_from_xml(modulation/BoxCarModulationPy)




SET(SeismicLabTools_CPP_SRCS
    SeismicLabTools.cpp   
    spectrum/CloughPenzienSpectrum.cpp
    spectrum/KanaiTajimiSpectrum.cpp
    spectrum/HuZhouSpectrum.cpp
    spectrum/SeismicGroundMotionSpectrum.cpp
    coherence/LohAndLinCoherence.cpp
    coherence/HarichandranVanmarckeCoherence.cpp
    coherence/AbrahamsonCoherence.cpp
    wavePassageEffect/WavePassageEffect.cpp
    modulation/ExponentialModulation.cpp
    modulation/ConstantModulation.cpp
    modulation/TrapezoidalModulation.cpp
    modulation/JenningsEtAl1968Modulation.cpp
    modulation/SaragoniHart1974Modulation.cpp
    modulation/BogdanoffGoldbergBernardModulation.cpp
    modulation/BoxCarModulation.cpp

    
)

SET(SeismicLabTools_HPP_SRCS
    RPS.h
    SeismicLabTools.h
    spectrum/CloughPenzienSpectrum.h
    spectrum/KanaiTajimiSpectrum.h
    spectrum/HuZhouSpectrum.h
    spectrum/SeismicGroundMotionSpectrum.h
    coherence/LohAndLinCoherence.h
    coherence/HarichandranVanmarckeCoherence.h
    coherence/AbrahamsonCoherence.h
    wavePassageEffect/WavePassageEffect.h
    modulation/ExponentialModulation.h
    modulation/ConstantModulation.h
    modulation/TrapezoidalModulation.h
    modulation/JenningsEtAl1968Modulation.h
    modulation/SaragoniHart1974Modulation.h
    modulation/BogdanoffGoldbergBernardModulation.h
    modulation/BoxCarModulation.h

    
    
)

SET(SeismicLabTools_SRCS

    PreCompiled.cpp
    PreCompiled.h
)

SET(Python_SRCS
    spectrum/SeismicGroundMotionSpectrumPyImp.cpp
    spectrum/SeismicGroundMotionSpectrumPy.xml
    coherence/LohAndLinCoherencePyImp.cpp
    coherence/LohAndLinCoherencePy.xml
    coherence/HarichandranVanmarckeCoherencePyImp.cpp
    coherence/HarichandranVanmarckeCoherencePy.xml
    coherence/AbrahamsonCoherencePyImp.cpp
    coherence/AbrahamsonCoherencePy.xml
    wavePassageEffect/WavePassageEffectPy.xml
    wavePassageEffect/WavePassageEffectPyImp.cpp
    spectrum/CloughPenzienSpectrumPyImp.cpp
    spectrum/CloughPenzienSpectrumPy.xml
    spectrum/KanaiTajimiSpectrumPyImp.cpp
    spectrum/KanaiTajimiSpectrumPy.xml
    spectrum/HuZhouSpectrumPyImp.cpp
    spectrum/HuZhouSpectrumPy.xml
    modulation/ExponentialModulationPyImp.cpp
    modulation/ExponentialModulationPy.xml
    modulation/ConstantModulationPyImp.cpp
    modulation/ConstantModulationPy.xml
    modulation/TrapezoidalModulationPyImp.cpp
    modulation/TrapezoidalModulationPy.xml
    modulation/JenningsEtAl1968ModulationPyImp.cpp
    modulation/JenningsEtAl1968ModulationPy.xml
    modulation/SaragoniHart1974ModulationPyImp.cpp
    modulation/SaragoniHart1974ModulationPy.xml
    modulation/BogdanoffGoldbergBernardModulationPyImp.cpp
    modulation/BogdanoffGoldbergBernardModulationPy.xml
    modulation/BoxCarModulationPyImp.cpp
    modulation/BoxCarModulationPy.xml

    
)

SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    ${SeismicLabTools_CPP_SRCS}
    ${SeismicLabTools_HPP_SRCS}
    AppSeismicLabTools.cpp
    AppSeismicLabToolsPy.cpp
    PreCompiled.cpp
    PreCompiled.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The SeismicLab stuff

SET(SeismicLabTools_SRCS
    ${WindModule_SRCS}
    ${Python_SRCS}
)

SET(SeismicLabTools_PCH_SRCS
    ${WindModule_SRCS}
    ${Python_SRCS}

)

add_library(SeismicLabTools SHARED ${SeismicLabTools_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(SeismicLabTools ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(SeismicLabTools ${Boost_LIBRARIES})

target_link_libraries(SeismicLabTools ${SeismicLabTools_LIBS})
set_target_properties(SeismicLabTools PROPERTIES FOLDER "Workbenches/SeismicLabTools")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" SeismicLabTools_CPP_SRCS ${SeismicLabTools_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(SeismicLabTools PreCompiled.h PreCompiled.cpp SeismicLabTools_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(SeismicLabTools SeismicLabTools /Mod/SeismicLabTools)
SET_PYTHON_PREFIX_SUFFIX(SeismicLabTools)

INSTALL(TARGETS SeismicLabTools DESTINATION ${CMAKE_INSTALL_LIBDIR})
