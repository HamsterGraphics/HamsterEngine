local function MakeExample(exampleFolder)
	local exampleName = path.getbasename(exampleFolder)
	project(exampleName)
		kind("ConsoleApp")
		dependson { "Application" }

		Project.CppLanguage()
		Project.Location(BuildOutputPath)
		Project.StaticRuntime("on")
		Project.CommonSettings()

		files {
			path.join(exampleFolder, "**.*")
		}

		includedirs {
			path.join(ModulesPath, "Core/Public"),
			path.join(ModulesPath, "OS/Public"),
			path.join(ModulesPath, "Application/Public"),
		}

		links {
			"Application"
		}
end

group("Samples")
local exampleFolders = os.matchdirs(path.join(SamplesPath, "*"))
for _, exampleFolder in pairs(exampleFolders) do
	MakeExample(exampleFolder)
end
group("")