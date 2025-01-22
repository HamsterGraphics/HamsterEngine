dofile("utils.lua")

--------------------------------------------------------------
-- Path
--------------------------------------------------------------
PlatformName = os.target()
RootPath = os.getenv("HG_BUILD_ROOT")
MakefilePath = path.join(RootPath, "Engine/Auto/Makefiles")
SourcePath = path.join(RootPath, "Engine/Source")
BuildOutputPath = path.join(RootPath, "Engine/Binaries")
--------------------------------------------------------------
-- Dump Info
--------------------------------------------------------------
Log.Info("-----------------------Path---------------------------")
Dump.PrintVar("PlatformName", PlatformName)
Dump.PrintVar("RootPath", RootPath)
Dump.PrintVar("MakefilePath", MakefilePath)
Dump.PrintVar("SourcePath", SourcePath)
Dump.PrintVar("BuildOutputPath", BuildOutputPath)
Log.Info("------------------------------------------------------")