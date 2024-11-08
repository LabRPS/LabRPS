if(WIN32)
    add_definitions(-DFCApp)
    add_definitions(-DBOOST_DYN_LINK)
endif(WIN32)

if(LABRPS_RELEASE_SEH)
    add_definitions(-DHAVE_SEH)
endif(LABRPS_RELEASE_SEH)

# This causes some problems with the resource files to be found, especially with the StartPage
IF(RESOURCEDIR)
    add_definitions(-DRESOURCEDIR="${RESOURCEDIR}")
ENDIF(RESOURCEDIR)

IF(LIBRARYDIR)
    add_definitions(-DLIBRARYDIR="${LIBRARYDIR}")
ENDIF(LIBRARYDIR)

IF(DOCDIR)
    add_definitions(-DDOCDIR="${DOCDIR}")
ENDIF(DOCDIR)

#if you want to use the old DAG structure uncomment this line
#add_definitions(-DUSE_OLD_DAG)

# -----------------------------------------------------------------------------

#write relevant cmake variables to a file for later access with python. Exported are all variables 
#starting with BUILD. As the variable only exists if the user set it to ON a dict is useless, we
#use a python list for export.
set(_vars "const char CMakeVariables[] =\"cmake = [")
set(_delim "")
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    if (${_variableName})
        STRING(REGEX MATCH "^[_]?[^_]*" _prefix "${_variableName}_")
        if(${_prefix} STREQUAL "BUILD")
            STRING(REPLACE "\\" "\\\\" _name ${_variableName})
            set(_vars "${_vars}${_delim}\\n\"\n\"\\\"${_name}\\\"")
            set(_delim ",")
        endif()
    endif ()
endforeach()
set(_vars "${_vars}]\\n\" \n;")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/CMakeScript.hh "${_vars}" )

rps_copy_file_if_different(
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeScript.hh"
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeScript.h"
)

# -----------------------------------------------------------------------------

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
)

