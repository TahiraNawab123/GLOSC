#ifndef UI_THEME_H
#define UI_THEME_H

#include <iostream>
#include <string>
#include <iomanip>

// Warehouse-themed color codes (ANSI) - Original Blue Scheme
namespace WarehouseTheme {
    // Industrial colors
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    
    // Primary warehouse colors - Blue scheme
    const std::string WAREHOUSE_BLUE = "\033[38;5;27m";      // Deep industrial blue
    const std::string WAREHOUSE_DARK_BLUE = "\033[38;5;18m";  // Deep corporate blue
    const std::string WAREHOUSE_LIGHT_BLUE = "\033[38;5;39m"; // Light professional blue
    const std::string WAREHOUSE_GRAY = "\033[38;5;240m";     // Industrial gray
    const std::string WAREHOUSE_DARK_GRAY = "\033[38;5;238m"; // Dark gray for emphasis
    const std::string WAREHOUSE_LIGHT_GRAY = "\033[38;5;250m"; // Light gray for subtle text
    const std::string WAREHOUSE_GREEN = "\033[38;5;34m";      // Success green
    const std::string WAREHOUSE_RED = "\033[38;5;196m";       // Alert red
    const std::string WAREHOUSE_YELLOW = "\033[38;5;226m";   // Warning yellow
    const std::string WAREHOUSE_CYAN = "\033[38;5;51m";      // Info cyan
    
    // Background colors
    const std::string BG_DARK = "\033[48;5;235m";
    const std::string BG_LIGHT = "\033[48;5;252m";
    
    // Utility functions
    inline void printHeader(const std::string& title) {
        std::cout << "\n" << WAREHOUSE_BLUE << BOLD 
                  << "╔════════════════════════════════════════════════════════════╗" << RESET << "\n"
                  << WAREHOUSE_BLUE << BOLD 
                  << "║" << std::setw(58) << std::left << ("  " + title) << "║" << RESET << "\n"
                  << WAREHOUSE_BLUE << BOLD 
                  << "╚════════════════════════════════════════════════════════════╝" << RESET << "\n";
    }
    
    inline void printSection(const std::string& title) {
        std::cout << "\n" << WAREHOUSE_BLUE << BOLD 
                  << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << "\n"
                  << WAREHOUSE_BLUE << BOLD << "  " << title << RESET << "\n"
                  << WAREHOUSE_BLUE << BOLD 
                  << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << "\n";
    }
    
    inline void printSuccess(const std::string& message) {
        std::cout << WAREHOUSE_GREEN << "✓ " << message << RESET << "\n";
    }
    
    inline void printError(const std::string& message) {
        std::cout << WAREHOUSE_RED << "✗ " << message << RESET << "\n";
    }
    
    inline void printInfo(const std::string& message) {
        std::cout << WAREHOUSE_CYAN << "ℹ " << message << RESET << "\n";
    }
    
    inline void printWarning(const std::string& message) {
        std::cout << WAREHOUSE_YELLOW << "⚠ " << message << RESET << "\n";
    }
    
    inline void printMenuOption(int num, const std::string& text) {
        std::cout << WAREHOUSE_BLUE << "  " << num << ". " << RESET << text << "\n";
    }
    
    inline void printWarehouseHub() {
        std::cout << "\n" << WAREHOUSE_BLUE << BOLD 
                  << "╔═══════════════════════════════════════════════════════════════════════════╗" << RESET << "\n"
                  << WAREHOUSE_BLUE << BOLD 
                  << "║" << std::setw(71) << std::left << "  🏭 WAREHOUSE MANAGEMENT SYSTEM - CENTRAL HUB" << "║" << RESET << "\n"
                  << WAREHOUSE_BLUE << BOLD 
                  << "╚═══════════════════════════════════════════════════════════════════════════╝" << RESET << "\n";
    }
    
    inline void printPrompt(const std::string& prompt) {
        std::cout << "\n" << WAREHOUSE_BLUE << BOLD << prompt << RESET << " ";
    }
}

#endif

