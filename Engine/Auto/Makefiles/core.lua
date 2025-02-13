project("Core")
	kind("Utility")

	Project.CppLanguage()
	Project.Location(BuildOutputPath)
	Project.StaticRuntime("on")
	Project.CommonSettings()

    files {
        path.join(ModulePath, "Core/**.*")
    }

	vpaths {
		["Public"] = path.join(ModulePath, "Core/Public/**.*"),
		["Private"] = path.join(ModulesPath, "Core/Private/**.*")
	}