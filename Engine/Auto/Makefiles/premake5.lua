dofile("utils.lua")

--------------------------------------------------------------
-- Path
--------------------------------------------------------------
PlatformName = os.target()
RootPath = os.getenv("HG_BUILD_ROOT")
MakefilePath = path.join(RootPath, "Engine/Auto/Makefiles")
SourcePath = path.join(RootPath, "Engine/Source")
ModulesPath = path.join(SourcePath, "Modules")
BuildOutputPath = path.join(RootPath, "Engine/Binaries")
SamplesPath = path.join(SourcePath, "Samples")

--------------------------------------------------------------
-- Dump Info
--------------------------------------------------------------
Log.Info("-----------------------Path---------------------------")
Dump.PrintVar("PlatformName", PlatformName)
Dump.PrintVar("RootPath", RootPath)
Dump.PrintVar("MakefilePath", MakefilePath)
Dump.PrintVar("SourcePath", SourcePath)
Dump.PrintVar("ModulesPath", ModulesPath)
Dump.PrintVar("BuildOutputPath", BuildOutputPath)
Log.Info("------------------------------------------------------")

--------------------------------------------------------------
-- Workspace
--------------------------------------------------------------
workspace("HamsterEngine")
	location(RootPath)

	filter { "system:windows" }
		architecture("x86_64")
	filter { "system:macosx" }
		architecture("universal")
	filter {}
	systemversion("latest")

	configurations { "Debug", "Release" }
	filter { "configurations:Debug" }
		defines { "_DEBUG" }
		symbols("On")
		optimize("Off")
	filter { "configurations:Release" }
		defines { "NDEBUG" }
		symbols("On")
		optimize("Full")
	filter {}

--------------------------------------------------------------	
-- Projects
--------------------------------------------------------------
group("Modules")
dofile("application.lua")
dofile("core.lua")
dofile("os.lua")
group("")

dofile("samples.lua")