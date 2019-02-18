# ORB SLAM2 Windows 10 e Visual Studio
Original:
 - https://github.com/Phylliida/orbslam-windows
 - https://github.com/raulmur/ORB_SLAM2

# Instalação
 - Instalar Visual Studio com as ferramentas de C++ e Python
 - Instalar o CMake marcando “Add CMake to system PATH”
 - Instalar o Python e adicionar no PATH
 - Instalar o opencv e opencv_contrib ([https://www.learnopencv.com/install-opencv3-on-windows/](https://www.learnopencv.com/install-opencv3-on-windows/))
	 - Baixar source code
	 - Extrair na mesma pasta e anotar o caminho
	 - Gerar os arquivos do Visual Studio pelo cMake para o opencv*
		 - Marque “INSTALL_C_EXAMPLES” e “INSTALL_PYTHON_EXAMPLES”
		 - “OPENCV_EXTRA_MODULES_PATH” é o caminho pra subpasta modules do
		   opencv_contrib
		 - Desmarque “BUILD_opencv_saliency”
		 - Gere os aquivos
	 - Compilar arquivos gerados em modo release
		 - `cmake.exe --build . --config Release --target INSTALL`
	 - Adicionar no PATH (variáveis do sistema)
		 - {Caminho completo}\build\install\x64\vc15\bin

	 - Nas variáveis de usuário adicionar OPENCV_DIR com o caminho: build/install
	 - Testar exemplos
 - Git clone https://github.com/alexandremendoncaalvaro/orbslam-visualstudio.git
 - Compilar /Thirdparty/DBoW2
	 - Gerar os arquivos do Visual Studio pelo cMake*
	 	- Em “CMAKE_INSTALL_PREFIX” insira o caminho da pasta build/install
	 - Compilar lib no Visual Studio*
	 	- Vai dar vários Warnings mas não pode dar erro
 - Compilar /Thirdparty/eigen
	 - Gerar os arquivos do Visual Studio pelo cMake*
	 - Compilar arquivos gerados em modo release
	 	- `cmake.exe --build . --config Release --target INSTALL`
 - Compilar /Thirdparty/g2o
	 - Gerar os arquivos do Visual Studio pelo cMake*
		 - Em “CMAKE_INSTALL_PREFIX” insira o caminho da pasta build/install
		 - Em “EIGEN3_INCLUDE_DIR” e “G2O_EIGEN3_INCLUDE” insira o caminho da pasta /Thirdparty/eigen
	 - Compilar lib no Visual Studio*

**GERAR ARQUIVOS DO VISUAL STUDIO PELO CMAKE***
 - Criar uma pasta build na raiz do que será usado como fonte
 - Preencher os 2 campos com o caminho absoluto da pasta raiz e da pasta build
 - Clicar em Configure
 - Especificar a versão do Visual Studio (Visual Studio 15 2017 Win64)
 - O restante deixar default e clicar em finish
 - Se der muita linha vermelha, ir corrigindo e clicar em Configure novamente
 - Assim que corrigir tudo clicar em Generate
 - “Configuring done” indica q tudo está certo

**COMPILAR LIB NO VISUAL STUDIO***
 - Abra o projeto gerado pelo cMake no Visual Studio em modo Administrador
 - Mude para Release
 - Projeto com mesmo nome da Solution -> Properties
	 - Em General: Target Extension para .lib e Configuration Type para Static Library (.lib)
	 - Em C/C++  -> Code Generation: RuntimeLibrary para Multi-threaded (/MT)
 - Compilar o ALL_BUILD

**SEMPRE QUE ATUALIZAR VARIÁVEIS DE AMBIENTE RESETAR O TERMINAL**
