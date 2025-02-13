#include "../headers/LLVMIR.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

namespace iron {

    void LLVM::linkExecutable(const std::vector<std::string>& objects,
                          const std::string& exeName,
                          const std::string& arch = "arm64",
                          const std::string& macosxVersionMin = "15.0.0") {
        // Build the base command using -platform_version (the SDK version is assumed to be the same as the minimum version)
        std::string command = "ld64.lld -arch " + arch +
                              " -o " + exeName +
                              " -syslibroot $(xcrun --sdk macosx --show-sdk-path) " +
                              "-platform_version macos " + macosxVersionMin + " " + macosxVersionMin;

        // Append each object file to the command
        for (const auto& obj : objects) {
            command += " " + obj;
        }

        // Append the system library
        command += " -lSystem";

        // Print the command for debugging purposes
        std::cout << "Executing: " << command << std::endl;

        // Execute the command
        int result = system(command.c_str());
        // Optionally, handle the result if needed (e.g., check if result != 0)
    }


}
