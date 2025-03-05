#include "../headers/LLVMIR.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>

namespace iron {

    /**
     * @brief Links object files into an executable using LLVM's LLD linker
     * 
     * @param objects Vector of object file paths to link
     * @param exeName Name of the output executable
     * @param arch Target architecture (default: arm64)
     * @param macosxVersionMin Minimum macOS version (default: 15.0.0)
     * @throws std::runtime_error if the linker command fails
     */
    void LLVM::linkExecutable(const std::vector<std::string>& objects,
                          const std::string& exeName,
                          const std::string& arch,
                          const std::string& macosxVersionMin) {
        if (objects.empty()) {
            throw std::runtime_error("No object files provided for linking");
        }
        
        if (exeName.empty()) {
            throw std::runtime_error("No executable name provided for linking");
        }
        
        // Build the base command using -platform_version (the SDK version is assumed to be the same as the minimum version)
        std::string command = "ld64.lld -arch " + arch +
                              " -o " + exeName +
                              " -syslibroot $(xcrun --sdk macosx --show-sdk-path) " +
                              "-platform_version macos " + macosxVersionMin + " " + macosxVersionMin;

        // Append each object file to the command
        for (const auto& obj : objects) {
            if (obj.empty()) {
                std::cerr << "Warning: Empty object file path skipped" << std::endl;
                continue;
            }
            command += " " + obj;
        }

        // Append the system library
        command += " -lSystem";

        // Print the command for debugging purposes
        std::cout << "Executing: " << command << std::endl;

        // Execute the command
        int result = system(command.c_str());
        
        // Check if the command was successful
        if (result != 0) {
            throw std::runtime_error("Linker command failed with exit code: " + std::to_string(result));
        }
        
        std::cout << "Successfully linked executable: " << exeName << std::endl;
    }

}
