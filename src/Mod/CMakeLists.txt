if(BUILD_ADDONMGR)
  add_subdirectory(AddonManager)
endif(BUILD_ADDONMGR)

# if(BUILD_IDF)
#   add_subdirectory(Idf)
# endif(BUILD_IDF)

# if(BUILD_IMAGE)
#   add_subdirectory(Image)
# endif(BUILD_IMAGE)

if(BUILD_IMPORT)
  add_subdirectory(Import)
endif(BUILD_IMPORT)

if(BUILD_PART)
  add_subdirectory(Part)
  add_subdirectory(Measure)
endif(BUILD_PART)

if(BUILD_PLOT)
  add_subdirectory(Plot)
endif(BUILD_PLOT)

if(BUILD_SPREADSHEET)
  add_subdirectory(Spreadsheet)
endif(BUILD_SPREADSHEET)

if(BUILD_START)
  add_subdirectory(Start)
endif(BUILD_START)

#add_subdirectory(TemplatePyMod)

# if(BUILD_TEST)
#   add_subdirectory(Test)
# endif(BUILD_TEST)

if(BUILD_WEB)
  add_subdirectory(Web)
endif(BUILD_WEB)

if(BUILD_HELP)
  add_subdirectory(Help)
endif(BUILD_HELP)

if(BUILD_WindLab)
  add_subdirectory(WindLab)
  add_subdirectory(WindLabAPI)
  add_subdirectory(WindLabTools)
endif(BUILD_WindLab)

if(BUILD_SeismicLab)
  add_subdirectory(SeismicLab)
  add_subdirectory(SeismicLabAPI)
  add_subdirectory(SeismicLabTools)
endif(BUILD_SeismicLab)

if(BUILD_SeaLab)
  add_subdirectory(SeaLab)
  add_subdirectory(SeaLabAPI)
  add_subdirectory(SeaLabTools)
endif(BUILD_SeaLab)

if(BUILD_UserDefinedPhenomenonLab)
  add_subdirectory(UserDefinedPhenomenonLab)
  add_subdirectory(UserDefinedPhenomenonLabAPI)
endif(BUILD_UserDefinedPhenomenonLab)

if(BUILD_WindLabPlugin)
  add_subdirectory(WindLabPlugins)
endif(BUILD_WindLabPlugin)

if(BUILD_SeismicLabPlugin)
  add_subdirectory(SeismicLabPlugins)
endif(BUILD_SeismicLabPlugin)

if(BUILD_SeaLabPlugin)
  add_subdirectory(SeaLabPlugins)
endif(BUILD_SeaLabPlugin)

add_subdirectory(GeneralTools)