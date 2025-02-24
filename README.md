# Ray_Tracing_Workshop
 Intro to Ray Tracing Workshop for ACM club at UC Merced

# Setting Up the Project
<p> Follow these steps to set up the project before the workshop, if you want to create your own ray tracer </p>

# Install Visual Studio
<p> If you do not already have Visual Studio installed, follow these directions: </p>
<p> Go to https://visualstudio.microsoft.com/ and select "Download Visual Studio", then run VisualStudioSetup.exe</p>

<p> Once you get to the installation process, make sure you select "Desktop development with C++" </p>

![image](https://drive.google.com/uc?export=view&id=1fFSGMovtMwt09WpiBKORRi0p2y2o-xqb)

<p> After Visual Studio is done installing, you can choose to log in through GitHub or Microsoft if you have an account </p>

# Install CMake
<p> If CMake is not already installed, follow these directions: </p>
<p> Go to https://cmake.org/download/ and download cmake </p>

<p> During the installation process, it will ask you where you want it to be downloaded. Wherever is fine </p>

![image](https://drive.google.com/uc?export=view&id=1fOBcfipNVsilY0_UnENMIBqTjXxIDEtp)

<p> After that, you can choose to add CMake as a desktop shortcut, otherwise remember where CMake was downloaded </p>

![image](https://drive.google.com/uc?export=view&id=1d4Ly2WZvmfV4lpo8kO1PMr7BU2zPGZnN)

# Downloading the Project
<p> Click on the green "<> Code" button in the repository, select Download ZIP, and extract the files into a folder </p>

![image](https://drive.google.com/uc?export=view&id=1HbqVs3_9Fgp_53rdUnzmCweSGYo0tAjE)

<p> If you have Git or GitHub Desktop on your device, you can choose to download the project that way </p>

# Building the Project
<p> Open the CMake GUI. This should be in your desktop shortcuts, or open the folder where you downloaded it and run bin/cmake-gui.exe </p>
<p> Once it opens, select "Browse Source" and navigate to the folder of the project you downloaded from GitHub </p>
<p> Select "Browse Build" and navigate to the same folder. Add "/cmake_build" at the end to put the built project in that folder. It will ask if you want to create a new foldercalled cmake_build, select yes </p>

![image](https://drive.google.com/uc?export=view&id=150RgTDN36iMxMrXClhtIy3AaDDHGU_91)

<p> Once you are done, hit "Configure" </p>
<p> Make sure the correct version of Visual Studio is selected (In this case Visual Studio 17 2022), and make sure "Use Default Native Compilers" is selected </p>

![image](https://drive.google.com/uc?export=view&id=1I6TgDNOC6UiQERuNNg5hMzJfCfnPOAN2)

<p> Click "Finish", then wait for configuration to complete. It should look like this: </p>

![image](https://drive.google.com/uc?export=view&id=1xAcjELaBymHErpjxA2fMgvwcVRP3K3Fc)

<p> Then click "Generate", and wait for the project generation to complete </p>

![image](https://drive.google.com/uc?export=view&id=1IsrtiTehEHWYZHnyzkZQlW5IYMGyBTxA)

<p> Now, head over to the file location of the project and there should be a folder called cmake_build with a file "Ray_Tracing_Workshop.sln". Go ahead and open it with Visual Studio </p>

# Running the Project
<p> With the project opened in Visual Studio, right click the project "Ray_Tracing_Workshop" and select "Set as Startup Project" </p>

![image](https://drive.google.com/uc?export=view&id=16mY4PHUmn-RnXhj9Eiwrd8quMbREZsKj)

<p> Now run "Local Windows Debugger" to build and run the project. If everything builds and compiles correctly, the project should start </p>

![image](https://drive.google.com/uc?export=view&id=1PtkmUHXAk9X8IaroemJNh4EBEC0ZMunW)

<p> Once you run the project and the window opens, you should see this: </p>

![image](https://drive.google.com/uc?export=view&id=1FQrkTMzAjb8hBALEdFNI24da0AI-36z_)

<p> You are now ready to start ray tracing! </p>
