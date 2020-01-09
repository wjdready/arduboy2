project = HelloWorld
buildDir = build

# 源文件
src += example/$(project)/$(project).cpp	
src += $(wildcard ./src/arduboy2/*.cpp)
src += $(wildcard ./src/hardware/*.cpp)

# 头文件路径
incDir += -I./src/arduboy2 -I./src/hardware 

# 用到的库
lib += -lpthread 

# 编译标志
cflag += $(incDir) $(lib)
cc = g++

$(project) : | $(buildDir)
	@$(cc) $(src) $(cflag) -o $(buildDir)/$(project) 

$(buildDir):
	@mkdir $(buildDir)

run: $(project) | $(buildDir)
	@cd $(buildDir) && ./$(project)

clear: | $(buildDir)
	@rm -rf $(buildDir)
