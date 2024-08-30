#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base Class: Vehicle
class Vehicle {
protected:
    int vehicleID;
    string manufacturer;
    string model;
    int year;
    static int totalVehicles;

public:
    // Constructors
    Vehicle() : vehicleID(0), manufacturer(""), model(""), year(0) { totalVehicles++; }
    Vehicle(int id, string manu, string mod, int yr) : vehicleID(id), manufacturer(manu), model(mod), year(yr) { totalVehicles++; }

    // Destructor
    virtual ~Vehicle() { totalVehicles--; }

    // Getters and Setters
    int getVehicleID() const { return vehicleID; }
    void setVehicleID(int id) { vehicleID = id; }

    string getManufacturer() const { return manufacturer; }
    void setManufacturer(string manu) { manufacturer = manu; }

    string getModel() const { return model; }
    void setModel(string mod) { model = mod; }

    int getYear() const { return year; }
    void setYear(int yr) { year = yr; }

    static int getTotalVehicles() { return totalVehicles; }

    virtual void display() const {
        cout << "Vehicle ID: " << vehicleID << "\nManufacturer: " << manufacturer << "\nModel: " << model << "\nYear: " << year << endl;
    }
};

int Vehicle::totalVehicles = 0;

// Derived Class: Car (Single Inheritance)
class Car : public Vehicle {
protected:
    string fuelType;

public:
    Car() : Vehicle(), fuelType("") {}
    Car(int id, string manu, string mod, int yr, string fuel) : Vehicle(id, manu, mod, yr), fuelType(fuel) {}

    string getFuelType() const { return fuelType; }
    void setFuelType(string fuel) { fuelType = fuel; }

    void display() const override {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

// Derived Class: ElectricCar (Multilevel Inheritance)
class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar() : Car(), batteryCapacity(0) {}
    ElectricCar(int id, string manu, string mod, int yr, string fuel, int battery)
        : Car(id, manu, mod, yr, fuel), batteryCapacity(battery) {}

    int getBatteryCapacity() const { return batteryCapacity; }
    void setBatteryCapacity(int battery) { batteryCapacity = battery; }

    void display() const override {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

// Base Class for Multiple Inheritance: Aircraft
class Aircraft {
protected:
    int flightRange;

public:
    Aircraft() : flightRange(0) {}
    Aircraft(int range) : flightRange(range) {}

    int getFlightRange() const { return flightRange; }
    void setFlightRange(int range) { flightRange = range; }

    virtual void display() const {
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};

// Derived Class: FlyingCar (Multiple Inheritance from Car and Aircraft)
class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}
    FlyingCar(int id, string manu, string mod, int yr, string fuel, int range)
        : Car(id, manu, mod, yr, fuel), Aircraft(range) {}

    void display() const override {
        Car::display();
        Aircraft::display();
    }
};

// Derived Class: SportsCar (Multilevel Inheritance from ElectricCar)
class SportsCar : public ElectricCar {
protected:
    int topSpeed;

public:
    SportsCar() : ElectricCar(), topSpeed(0) {}
    SportsCar(int id, string manu, string mod, int yr, string fuel, int battery, int speed)
        : ElectricCar(id, manu, mod, yr, fuel, battery), topSpeed(speed) {}

    int getTopSpeed() const { return topSpeed; }
    void setTopSpeed(int speed) { topSpeed = speed; }

    void display() const override {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};

// Derived Class: Sedan (Hierarchical Inheritance from Car)
class Sedan : public Car {
public:
    Sedan() : Car() {}
    Sedan(int id, string manu, string mod, int yr, string fuel) : Car(id, manu, mod, yr, fuel) {}

    void display() const override {
        Car::display();
        cout << "Type: Sedan" << endl;
    }
};

// Derived Class: SUV (Hierarchical Inheritance from Car)
class SUV : public Car {
public:
    SUV() : Car() {}
    SUV(int id, string manu, string mod, int yr, string fuel) : Car(id, manu, mod, yr, fuel) {}

    void display() const override {
        Car::display();
        cout << "Type: SUV" << endl;
    }
};

// Class: VehicleRegistry
class VehicleRegistry {
private:
    vector<Vehicle*> vehicles;

public:
    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }

    void displayAllVehicles() const {
        for (const auto& vehicle : vehicles) {
            vehicle->display();
            cout << "---------------------" << endl;
        }
    }

    Vehicle* searchById(int id) const {
        for (const auto& vehicle : vehicles) {
            if (vehicle->getVehicleID() == id) {
                return vehicle;
            }
        }
        return nullptr;
    }
};

// Main Function
int main() {
    VehicleRegistry registry;
    int choice;

    do {
        cout << "\nVehicle Registry Menu\n";
        cout << "1. Add a vehicle\n";
        cout << "2. View all vehicles\n";
        cout << "3. Search by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int type, id, year, battery, range, speed;
            string manu, model, fuel;
            cout << "Choose vehicle type:\n1. Car\n2. ElectricCar\n3. FlyingCar\n4. SportsCar\n5. Sedan\n6. SUV\n";
            cin >> type;
            cout << "Enter Vehicle ID: "; cin >> id;
            cout << "Enter Manufacturer: "; cin >> manu;
            cout << "Enter Model: "; cin >> model;
            cout << "Enter Year: "; cin >> year;

            if (type == 1) {
                cout << "Enter Fuel Type: "; cin >> fuel;
                registry.addVehicle(new Car(id, manu, model, year, fuel));
            }
            else if (type == 2) {
                cout << "Enter Fuel Type: "; cin >> fuel;
                cout << "Enter Battery Capacity: "; cin >> battery;
                registry.addVehicle(new ElectricCar(id, manu, model, year, fuel, battery));
            }
            else if (type == 3) {
                cout << "Enter Fuel Type: "; cin >> fuel;
                cout << "Enter Flight Range: "; cin >> range;
                registry.addVehicle(new FlyingCar(id, manu, model, year, fuel, range));
            }
            else if (type == 4) {
                cout << "Enter Fuel Type: "; cin >> fuel;
                cout << "Enter Battery Capacity: "; cin >> battery;
                cout << "Enter Top Speed: "; cin >> speed;
                registry.addVehicle(new SportsCar(id, manu, model, year, fuel, battery, speed));
            }
            else if (type == 5) {
                cout << "Enter Fuel Type: "; cin >> fuel;
                registry.addVehicle(new Sedan(id, manu, model, year, fuel));
            }
            else if (type == 6) {
                cout << "Enter Fuel Type: "; cin >> fuel;
                registry.addVehicle(new SUV(id, manu, model, year, fuel));
            }
            break;
        }
        case 2: {
            registry.displayAllVehicles();
            break;
        }
        case 3: {
            int searchID;
            cout << "Enter Vehicle ID to search: ";
            cin >> searchID;
            Vehicle* foundVehicle = registry.searchById(searchID);
            if (foundVehicle) {
                foundVehicle->display();
            } else {
                cout << "Vehicle not found!\n";
            }
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