set(LabRPSApp_LIBS
    LabRPSBase
    ${Boost_LIBRARIES}
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND LabRPSApp_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND LabRPSApp_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(DocumentPy)
generate_from_xml(DocumentObjectPy)
generate_from_xml(ExtensionPy)
generate_from_xml(ExtensionContainerPy)
generate_from_xml(DocumentObjectExtensionPy)
generate_from_xml(GroupExtensionPy)
generate_from_xml(LinkBaseExtensionPy)
generate_from_xml(DocumentObjectGroupPy)
generate_from_xml(MetadataPy)
generate_from_xml(PropertyContainerPy)
generate_from_xml(SimulationPy)
generate_from_xml(RPSFeaturePy)
generate_from_py(LabRPSInit InitScript.h)
generate_from_py(LabRPSTest TestScript.h)

SET(LabRPSApp_XML_SRCS
    ExtensionPy.xml
    ExtensionContainerPy.xml
    DocumentObjectExtensionPy.xml
    GroupExtensionPy.xml
    LinkBaseExtensionPy.xml
    MetadataPy.xml
    DocumentObjectGroupPy.xml
    DocumentObjectPy.xml
    DocumentPy.xml
    PropertyContainerPy.xml
    SimulationPy.xml
    RPSFeaturePy.xml
)
SOURCE_GROUP("XML" FILES ${LabRPSApp_XML_SRCS})

# The document stuff
SET(Document_CPP_SRCS
    Document.cpp
    DocumentObject.cpp
    Extension.cpp
    ExtensionPyImp.cpp
    DocumentObjectExtension.cpp
    DocumentObjectExtensionPyImp.cpp
    ExtensionContainer.cpp
    ExtensionContainerPyImp.cpp
    GroupExtension.cpp
    GroupExtensionPyImp.cpp
    DocumentObjectFileIncluded.cpp
    DocumentObjectGroup.cpp
    DocumentObjectGroupPyImp.cpp
    DocumentObjectPyImp.cpp
    DocumentObserver.cpp
    DocumentObserverPython.cpp
    DocumentPyImp.cpp
    Expression.cpp
    FeaturePython.cpp
    FeatureTest.cpp
    Path.cpp
    Range.cpp
    Transactions.cpp
    TransactionalObject.cpp
    MergeDocuments.cpp
    TextDocument.cpp
    Link.cpp
    LinkBaseExtensionPyImp.cpp
    RPSFeature.cpp
    RPSFeaturePyImp.cpp
    Simulation.cpp
    SimulationPyImp.cpp
)

SET(Document_HPP_SRCS
    Document.h
    DocumentObject.h
    Extension.h
    ExtensionContainer.h
    GroupExtension.h
    DocumentObjectExtension.h
    DocumentObjectFileIncluded.h
    DocumentObjectGroup.h
    DocumentObserver.h
    DocumentObserverPython.h
    Expression.h
    ExpressionParser.h
    ExpressionVisitors.h
    FeatureCustom.h
    FeaturePython.h
    FeaturePythonPyImp.h
    FeaturePythonPyImp.inl
    FeatureTest.h
    Path.h
    Range.h
    Transactions.h
    TransactionalObject.h
    MergeDocuments.h
    TextDocument.h
    Link.h
    RPSFeature.h
    Simulation.h
)
SET(Document_SRCS
    ${Document_CPP_SRCS}
    ${Document_HPP_SRCS}
)
SOURCE_GROUP("Document" FILES ${Document_SRCS})

# The property stuff
SET(Properties_CPP_SRCS
    DynamicProperty.cpp
    ObjectIdentifier.cpp
    Property.cpp
    PropertyContainer.cpp
    PropertyContainerPyImp.cpp
    PropertyFile.cpp
    PropertyGeo.cpp
    PropertyLinks.cpp
    PropertyPythonObject.cpp
    PropertyStandard.cpp
    PropertyUnits.cpp
    PropertyExpressionEngine.cpp
)
SET(Properties_HPP_SRCS
    DynamicProperty.h
    ObjectIdentifier.h
    Property.h
    PropertyContainer.h
    PropertyFile.h
    PropertyGeo.h
    PropertyLinks.h
    PropertyPythonObject.h
    PropertyStandard.h
    PropertyUnits.h
    PropertyExpressionEngine.h
)
SET(Properties_SRCS
    ${Properties_CPP_SRCS}
    ${Properties_HPP_SRCS}
)
SOURCE_GROUP("Properties" FILES ${Properties_SRCS})

SET(LabRPSApp_CPP_SRCS
    ${Document_CPP_SRCS}
    ${Properties_CPP_SRCS}
    Application.cpp
    ApplicationPy.cpp
    AutoTransaction.cpp
    Branding.cpp
    Enumeration.cpp
    Metadata.cpp
    MetadataPyImp.cpp
    RPSpluginManager.cpp
    WindLabUtils.cpp
    SeismicLabUtils.cpp
    SeaLabUtils.cpp
    Color.cpp

)

SET(LabRPSApp_HPP_SRCS
    ${Document_HPP_SRCS}
    ${Properties_HPP_SRCS}
    Application.h
    AutoTransaction.h
    Branding.h
    Enumeration.h
    Metadata.h
    RPSpluginManager.h
    WindLabUtils.h
    SeismicLabUtils.h
    SeaLabUtils.h
    Color.h

)

SET(LabRPSApp_SRCS
    ${LabRPSApp_CPP_SRCS}
    ${LabRPSApp_HPP_SRCS}
    ${LabRPSApp_XML_SRCS}
    LabRPSInit.py
    LabRPSTest.py
    PreCompiled.cpp
    PreCompiled.h
)

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    ADD_MSVC_PRECOMPILED_HEADER(LabRPSApp PreCompiled.h PreCompiled.cpp LabRPSApp_CPP_SRCS)
endif(LABRPS_USE_PCH)

add_library(LabRPSApp SHARED ${LabRPSApp_SRCS})

target_link_libraries(LabRPSApp ${LabRPSApp_LIBS})
set_target_properties(LabRPSApp PROPERTIES FOLDER "App")

add_dependencies(LabRPSApp rps_version)

SET_BIN_DIR(LabRPSApp LabRPSApp)

if(WIN32)
    INSTALL(TARGETS LabRPSApp
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
else(WIN32)
    INSTALL(TARGETS LabRPSApp
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif(WIN32)
