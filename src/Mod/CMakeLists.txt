if(BUILD_ADDONMGR)
  add_subdirectory(AddonManager)
endif(BUILD_ADDONMGR)

if(BUILD_PLOT)
  add_subdirectory(Plot)
endif(BUILD_PLOT)

if(BUILD_SPREADSHEET)
  add_subdirectory(Spreadsheet)
endif(BUILD_SPREADSHEET)

if(BUILD_START)
  add_subdirectory(Start)
endif(BUILD_START)

if(BUILD_TEST)
  add_subdirectory(Test)
endif(BUILD_TEST)

if(BUILD_WEB)
  add_subdirectory(Web)
endif(BUILD_WEB)

if(BUILD_HELP)
  add_subdirectory(Help)
endif(BUILD_HELP)

if(BUILD_WINDLAB)
  add_subdirectory(WindLab)
  add_subdirectory(WindLabAPI)
  add_subdirectory(WindLabTools)
endif(BUILD_WINDLAB)

if(BUILD_SEISMICLAB)
  add_subdirectory(SeismicLab)
  add_subdirectory(SeismicLabAPI)
  add_subdirectory(SeismicLabTools)
endif(BUILD_SEISMICLAB)

if(BUILD_SEALAB)
  add_subdirectory(SeaLab)
  add_subdirectory(SeaLabAPI)
  add_subdirectory(SeaLabTools)
endif(BUILD_SEALAB)

if(BUILD_USERLAB)
  add_subdirectory(UserLab)
  add_subdirectory(UserLabAPI)
endif(BUILD_USERLAB)

if(BUILD_WINDLAB_PLUGIN)
  add_subdirectory(WindLabPlugins)
endif(BUILD_WINDLAB_PLUGIN)

if(BUILD_SEISMICLAB_PLUGIN)
  add_subdirectory(SeismicLabPlugins)
endif(BUILD_SEISMICLAB_PLUGIN)

if(BUILD_SEALAB_PLUGIN)
  add_subdirectory(SeaLabPlugins)
endif(BUILD_SEALAB_PLUGIN)

if(BUILD_USERLAB_PLUGIN)
  add_subdirectory(UserLabPlugins)
endif(BUILD_USERLAB_PLUGIN)

add_subdirectory(GeneralTools)