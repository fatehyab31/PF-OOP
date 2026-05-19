//Fatehyab Ajaz F25bscs004
#include <iostream>  
#include <string>     
using namespace std;

// Class representing device
class Device {
private:
    string name;      // Device name
    bool ison;        // Device ON/OFF status
    int brightness;   // Brightness level (0-100)

public:
    // Default constructor
    Device() {
        name = "Unknown";       // Default name
        ison = false;           // Default status OFF
        brightness = 50;        // Default brightness
    }

    // Parameterized constructor
    Device(string aname, bool aison, int abrightness) {
        name = aname;
        ison = aison;
        setBrightness(abrightness);  // Set brightness using setter to ensure it's valid
    }

    // Destructor
    ~Device() {
        cout << "Device " << name << " is being removed." << endl;
    }

    // Setter for name
    void setName(string aname) {
        name = aname;
    }

    // Getter for name
    string getName() const {
        return name;
    }

    // Setter for brightness with validation
    void setBrightness(int abrightness) {
        if (abrightness >= 0 && abrightness <= 100) {
            brightness = abrightness;
            cout << "Brightness set to " << brightness << endl;
        }
        else {
            cout << "sorry invalid number " << endl;
        }
    }

    // Getter for brightness
    int getBrightness() const {
        return brightness;
    }

    // Turn device ON
    void turnOn() {
        ison = true;
    }

    // Turn device OFF
    void turnOff() {
        ison = false;
    }

    // Getting device status
    bool getStatus() const {
        return ison;
    }

    // Display device information
    void showInfo() const {
        cout << "Name: " << name
            << ", Status: " << (ison ? "ON" : "OFF")
            << ", Brightness: " << brightness
            << endl;
    }
};

// Class representing a room containing multiple devices
class Room {
private:
    string roomName;      // Name of the room
    Device devices[5];    // Array to store up to 5 devices
    int count;            // Current number of devices in the room

public:
    // Constructor
    Room(string name) {
        roomName = name;
        count = 0;        // Initially no devices
    }

    // Destructor
    ~Room() {
        cout << "Room " << roomName << " manager closed." << endl;
    }

    // Add a new device to the room
    void addDevice(const Device& d) {
        if (count < 5) {
            devices[count] = d;  // Add device to array
            count++;             // Increment count
            cout << "Device added successfully." << endl;
        }
        else {
            cout << "Room is full. Cannot add more devices." << endl;
        }
    }

    // Display all devices in the room
    void showAllDevices() const {
        if (count == 0) {
            cout << "No devices in this room." << endl;
            return;
        }
        for (int i = 0; i < count; i++) {
            devices[i].showInfo();  // Show info of each device
        }
    }

    // Find device index by name
    int findDevice(string name) {
        for (int i = 0; i < count; i++) {
            if (devices[i].getName() == name) {
                return i;   // Return index if found
            }
        }
        return -1;  // Return -1 if not found
    }

    // Toggle a device ON/OFF
    void toggleDevice(string name) {
        int index = findDevice(name);

        if (index == -1) {
            cout << "Device not found." << endl;
            return;
        }

        if (devices[index].getStatus()) {
            devices[index].turnOff();
            cout << name << " turned OFF." << endl;
        }
        else {
            devices[index].turnOn();
            cout << name << " turned ON." << endl;
        }
    }

    // Change brightness of a device
    void setDeviceBrightness(string name, int brightness) {
        int index = findDevice(name);

        if (index == -1) {
            cout << "Device not found." << endl;
            return;
        }

        devices[index].setBrightness(brightness);  // Update brightness
    }
};

// Main function for user interaction
int main() {
    Room r("LivingRoom");  // Create a room
    int choice;

    do {
        // Menu
        cout << "=== Smart Room Manager ===" << endl;
        cout << "1. Add a Device" << endl;
        cout << "2.Show All Devices" << endl;
        cout << "3.Turn Device ON / OFF" << endl;
        cout << "4.Change Brightness" << endl;
        cout << "5.Exit" << endl;
        cout << "Enter choice" << endl;
        cin >> choice;

        if (choice == 1) {
            // Add a new device
            string name;
            bool status;
            int brightness;
            cout << "Enter device name: ";
            cin >> name;
            cout << "Is the device ON? (1 for yes, 0 for no): ";
            cin >> status;
            cout << "Enter brightness (0-100): ";
            cin >> brightness;
            Device d(name, status, brightness);
            r.addDevice(d);

        }
        else if (choice == 2) {
            // Show all devices
            r.showAllDevices();

        }
        else if (choice == 3) {
            // Toggle a device
            string name;
            cout << "Enter device name to toggle: ";
            cin >> name;
            r.toggleDevice(name);

        }
        else if (choice == 4) {
            // Change device brightness
            string name;
            int brightness;
            cout << "Enter device name to change brightness: ";
            cin >> name;
            cout << "Enter new brightness (0-100): ";
            cin >> brightness;
            r.setDeviceBrightness(name, brightness);

        }

    } while (choice != 5);  // Loop until exit

    return 0;
}
