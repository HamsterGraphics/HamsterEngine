project("Application")
	kind("StaticLib")

	Project.CppLanguage()
	Project.Location(BuildOutputPath)
	Project.StaticRuntime("on")
	Project.CommonSettings()

	includedirs {
		path.join(ModulesPath, "Core/Public"),
		path.join(ModulesPath, "OS/Public"),
		path.join(ModulesPath, "Application/Public"),
	}
    
	files {
		path.join(ModulesPath, "Application/Public/**.*"),
		path.join(ModulesPath, "Application/Private/"..PlatformName.."/**.*")
	}

	vpaths {
		["Public"] = path.join(ModulesPath, "Application/Public/**.*"),
		["Private"] = path.join(ModulesPath, "Application/Private/"..PlatformName.."/**.*")
	}

	links {
		"OS"
	}