# 🏨 Hotel Reservation System

A comprehensive hotel management system implemented in C that handles guest reservations, staff management, and various hotel operations with efficient file handling, modular design, and an intuitive colorful user interface.

## ✨ Features

### 🎯 Core Functionality
- **👥 Guest Management**: Complete guest registration and profile management
- **📅 Reservation System**: Create, modify, and cancel room reservations
- **🚪 Check-in/Check-out**: Streamlined guest arrival and departure processing
- **👨‍💼 Staff Management**: Employee records and access control
- **🏠 Room Management**: Room availability tracking and assignment
- **💰 Billing System**: Automated checkout calculations with per-night rates
- **🔍 Search Capabilities**: Multiple search options for efficient data retrieval
- **⏰ Real-time Date/Time**: Uses system date and time for accurate timestamps

### 🔎 Search Functions
- **🏷️ Search by Guest Name**: Find reservations using guest information
- **🔢 Search by Room Number**: Locate specific room assignments
- **📆 Search by Date**: Filter reservations by check-in/check-out dates
- **🎯 Advanced Filtering**: Combine multiple search criteria

### 💳 Financial Management
- **💵 Per-night Rate Calculation**: Automatic billing based on room type and duration
- **✅ Checkout Validation**: Comprehensive bill verification and payment processing
- **💸 Rate Management**: Flexible pricing structure for different room categories
- **📊 Transaction Logging**: All transactions timestamped with system date/time

### 🎨 User Interface
- **🌈 Colorful Console Interface**: Vibrant color-coded menus and displays
- **🎭 Visual Feedback**: Color-coded status indicators and messages
- **📊 Enhanced Readability**: Clear formatting with colored text and backgrounds
- **⚡ Intuitive Navigation**: Easy-to-follow menu system with visual cues
- **⏰ Real-time Clock**: System date and time displayed throughout the interface

## 🏗️ System Architecture

### 📁 File Structure
The system uses a modular design with separate header files for better organization:

## 💾 File Handling

### 📄 File Types Used

#### 📦 Binary Files (.dat)
- **🎯 Purpose**: Fast read/write operations for structured data
- **🔧 Usage**: Guest records, reservations, staff information
- **✅ Benefits**: Efficient storage, faster access, smaller file sizes

#### 📝 Text Files (.txt)
- **🎯 Purpose**: Human-readable configuration and reference data
- **🔧 Usage**: Room configurations, system settings
- **✅ Benefits**: Easy manual editing, debugging, and backup

### 🔄 File Operations
- **➕ Create**: Initialize new data files with proper headers
- **📖 Read**: Load data structures from files into memory
- **💾 Write**: Save modified data back to files
- **📌 Append**: Add new records without overwriting existing data
- **🔄 Update**: Modify existing records in place
- **🛡️ Backup**: Create safety copies of critical data files
- **⏰ Timestamp Management**: All file operations logged with system date/time

## 🚀 Installation and Setup

### 📋 Prerequisites
- 🔧 GCC compiler (version 7.0 or higher)
- 📚 Standard C library
- 💾 Minimum 100MB free disk space

### ⚙️ Compilation
Navigate to project directory and compile:
- Use GCC to compile all source files
- Include header files directory
- Link with standard C library
- Generate executable file

## 🎮 Usage

### 🌟 Starting the System
1. 🚀 Launch the program
2. 🔐 Login with staff credentials
3. 🧭 Navigate through the colorful main menu options

### 🎯 Main Menu Options
1. **👥 Guest Management**
   - ➕ Add new guest
   - 👁️ View guest information
   - ✏️ Update guest details
   - 🔍 Search guests

2. **📋 Reservation Management**
   - 🆕 Create new reservation
   - 📝 Modify existing reservation
   - ❌ Cancel reservation
   - 👁️ View reservation details

3. **🚪 Check-in/Check-out**
   - 🏨 Process guest check-in
   - 🚶‍♂️ Handle guest check-out
   - 🧮 Calculate final bill
   - 🖨️ Print receipt

4. **👨‍💼 Staff Operations**
   - 👤 Add staff member
   - 🔄 Update staff information
   - 📂 View staff directory
   - 🔒 Manage access levels

5. **🔍 Search Functions**
   - 🏷️ Search by guest name
   - 🔢 Search by room number
   - 📅 Search by date range
   - 🎯 Advanced search options

### 🎪 Sample Workflow

#### 📋 Making a Reservation
1. 🎯 Select "Reservation Management" from main menu
2. 🆕 Choose "Create New Reservation"
3. 👤 Enter guest information or select existing guest
4. 🏠 Choose room type and dates
5. ✅ Confirm reservation details
6. 🏷️ System generates reservation ID

#### 🚶‍♂️ Check-out Process
1. 🎯 Select "Check-in/Check-out" from main menu
2. 🚪 Choose "Guest Check-out"
3. 🔍 Enter room number or guest name
4. 🧮 System calculates total charges
5. 💳 Process payment
6. 🖨️ Generate receipt and update records

## ✅ Data Validation

### 📝 Input Validation
- **📅 Date Format**: MM/DD/YYYY with leap year consideration
- **🔢 Room Numbers**: Valid room range checking
- **👤 Guest Information**: Email format and phone number validation
- **💳 Payment Processing**: Amount validation and payment method verification
- **⏰ Date/Time Logic**: Automatic validation against current system date/time

### 🔒 Data Integrity
- **🔗 Referential Integrity**: Guest IDs must exist before creating reservations
- **📅 Booking Conflicts**: Prevent double-booking of rooms
- **⏰ Date Logic**: Check-out date must be after check-in date
- **🕒 Real-time Validation**: All operations validated against current system date/time

### 👤 User Input
- ❌ Invalid menu selections
- 📅 Malformed date inputs
- 🔢 Out-of-range values
- ❗ Missing required fields

### 🖥️ System Errors
- 💾 Memory allocation failures
- 🗄️ Database corruption
- 🌐 Network connectivity issues
- 🛡️ Backup and recovery procedures

*📅 Last Updated: Jan 2025*  
