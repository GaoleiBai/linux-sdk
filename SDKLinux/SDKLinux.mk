##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SDKLinux
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/blue/Ubuntu One/compartido/SDKLinux"
ProjectPath            := "/home/blue/Ubuntu One/compartido/SDKLinux"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=blue
Date                   :=27/11/12
CodeLitePath           :="/home/blue/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/Collections_collection$(ObjectSuffix) $(IntermediateDirectory)/Collections_collection_exception$(ObjectSuffix) $(IntermediateDirectory)/Text_text$(ObjectSuffix) $(IntermediateDirectory)/Text_text_exception$(ObjectSuffix) $(IntermediateDirectory)/LFC_n_object$(ObjectSuffix) $(IntermediateDirectory)/LFC_exception$(ObjectSuffix) $(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/Tests_test_text$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Collections_collection$(ObjectSuffix): LFC/Collections/collection.cpp $(IntermediateDirectory)/Collections_collection$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Collections/collection.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Collections_collection$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Collections_collection$(DependSuffix): LFC/Collections/collection.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Collections_collection$(ObjectSuffix) -MF$(IntermediateDirectory)/Collections_collection$(DependSuffix) -MM "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Collections/collection.cpp"

$(IntermediateDirectory)/Collections_collection$(PreprocessSuffix): LFC/Collections/collection.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Collections_collection$(PreprocessSuffix) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Collections/collection.cpp"

$(IntermediateDirectory)/Collections_collection_exception$(ObjectSuffix): LFC/Collections/collection_exception.cpp $(IntermediateDirectory)/Collections_collection_exception$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Collections/collection_exception.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Collections_collection_exception$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Collections_collection_exception$(DependSuffix): LFC/Collections/collection_exception.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Collections_collection_exception$(ObjectSuffix) -MF$(IntermediateDirectory)/Collections_collection_exception$(DependSuffix) -MM "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Collections/collection_exception.cpp"

$(IntermediateDirectory)/Collections_collection_exception$(PreprocessSuffix): LFC/Collections/collection_exception.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Collections_collection_exception$(PreprocessSuffix) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Collections/collection_exception.cpp"

$(IntermediateDirectory)/Text_text$(ObjectSuffix): LFC/Text/text.cpp $(IntermediateDirectory)/Text_text$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Text/text.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Text_text$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Text_text$(DependSuffix): LFC/Text/text.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Text_text$(ObjectSuffix) -MF$(IntermediateDirectory)/Text_text$(DependSuffix) -MM "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Text/text.cpp"

$(IntermediateDirectory)/Text_text$(PreprocessSuffix): LFC/Text/text.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Text_text$(PreprocessSuffix) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Text/text.cpp"

$(IntermediateDirectory)/Text_text_exception$(ObjectSuffix): LFC/Text/text_exception.cpp $(IntermediateDirectory)/Text_text_exception$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Text/text_exception.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Text_text_exception$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Text_text_exception$(DependSuffix): LFC/Text/text_exception.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Text_text_exception$(ObjectSuffix) -MF$(IntermediateDirectory)/Text_text_exception$(DependSuffix) -MM "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Text/text_exception.cpp"

$(IntermediateDirectory)/Text_text_exception$(PreprocessSuffix): LFC/Text/text_exception.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Text_text_exception$(PreprocessSuffix) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/Text/text_exception.cpp"

$(IntermediateDirectory)/LFC_n_object$(ObjectSuffix): LFC/n_object.cpp $(IntermediateDirectory)/LFC_n_object$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/n_object.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/LFC_n_object$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LFC_n_object$(DependSuffix): LFC/n_object.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/LFC_n_object$(ObjectSuffix) -MF$(IntermediateDirectory)/LFC_n_object$(DependSuffix) -MM "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/n_object.cpp"

$(IntermediateDirectory)/LFC_n_object$(PreprocessSuffix): LFC/n_object.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LFC_n_object$(PreprocessSuffix) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/n_object.cpp"

$(IntermediateDirectory)/LFC_exception$(ObjectSuffix): LFC/exception.cpp $(IntermediateDirectory)/LFC_exception$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/exception.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/LFC_exception$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LFC_exception$(DependSuffix): LFC/exception.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/LFC_exception$(ObjectSuffix) -MF$(IntermediateDirectory)/LFC_exception$(DependSuffix) -MM "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/exception.cpp"

$(IntermediateDirectory)/LFC_exception$(PreprocessSuffix): LFC/exception.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LFC_exception$(PreprocessSuffix) "/home/blue/Ubuntu One/compartido/SDKLinux/LFC/exception.cpp"

$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/blue/Ubuntu One/compartido/SDKLinux/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/blue/Ubuntu One/compartido/SDKLinux/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/blue/Ubuntu One/compartido/SDKLinux/main.cpp"

$(IntermediateDirectory)/Tests_test_text$(ObjectSuffix): Tests/test_text.cpp $(IntermediateDirectory)/Tests_test_text$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/blue/Ubuntu One/compartido/SDKLinux/Tests/test_text.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Tests_test_text$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tests_test_text$(DependSuffix): Tests/test_text.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Tests_test_text$(ObjectSuffix) -MF$(IntermediateDirectory)/Tests_test_text$(DependSuffix) -MM "/home/blue/Ubuntu One/compartido/SDKLinux/Tests/test_text.cpp"

$(IntermediateDirectory)/Tests_test_text$(PreprocessSuffix): Tests/test_text.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Tests_test_text$(PreprocessSuffix) "/home/blue/Ubuntu One/compartido/SDKLinux/Tests/test_text.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Collections_collection$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Collections_collection$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Collections_collection$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Collections_collection_exception$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Collections_collection_exception$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Collections_collection_exception$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Text_text$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Text_text$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Text_text$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Text_text_exception$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Text_text_exception$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Text_text_exception$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/LFC_n_object$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/LFC_n_object$(DependSuffix)
	$(RM) $(IntermediateDirectory)/LFC_n_object$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/LFC_exception$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/LFC_exception$(DependSuffix)
	$(RM) $(IntermediateDirectory)/LFC_exception$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Tests_test_text$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Tests_test_text$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Tests_test_text$(PreprocessSuffix)
	$(RM) $(OutputFile)


