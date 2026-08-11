# Global Logistics & Smart Supply Chain Center (GLOSC)

A comprehensive C++ application for managing warehouse operations, fleet logistics, order processing, and shipment tracking in an integrated supply chain management system.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Build Instructions](#build-instructions)
- [Usage](#usage)
- [Modules](#modules)
- [Technologies Used](#technologies-used)
- [File Structure](#file-structure)

## Overview

GLOSC is a professional warehouse management system designed to streamline logistics operations through a centralized warehouse hub. The system integrates product management, inventory control, order processing, fleet management, and shipment tracking into a unified platform.

**Key Design Principle:** All operations flow through the Warehouse Central Hub, ensuring a logical and efficient workflow:
```
Warehouse → Fleet Management → Shipment Tracking → Order Processing
```

## Features

### Warehouse Management (Core Hub)
- **Product Catalog**: Binary Search Tree (BST) based product management
- **Inventory Management**: Template-based queue system for perishable items (FIFO)
- **Storage Bins**: Graph-based storage bin network with adjacency matrix
- **Category Management**: Dynamic category system with linked list structure
- **Replenishment System**: Automated low-stock alerts and reorder notifications
- **Product Types**: Support for Perishable, Durable, and Fragile products

### Order Management
- **Priority Processing**: Max-heap based priority queue for order handling
- **Order Sorting**: Multiple sorting algorithms (Selection, Quick, Counting Sort)
- **Order Search**: Binary search tree for efficient order lookup
- **Document Generation**: Automated receipt and order documentation
- **Loading System**: Stack-based loading bay management

### Fleet Management
- **Vehicle Management**: BST and Linked List implementations for vehicle tracking
- **Driver Assignment**: Driver-vehicle assignment system
- **Route Optimization**: Graph-based route planning with Dijkstra's algorithm
- **Vehicle Types**: Support for Trucks, Vans, and Bikes
- **Fuel Management**: Fuel consumption tracking and optimization

### Shipment Tracking
- **Shipment Management**: BST-based shipment tracking system
- **Priority Shipments**: Special handling for priority shipments
- **Route Network**: Graph-based city and route network
- **Analytics Engine**: Success rate calculation and delayed shipment alerts
- **Tracking Events**: Complete shipment history tracking
- **Graph Traversals**: BFS and DFS for route analysis

### User Interface
- **Professional UI**: Clean, modern, light-themed color palette
- **Visual Hierarchy**: Well-structured menus and sections
- **User-Friendly**: Intuitive navigation and clear prompts

## System Architecture

The system follows a modular architecture with the Warehouse as the central hub:

```
                    ┌─────────────────┐
                    │   WAREHOUSE     │
                    │  (Central Hub)  │
                    └────────┬────────┘
                             │
        ┌────────────────────┼────────────────────┐
        │                    │                    │
        ▼                    ▼                    ▼
┌──────────────┐    ┌──────────────┐    ┌──────────────┐
│   PRODUCTS   │    │    ORDERS    │    │    FLEET     │
│              │    │              │    │              │
│ - Catalog    │    │ - Processing │    │ - Vehicles   │
│ - Inventory  │    │ - Priority   │    │ - Drivers    │
│ - Storage    │    │ - Payment    │    │ - Routes     │
└──────┬───────┘    └───────┬──────┘    └────────┬─────┘
       │                    │                    │
       └────────────────────┼────────────────────┘
                            │
                            ▼
                    ┌──────────────┐
                    │   SHIPMENT   │
                    │   TRACKING   │
                    │              │
                    │ - Tracking   │
                    │ - Analytics  │
                    │ - Routes     │
                    └──────────────┘
```

## Project Structure

```
GLOSC/
├── Common/                      # Shared utilities and data structures
│   ├── AllStructures.h         # Common data structures (BST, Queue, Stack, Graph)
│   ├── linkedList.h            # Linked list implementations
│   ├── smartArray.h            # Dynamic array template
│   └── UITheme.h               # UI styling and color themes
│
├── WarehouseManagement/        # Core warehouse module
│   ├── wareHouse.h/cpp         # Main warehouse class
│   ├── Product.h/cpp           # Base product class
│   ├── PerishableProduct.*     # Perishable product implementation
│   ├── DurableProduct.*        # Durable product implementation
│   ├── FragileProduct.*        # Fragile product implementation
│   ├── ProductCatalog.*        # BST-based product catalog
│   ├── InventoryManager.*      # Template-based inventory queue
│   ├── StorageBin.*            # Storage bin with graph connections
│   ├── CategoryManager.*       # Product category management
│   ├── ReplishmentSystem.*     # Stock replenishment alerts
│   ├── Delivery.*              # Delivery scheduling
│   ├── Notification.*          # Notification system
│   ├── Payment.*               # Payment processing
│   └── module1Main.cpp         # Warehouse module entry point
│
├── OrderManagement/            # Order processing module
│   ├── OrderProcessor.*        # Main order processor
│   ├── Order.h                 # Order data structure
│   ├── PriorityManager.*       # Max-heap priority queue
│   ├── SortingEngine.*         # Sorting algorithms
│   ├── OrderBST.*              # Order binary search tree
│   ├── DocumentGenerator.*     # Receipt/document generation
│   └── Module3_Main.cpp        # Order module entry point
│
├── FleetManagement/            # Fleet and vehicle management
│   ├── Vehicle.*               # Vehicle base class
│   ├── Driver.*                # Driver management
│   ├── VehicleBST.*            # Vehicle binary search tree
│   ├── VehicleLL.*              # Vehicle linked list
│   ├── Graph.*                 # Route graph and Dijkstra's algorithm
│   └── fleetmangementmain.cpp  # Fleet module entry point
│
├── ShipmentTracking/           # Shipment tracking module
│   ├── shipment.*               # Shipment base class
│   ├── shipmentBST.*           # Shipment binary search tree
│   ├── shipmentGraph.*          # Route network graph
│   ├── analyticsEngine.*        # Analytics and reporting
│   ├── trackingEvent.*         # Tracking event management
│   └── ShipmentMAIN.cpp        # Shipment module entry point
│
├── Files/                      # Data files
│   ├── products.txt            # Product data
│   ├── orders.txt              # Order records
│   ├── categories.txt          # Category data
│   └── queue_log.txt           # Inventory queue logs
│
├── main.cpp                    # Main entry point
├── Makefile                    # Build configuration
└── README.md                   
```

## Prerequisites

- **Compiler**: GCC (G++) with C++17 support or higher
- **Operating System**: Windows, Linux, or macOS
- **Build Tool**: Make (or compatible build system)
- **Terminal**: ANSI color code support (for UI colors)

## Build Instructions

### Using Make (Recommended)

```bash
# Clean previous build
make clean

# Build the project
make

# Build and run
make run
```

### Manual Compilation

```bash
g++ -std=c++17 -Wall main.cpp \
    WarehouseManagement/*.cpp \
    FleetManagement/*.cpp \
    OrderManagement/*.cpp \
    ShipmentTracking/*.cpp \
    -o project
```

### Windows (Cygwin/MinGW)

```bash
# Using Make
make clean
make

# Or using g++ directly
g++ -std=c++17 -Wall main.cpp WarehouseManagement/*.cpp FleetManagement/*.cpp OrderManagement/*.cpp ShipmentTracking/*.cpp -o project.exe
```

## Usage

### Starting the Application

```bash
./project        # Linux/macOS
project.exe      # Windows
```

### Main Menu Navigation

1. **Warehouse Management System** - Access product catalog, inventory, and warehouse operations
2. **Fleet Management System** - Manage vehicles, drivers, and routes
3. **Order Management System** - Process orders, handle priorities, and generate receipts
4. **Shipment Tracking System** - Track shipments, manage routes, and view analytics

### Example Workflow

1. **Add Products**: Navigate to Warehouse Management → Add Product
2. **Create Order**: Navigate to Order Management → Add New Order
3. **Process Payment**: Navigate to Warehouse Management → Process Payment
4. **Assign Fleet**: Navigate to Fleet Management → Assign Driver to Vehicle
5. **Track Shipment**: Navigate to Shipment Tracking → Add Shipment

## Modules

### 1. Warehouse Management (Core Hub)
- **Purpose**: Central hub for all warehouse operations
- **Key Features**:
  - Product catalog with BST structure
  - FIFO inventory queue for perishables
  - Storage bin network with graph connections
  - Category-based product organization
  - Automated replenishment alerts

### 2. Order Management
- **Purpose**: Handle order processing and prioritization
- **Key Features**:
  - Priority-based order processing (Max-heap)
  - Multiple sorting algorithms
  - Order search and retrieval (BST)
  - Automated receipt generation
  - Loading bay management

### 3. Fleet Management
- **Purpose**: Manage vehicles, drivers, and delivery routes
- **Key Features**:
  - Vehicle management (BST and Linked List)
  - Driver assignment system
  - Route optimization (Dijkstra's algorithm)
  - Fuel consumption tracking
  - Multiple vehicle types support

### 4. Shipment Tracking
- **Purpose**: Track shipments and analyze logistics
- **Key Features**:
  - Shipment tracking with BST
  - Priority shipment handling
  - Route network management
  - Analytics and reporting
  - Graph traversals (BFS/DFS)

## Technologies Used

- **Language**: C++17
- **Data Structures**:
  - Binary Search Trees (BST)
  - Queues (FIFO)
  - Stacks (LIFO)
  - Linked Lists
  - Graphs (Adjacency Matrix)
  - Heaps (Max-Heap)
  - Dynamic Arrays
- **Algorithms**:
  - Dijkstra's Shortest Path
  - Sorting (Selection, Quick, Counting)
  - Binary Search
  - Graph Traversals (BFS, DFS)
- **Design Patterns**:
  - Template Programming
  - Inheritance and Polymorphism
  - Composition
  - Singleton Pattern

## Data Structures Overview

| Module | Primary Data Structures |
|--------|------------------------|
| Warehouse | BST (Product Catalog), Queue (Inventory), Graph (Storage Bins) |
| Orders | Max-Heap (Priority), BST (Order Search), Stack (Loading) |
| Fleet | BST (Vehicle Search), Linked List (Vehicle List), Graph (Routes) |
| Shipment | BST (Shipment Tree), Graph (Route Network), Dynamic Array |

## UI Design

The application features a professional, light-themed user interface with:
- Clean color palette (soft blues, grays, and accent colors)
- Well-structured visual hierarchy
- Consistent spacing and alignment
- Intuitive menu navigation
- Clear status messages and feedback

## File I/O

The system uses text files for data persistence:
- `Files/products.txt` - Product records
- `Files/orders.txt` - Order history
- `Files/categories.txt` - Category definitions
- `Files/queue_log.txt` - Inventory queue operations

## Notes

- All operations flow through the Warehouse Central Hub
- The system maintains data integrity through proper memory management
- Template-based implementations ensure type safety
- Forward declarations prevent circular dependencies
