if(MSVC)
    add_definitions(-DFCAppWindLabTools -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(WindLabTools_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND WindLabTools_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND WindLabTools_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(coherence/DavenportCoherencePy)
generate_from_xml(meanWindSpeed/DeavesHarrisMeanWindSpeedPy)
generate_from_xml(meanWindSpeed/LogarithmicMeanWindSpeedPy)
generate_from_xml(meanWindSpeed/PowerLawMeanWindSpeedPy)
generate_from_xml(meanWindSpeed/HongandHong2021MeanWindSpeedPy)


generate_from_xml(spectrum/WindSpectrumPy)
generate_from_xml(spectrum/KaimalSpectrumPy)
generate_from_xml(spectrum/SimuSpectrumPy)
generate_from_xml(spectrum/VonKarmanSpectrumPy)
generate_from_xml(spectrum/HarrisSpectrumPy)
generate_from_xml(spectrum/DavenportSpectrumPy)
generate_from_xml(spectrum/GeneralizedKaimalSpectrumPy)
generate_from_xml(spectrum/GeneralizedVonKarmanSpectrumPy)
generate_from_xml(modulation/ExponentialModulationPy)
generate_from_xml(modulation/SineModulationPy)
generate_from_xml(modulation/ThreeParametersModulationPy)
generate_from_xml(wavePassageEffect/WavePassageEffectPy)
generate_from_xml(coherence/KrenkCoherencePy)
generate_from_xml(turbulenceIntensity/TurbulenceIntensityPy)
generate_from_xml(modulation/DominikEtAl2013Py)



SET(WindLabTools_CPP_SRCS
    WindLabTools.cpp   
    spectrum/WindSpectrum.cpp
    spectrum/KaimalSpectrum.cpp
    spectrum/SimuSpectrum.cpp
    spectrum/VonKarmanSpectrum.cpp
    spectrum/HarrisSpectrum.cpp
    spectrum/DavenportSpectrum.cpp
    meanWindSpeed/DeavesHarrisMeanWindSpeed.cpp
    meanWindSpeed/LogarithmicMeanWindSpeed.cpp
    meanWindSpeed/PowerLawMeanWindSpeed.cpp
    meanWindSpeed/HongandHong2021MeanWindSpeed.cpp
    coherence/DavenportCoherence.cpp
    modulation/ExponentialModulation.cpp
    modulation/SineModulation.cpp
    modulation/DominikEtAl2013.cpp
    modulation/ThreeParametersModulation.cpp
    spectrum/GeneralizedKaimalSpectrum.cpp
    spectrum/GeneralizedVonKarmanSpectrum.cpp
    wavePassageEffect/WavePassageEffect.cpp
    coherence/KrenkCoherence.cpp
    turbulenceIntensity/TurbulenceIntensity.cpp

)

SET(WindLabTools_HPP_SRCS
    RPS.h
    WindLabTools.h
    spectrum/WindSpectrum.h
    spectrum/KaimalSpectrum.h
    spectrum/SimuSpectrum.h
    spectrum/VonKarmanSpectrum.h
    spectrum/HarrisSpectrum.h
    spectrum/DavenportSpectrum.h
    meanWindSpeed/DeavesHarrisMeanWindSpeed.h
    meanWindSpeed/LogarithmicMeanWindSpeed.h
    meanWindSpeed/PowerLawMeanWindSpeed.h
    meanWindSpeed/HongandHong2021MeanWindSpeed.h
    coherence/DavenportCoherence.h
    modulation/ExponentialModulation.h
    modulation/SineModulation.h
    modulation/ThreeParametersModulation.h
    modulation/DominikEtAl2013.h   
    spectrum/GeneralizedKaimalSpectrum.h
    spectrum/GeneralizedVonKarmanSpectrum.h
    wavePassageEffect/WavePassageEffect.h
    coherence/KrenkCoherence.h
    turbulenceIntensity/TurbulenceIntensity.h

)

SET(WindLabTools_SRCS

    PreCompiled.cpp
    PreCompiled.h
)

SET(Python_SRCS
    coherence/DavenportCoherencePy.xml
    coherence/DavenportCoherencePyImp.cpp
    meanWindSpeed/DeavesHarrisMeanWindSpeedPy.xml
    meanWindSpeed/DeavesHarrisMeanWindSpeedPyImp.cpp
    meanWindSpeed/LogarithmicMeanWindSpeedPy.xml
    meanWindSpeed/LogarithmicMeanWindSpeedPyImp.cpp
    meanWindSpeed/PowerLawMeanWindSpeedPy.xml
    meanWindSpeed/PowerLawMeanWindSpeedPyImp.cpp
    meanWindSpeed/HongandHong2021MeanWindSpeedPy.xml
    meanWindSpeed/HongandHong2021MeanWindSpeedPyImp.cpp
    spectrum/WindSpectrumPyImp.cpp
    spectrum/KaimalSpectrumPyImp.cpp
    spectrum/SimuSpectrumPyImp.cpp
    spectrum/VonKarmanSpectrumPyImp.cpp
    spectrum/HarrisSpectrumPyImp.cpp
    spectrum/DavenportSpectrumPyImp.cpp
    spectrum/GeneralizedKaimalSpectrumPyImp.cpp
    spectrum/GeneralizedVonKarmanSpectrumPyImp.cpp
    spectrum/WindSpectrumPy.xml
    spectrum/KaimalSpectrumPy.xml
    spectrum/SimuSpectrumPy.xml
    spectrum/VonKarmanSpectrumPy.xml
    spectrum/HarrisSpectrumPy.xml
    spectrum/DavenportSpectrumPy.xml
    spectrum/GeneralizedKaimalSpectrumPy.xml
    spectrum/GeneralizedVonKarmanSpectrumPy.xml
    modulation/SineModulationPyImp.cpp
    modulation/SineModulationPy.xml
    modulation/ThreeParametersModulationPyImp.cpp
    modulation/ThreeParametersModulationPy.xml
    modulation/ExponentialModulationPyImp.cpp
    modulation/ExponentialModulationPy.xml
    modulation/DominikEtAl2013PyImp.cpp
    modulation/DominikEtAl2013Py.xml
    wavePassageEffect/WavePassageEffectPy.xml
    wavePassageEffect/WavePassageEffectPyImp.cpp
    coherence/KrenkCoherencePy.xml
    coherence/KrenkCoherencePyImp.cpp
    turbulenceIntensity/TurbulenceIntensityPy.xml
    turbulenceIntensity/TurbulenceIntensityPyImp.cpp


)

SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    ${WindLabTools_CPP_SRCS}
    ${WindLabTools_HPP_SRCS}
    AppWindLabTools.cpp
    AppWindLabToolsPy.cpp
    PreCompiled.cpp
    PreCompiled.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The WindLab stuff

SET(WindLabTools_SRCS
    ${WindModule_SRCS}
    ${Python_SRCS}
)

SET(WindLabTools_PCH_SRCS
    ${WindModule_SRCS}
    ${Python_SRCS}

)

add_library(WindLabTools SHARED ${WindLabTools_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(WindLabTools ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(WindLabTools ${Boost_LIBRARIES})

target_link_libraries(WindLabTools ${WindLabTools_LIBS})
set_target_properties(WindLabTools PROPERTIES FOLDER "Workbenches/WindLabTools")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" WindLabTools_CPP_SRCS ${WindLabTools_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(WindLabTools PreCompiled.h PreCompiled.cpp WindLabTools_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(WindLabTools WindLabTools /Mod/WindLabTools)
SET_PYTHON_PREFIX_SUFFIX(WindLabTools)

INSTALL(TARGETS WindLabTools DESTINATION ${CMAKE_INSTALL_LIBDIR})
