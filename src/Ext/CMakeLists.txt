# this directory is the entry point for namespace modules. Any package
# installed to a directory "labrps" which is in sys.path can be imported
# with "from labrps import package" and is checked for a init_gui.py 
# module, which is imported at startup. (LabRPSGuiInit.py)

add_subdirectory(labrps)