project("OS")
	kind("StaticLib")

	Project.CppLanguage()
	Project.Location(BuildOutputPath)
	Project.StaticRuntime("on")
	Project.CommonSettings()

	includedirs {
		path.join(ModulesPath, "Core/Public"),
		path.join(ModulesPath, "OS/Public"),
	}

	files {
		path.join(ModulesPath, "OS/Public/**.*"),
		path.join(ModulesPath, "OS/Private/"..PlatformName.."/**.*")
	}

	vpaths {
		["Public"] = path.join(ModulesPath, "OS/Public/**.*"),
		["Private"] = path.join(ModulesPath, "OS/Private/"..PlatformName.."/**.*")
	}