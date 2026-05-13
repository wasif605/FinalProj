#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int safeIntInput() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return value;
}

// ========== SEAT CLASS ==========
class Seat {
    int  seatNumber;
    bool isBooked;
    bool isCrewReserved;
public:
    Seat(int num = 0, bool booked = false, bool reserved = false);
    int  getSeatNumber()     const;
    bool getIsBooked()       const;
    bool getIsCrewReserved() const;
    void setSeatNumber(int num);
    void setIsBooked(bool b);
    void setIsCrewReserved(bool r);
    bool isAvailable() const;
    void book();
    void unbook();
    bool isWindow()  const;
    bool isCrewSeat()const;
};

Seat::Seat(int num, bool booked, bool reserved)
    : seatNumber(num), isBooked(booked), isCrewReserved(reserved) {
}

int Seat::getSeatNumber() const { return seatNumber; }
bool Seat::getIsBooked() const { return isBooked; }
bool Seat::getIsCrewReserved() const { return isCrewReserved; }
void Seat::setSeatNumber(int num) { seatNumber = num; }
void Seat::setIsBooked(bool b) { isBooked = b; }
void Seat::setIsCrewReserved(bool r) { isCrewReserved = r; }
bool Seat::isAvailable() const { return !isBooked && !isCrewReserved; }
void Seat::book() { isBooked = true; }
void Seat::unbook() { isBooked = false; }
bool Seat::isWindow() const { return seatNumber % 6 == 0; }
bool Seat::isCrewSeat() const { return isCrewReserved; }

// ========== FLIGHT BASE CLASS ==========
class Flight {
protected:
    string name, origin, destination;
    int    type;
    string flightNumber, departureTime, departureDay;
    int    availableSeats;
public:
    Seat seats[110];
    Flight(string n, string o, string d, int t,
        string fNum, string time, string day);
    string getName()          const;
    string getOrigin()        const;
    string getDestination()   const;
    int    getType()          const;
    string getFlightNumber()  const;
    string getDepartureTime() const;
    string getDepartureDay()  const;
    int    getAvailableSeats()const;
    void   setName(string n);
    void   setOrigin(string o);
    void   setDestination(string d);
    void   setType(int t);
    void   setFlightNumber(string fn);
    void   setDepartureTime(string dt);
    void   setDepartureDay(string dd);
    void   setAvailableSeats(int s);
    virtual double getMultiplier() = 0;
    virtual int    getBusinessBaggage() = 0;
    virtual int    getEconomyBaggage() = 0;
    virtual int    getBaggageChargePerKg() = 0;
    virtual string getFlightInfo()         const;
    virtual ~Flight() {}
};

Flight::Flight(string n, string o, string d, int t,
    string fNum, string time, string day)
    : name(n), origin(o), destination(d), type(t),
    flightNumber(fNum), departureTime(time), departureDay(day),
    availableSeats(107)
{
    for (int i = 0; i < 110; i++) {
        bool reserved = (i == 33 || i == 36 || i == 76);
        seats[i] = Seat(i + 1, false, reserved);
    }
}

string Flight::getName() const { return name; }
string Flight::getOrigin() const { return origin; }
string Flight::getDestination() const { return destination; }
int Flight::getType() const { return type; }
string Flight::getFlightNumber() const { return flightNumber; }
string Flight::getDepartureTime() const { return departureTime; }
string Flight::getDepartureDay() const { return departureDay; }
int Flight::getAvailableSeats() const { return availableSeats; }
void Flight::setName(string n) { name = n; }
void Flight::setOrigin(string o) { origin = o; }
void Flight::setDestination(string d) { destination = d; }
void Flight::setType(int t) { type = t; }
void Flight::setFlightNumber(string fn) { flightNumber = fn; }
void Flight::setDepartureTime(string dt) { departureTime = dt; }
void Flight::setDepartureDay(string dd) { departureDay = dd; }
void Flight::setAvailableSeats(int s) { availableSeats = s; }

string Flight::getFlightInfo() const {
    return flightNumber + " | " + name + " | " + origin + " -> " + destination
        + " | " + departureDay + " " + departureTime;
}

// ========== AIRLINE SUBCLASSES ==========
class SereneAir : public Flight {
public:
    SereneAir(string o, string d, int t, string fNum, string time, string day);
    double getMultiplier()         override;
    int    getBusinessBaggage()    override;
    int    getEconomyBaggage()     override;
    int    getBaggageChargePerKg() override;
};

SereneAir::SereneAir(string o, string d, int t, string fNum, string time, string day)
    : Flight("Serene Air", o, d, t, fNum, time, day) {
}

double SereneAir::getMultiplier() { return 1.1; }
int SereneAir::getBusinessBaggage() { return (type == 1) ? 35 : 45; }
int SereneAir::getEconomyBaggage() { return (type == 1) ? 25 : 35; }
int SereneAir::getBaggageChargePerKg() { return (type == 1) ? 1000 : 2000; }

class PIA : public Flight {
public:
    PIA(string o, string d, int t, string fNum, string time, string day);
    double getMultiplier()         override;
    int    getBusinessBaggage()    override;
    int    getEconomyBaggage()     override;
    int    getBaggageChargePerKg() override;
};

PIA::PIA(string o, string d, int t, string fNum, string time, string day)
    : Flight("PIA", o, d, t, fNum, time, day) {
}

double PIA::getMultiplier() { return 1.0; }
int PIA::getBusinessBaggage() { return (type == 1) ? 30 : 40; }
int PIA::getEconomyBaggage() { return (type == 1) ? 20 : 30; }
int PIA::getBaggageChargePerKg() { return (type == 1) ? 1000 : 2000; }

class AirBlue : public Flight {
public:
    AirBlue(string o, string d, int t, string fNum, string time, string day);
    double getMultiplier()         override;
    int    getBusinessBaggage()    override;
    int    getEconomyBaggage()     override;
    int    getBaggageChargePerKg() override;
};

AirBlue::AirBlue(string o, string d, int t, string fNum, string time, string day)
    : Flight("AirBlue", o, d, t, fNum, time, day) {
}

double AirBlue::getMultiplier() { return 0.9; }
int AirBlue::getBusinessBaggage() { return (type == 1) ? 28 : 38; }
int AirBlue::getEconomyBaggage() { return (type == 1) ? 18 : 28; }
int AirBlue::getBaggageChargePerKg() { return (type == 1) ? 1000 : 2000; }

class AirSial : public Flight {
public:
    AirSial(string o, string d, int t, string fNum, string time, string day);
    double getMultiplier()         override;
    int    getBusinessBaggage()    override;
    int    getEconomyBaggage()     override;
    int    getBaggageChargePerKg() override;
};

AirSial::AirSial(string o, string d, int t, string fNum, string time, string day)
    : Flight("AirSial", o, d, t, fNum, time, day) {
}

double AirSial::getMultiplier() { return 1.2; }
int AirSial::getBusinessBaggage() { return (type == 1) ? 40 : 50; }
int AirSial::getEconomyBaggage() { return (type == 1) ? 30 : 40; }
int AirSial::getBaggageChargePerKg() { return (type == 1) ? 1000 : 2000; }

// ========== PASSENGER BASE CLASS ==========
class Passenger {
protected:
    string name, address, nationality, cnic;
    int    age, baggageWeight;
public:
    Passenger(string n = "", string a = "", string nat = "",
        string c = "", int ag = 0, int bag = 0);
    string getName()         const;
    string getAddress()      const;
    string getNationality()  const;
    string getCNIC()         const;
    int    getAge()          const;
    int    getBaggageWeight()const;
    void   setName(string n);
    void   setAddress(string a);
    void   setNationality(string nat);
    void   setCNIC(string c);
    void   setAge(int ag);
    void   setBaggageWeight(int bw);
    virtual int calculateFare(int seatNo, int flightType) = 0;
    virtual int getFreeBaggage(int classType) = 0;
    virtual int getBaggageCharge() = 0;
    virtual ~Passenger() {}
};

Passenger::Passenger(string n, string a, string nat,
    string c, int ag, int bag)
    : name(n), address(a), nationality(nat), cnic(c), age(ag), baggageWeight(bag) {
}

string Passenger::getName() const { return name; }
string Passenger::getAddress() const { return address; }
string Passenger::getNationality() const { return nationality; }
string Passenger::getCNIC() const { return cnic; }
int Passenger::getAge() const { return age; }
int Passenger::getBaggageWeight() const { return baggageWeight; }
void Passenger::setName(string n) { name = n; }
void Passenger::setAddress(string a) { address = a; }
void Passenger::setNationality(string nat) { nationality = nat; }
void Passenger::setCNIC(string c) { cnic = c; }
void Passenger::setAge(int ag) { age = ag; }
void Passenger::setBaggageWeight(int bw) { baggageWeight = bw; }

// ========== PASSENGER SUBCLASSES ==========
class DomesticPassenger : public Passenger {
public:
    DomesticPassenger(string n = "", string a = "", string nat = "",
        string c = "", int ag = 0, int bag = 0);
    int calculateFare(int seatNo, int flightType) override;
    int getFreeBaggage(int classType)             override;
    int getBaggageCharge()                        override;
};

DomesticPassenger::DomesticPassenger(string n, string a, string nat,
    string c, int ag, int bag)
    : Passenger(n, a, nat, c, ag, bag) {
}

int DomesticPassenger::calculateFare(int seatNo, int) {
    int fare = (seatNo < 25) ? 20000 : 15000;
    if (age < 12) fare = (int)(fare * 0.7);
    if ((seatNo + 1) % 6 == 0) fare += 2000;
    return fare;
}

int DomesticPassenger::getFreeBaggage(int classType) { return (classType == 1) ? 30 : 20; }
int DomesticPassenger::getBaggageCharge() { return 1000; }

class InternationalPassenger : public Passenger {
public:
    InternationalPassenger(string n = "", string a = "", string nat = "",
        string c = "", int ag = 0, int bag = 0);
    int calculateFare(int seatNo, int flightType) override;
    int getFreeBaggage(int classType)             override;
    int getBaggageCharge()                        override;
};

InternationalPassenger::InternationalPassenger(string n, string a, string nat,
    string c, int ag, int bag)
    : Passenger(n, a, nat, c, ag, bag) {
}

int InternationalPassenger::calculateFare(int seatNo, int) {
    int fare = (seatNo < 25) ? 90000 : 70000;
    if (age < 12) fare = (int)(fare * 0.7);
    if ((seatNo + 1) % 6 == 0) fare += 2000;
    return fare;
}

int InternationalPassenger::getFreeBaggage(int classType) { return (classType == 1) ? 40 : 30; }
int InternationalPassenger::getBaggageCharge() { return 2000; }

// ========== BOOKING CLASS ==========
class Booking {
    Seat       seat;
    Passenger* passenger;
    int        fare;
    int        baggageFare;
    Flight* flight;
    int        classType;
    string     bookingID;
public:
    Booking(Seat s, Passenger* p, int f, int bf,
        Flight* fl, int ct, string bid);
    int        getFare()          const;
    int        getBaggageFare()   const;
    int        getTotalFare()     const;
    string     getPassengerName() const;
    string     getPassengerCNIC() const;
    int        getSeatNumber()    const;
    string     getFlightInfo()    const;
    string     getFlightNumber()  const;
    string     getBookingID()     const;
    int        getClassType()     const;
    Seat       getSeat()          const;
    Passenger* getPassenger()     const;
    Flight* getFlight()        const;
    void       setFare(int f);
    void       setBaggageFare(int bf);
    void       setClassType(int ct);
    void       setBookingID(string bid);
};

Booking::Booking(Seat s, Passenger* p, int f, int bf,
    Flight* fl, int ct, string bid)
    : seat(s), passenger(p), fare(f), baggageFare(bf),
    flight(fl), classType(ct), bookingID(bid) {
}

int Booking::getFare() const { return fare; }
int Booking::getBaggageFare() const { return baggageFare; }
int Booking::getTotalFare() const { return fare + baggageFare; }
string Booking::getPassengerName() const { return passenger->getName(); }
string Booking::getPassengerCNIC() const { return passenger->getCNIC(); }
int Booking::getSeatNumber() const { return seat.getSeatNumber(); }
string Booking::getFlightInfo() const { return flight->getFlightInfo(); }
string Booking::getFlightNumber() const { return flight->getFlightNumber(); }
string Booking::getBookingID() const { return bookingID; }
int Booking::getClassType() const { return classType; }
Seat Booking::getSeat() const { return seat; }
Passenger* Booking::getPassenger() const { return passenger; }
Flight* Booking::getFlight() const { return flight; }
void Booking::setFare(int f) { fare = f; }
void Booking::setBaggageFare(int bf) { baggageFare = bf; }
void Booking::setClassType(int ct) { classType = ct; }
void Booking::setBookingID(string bid) { bookingID = bid; }

// ========== RESERVATION SYSTEM ==========
class ReservationSystem {
    Flight** flights;
    Booking** bookings;
    int flightCount, bookingCount, totalRevenue, bookingIDCounter;
public:
    ReservationSystem();
    ~ReservationSystem();
    void     initializeFlights();
    int      getFlightCount()                          const;
    int      getBookingCount()                         const;
    int      getTotalRevenue()                         const;
    void     setTotalRevenue(int r);
    void     setBookingIDCounter(int c);
    int      getBookingIDCounter()                     const;
    Flight* getFlight(int i)                          const;
    Booking* getBooking(int i)                         const;
    int      getFlightCountByType(int flightType)      const;
    Flight* getFlightByIndex(int flightType, int idx) const;
    Flight* getFlightByNumber(const string& fNum)     const;
    int      getAvailableSeatsArr(Flight* f, int classType, int arr[]) const;
    int      createBooking(int flightType, int flightIdx, int classType,
        string nm, string addr, string nat, string cnic,
        int age, int bagWeight, int seatNo);
    int      loadBooking(string flightNum, int seatNo, int classType,
        string nm, string addr, string nat, string cnic,
        int age, int bagWeight, int fare, int baggageFare,
        string bookingID);
    void     applyGroupDiscount(int count, int& totalFare);
    Booking* findByCNIC(const string& cnic, int skip = 0) const;
    Booking* findByName(const string& nm)                  const;
    bool     cancelByCNIC(const string& cnic,
        int& origFare, int& charge, int& refund);

    // ── FILE HANDLING ──
    void saveToFile()   const;
    bool loadFromFile();
};

ReservationSystem::ReservationSystem()
    : flightCount(0), bookingCount(0), totalRevenue(0), bookingIDCounter(1000)
{
    flights = new Flight * [50];
    bookings = new Booking * [500];
    initializeFlights();
}

ReservationSystem::~ReservationSystem() {
    for (int i = 0; i < flightCount; i++) delete flights[i];
    for (int i = 0; i < bookingCount; i++) delete bookings[i];
    delete[] flights;
    delete[] bookings;
}

void ReservationSystem::initializeFlights() {
    flights[flightCount++] = new PIA("Islamabad", "Karachi", 1, "PK-300", "08:00 AM", "Monday");
    flights[flightCount++] = new SereneAir("Lahore", "Karachi", 1, "ER-501", "10:30 AM", "Monday");
    flights[flightCount++] = new AirBlue("Islamabad", "Lahore", 1, "PA-200", "02:00 PM", "Monday");
    flights[flightCount++] = new PIA("Karachi", "Peshawar", 1, "PK-350", "06:00 PM", "Tuesday");
    flights[flightCount++] = new AirSial("Multan", "Quetta", 1, "PF-100", "09:00 AM", "Tuesday");
    flights[flightCount++] = new PIA("Pakistan", "Saudi Arabia", 2, "PK-700", "11:00 PM", "Monday");
    flights[flightCount++] = new SereneAir("Pakistan", "UAE", 2, "ER-800", "01:00 AM", "Tuesday");
    flights[flightCount++] = new AirBlue("Pakistan", "Turkey", 2, "PA-900", "03:00 AM", "Wednesday");
    flights[flightCount++] = new PIA("Pakistan", "Qatar", 2, "PK-750", "05:00 PM", "Wednesday");
    flights[flightCount++] = new AirSial("Pakistan", "Malaysia", 2, "PF-600", "11:30 PM", "Thursday");
}

int ReservationSystem::getFlightCount() const { return flightCount; }
int ReservationSystem::getBookingCount() const { return bookingCount; }
int ReservationSystem::getTotalRevenue() const { return totalRevenue; }
void ReservationSystem::setTotalRevenue(int r) { totalRevenue = r; }
void ReservationSystem::setBookingIDCounter(int c) { bookingIDCounter = c; }
int ReservationSystem::getBookingIDCounter() const { return bookingIDCounter; }
Flight* ReservationSystem::getFlight(int i) const { return flights[i]; }
Booking* ReservationSystem::getBooking(int i) const { return bookings[i]; }

Flight* ReservationSystem::getFlightByNumber(const string& fNum) const {
    for (int i = 0; i < flightCount; i++)
        if (flights[i]->getFlightNumber() == fNum) return flights[i];
    return nullptr;
}

int ReservationSystem::getFlightCountByType(int ft) const {
    int c = 0;
    for (int i = 0; i < flightCount; i++)
        if (flights[i]->getType() == ft && flights[i]->getAvailableSeats() > 0) c++;
    return c;
}

Flight* ReservationSystem::getFlightByIndex(int ft, int idx) const {
    int c = 0;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i]->getType() == ft && flights[i]->getAvailableSeats() > 0) {
            if (c == idx) return flights[i];
            c++;
        }
    }
    return nullptr;
}

int ReservationSystem::getAvailableSeatsArr(Flight* f, int classType, int arr[]) const {
    int cnt = 0;
    for (int i = 0; i < 110; i++) {
        int sn = f->seats[i].getSeatNumber();
        if (f->seats[i].isAvailable()) {
            if ((classType == 1 && sn <= 25) || (classType == 2 && sn > 25))
                arr[cnt++] = sn;
        }
    }
    return cnt;
}

int ReservationSystem::createBooking(int flightType, int flightIdx, int classType,
    string nm, string addr, string nat, string cnic,
    int age, int bagWeight, int seatNo)
{
    Flight* f = getFlightByIndex(flightType, flightIdx);
    if (!f) return -1;
    if (seatNo < 1 || seatNo > 110) return -1;
    if (!f->seats[seatNo - 1].isAvailable()) return -1;

    Passenger* p;
    if (flightType == 1)
        p = new DomesticPassenger(nm, addr, nat, cnic, age, bagWeight);
    else
        p = new InternationalPassenger(nm, addr, nat, cnic, age, bagWeight);

    int baseFare = p->calculateFare(seatNo - 1, flightType);
    int fare = (int)(baseFare * f->getMultiplier());
    int freeBag = p->getFreeBaggage(classType);
    int baggageFare = (bagWeight > freeBag) ? (bagWeight - freeBag) * p->getBaggageCharge() : 0;

    f->seats[seatNo - 1].book();
    f->setAvailableSeats(f->getAvailableSeats() - 1);

    string bid = "FSP" + to_string(bookingIDCounter++);
    bookings[bookingCount++] = new Booking(f->seats[seatNo - 1], p, fare,
        baggageFare, f, classType, bid);
    totalRevenue += fare + baggageFare;
    return bookingCount - 1;
}

// Special load function used only by loadFromFile (skips fare recalculation)
int ReservationSystem::loadBooking(string flightNum, int seatNo, int classType,
    string nm, string addr, string nat, string cnic,
    int age, int bagWeight, int fare, int baggageFare, string bookingID)
{
    Flight* f = getFlightByNumber(flightNum);
    if (!f) return -1;
    if (seatNo < 1 || seatNo > 110) return -1;
    if (!f->seats[seatNo - 1].isAvailable()) return -1;

    Passenger* p;
    if (f->getType() == 1)
        p = new DomesticPassenger(nm, addr, nat, cnic, age, bagWeight);
    else
        p = new InternationalPassenger(nm, addr, nat, cnic, age, bagWeight);

    f->seats[seatNo - 1].book();
    f->setAvailableSeats(f->getAvailableSeats() - 1);

    bookings[bookingCount++] = new Booking(f->seats[seatNo - 1], p, fare,
        baggageFare, f, classType, bookingID);
    return bookingCount - 1;
}

void ReservationSystem::applyGroupDiscount(int count, int& totalFare) {
    if (count >= 5) {
        int discount = (int)(totalFare * 0.05);
        totalFare -= discount;
        totalRevenue -= discount;
    }
}

Booking* ReservationSystem::findByCNIC(const string& cnic, int skip) const {
    int found = 0;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i]->getPassengerCNIC() == cnic) {
            if (found == skip) return bookings[i];
            found++;
        }
    }
    return nullptr;
}

Booking* ReservationSystem::findByName(const string& nm) const {
    for (int i = 0; i < bookingCount; i++)
        if (bookings[i]->getPassengerName() == nm) return bookings[i];
    return nullptr;
}

bool ReservationSystem::cancelByCNIC(const string& cnic,
    int& origFare, int& charge, int& refund)
{
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i]->getPassengerCNIC() == cnic) {
            origFare = bookings[i]->getTotalFare();
            charge = (int)(origFare * 0.10);
            refund = origFare - charge;
            Flight* fl = bookings[i]->getFlight();
            fl->seats[bookings[i]->getSeatNumber() - 1].unbook();
            fl->setAvailableSeats(fl->getAvailableSeats() + 1);
            delete bookings[i];
            for (int j = i; j < bookingCount - 1; j++) bookings[j] = bookings[j + 1];
            bookingCount--;
            totalRevenue -= refund;
            return true;
        }
    }
    return false;
}

// =====================================================================
//  FILE HANDLING
//  3 files are used:
//    revenue.txt   — totalRevenue & bookingIDCounter
//    flights.txt   — seat booked/available status per flight
//    bookings.txt  — all booking records
// =====================================================================

void ReservationSystem::saveToFile() const {
    // 1. Revenue & Counter
    {
        ofstream rf("revenue.txt");
        if (rf.is_open()) {
            rf << totalRevenue << "\n";
            rf << bookingIDCounter << "\n";
            rf.close();
        }
    }
    // 2. Flight seat status
    {
        ofstream ff("flights.txt");
        if (ff.is_open()) {
            for (int i = 0; i < flightCount; i++) {
                ff << flights[i]->getFlightNumber() << "\n";
                ff << flights[i]->getAvailableSeats() << "\n";
                for (int s = 0; s < 110; s++)
                    ff << flights[i]->seats[s].getIsBooked() << " ";
                ff << "\n";
            }
            ff.close();
        }
    }
    // 3. Bookings
    {
        ofstream bf("bookings.txt");
        if (bf.is_open()) {
            bf << bookingCount << "\n";
            for (int i = 0; i < bookingCount; i++) {
                Booking* b = bookings[i];
                Passenger* p = b->getPassenger();
                bf << b->getBookingID() << "\n";
                bf << b->getFlightNumber() << "\n";
                bf << b->getSeatNumber() << "\n";
                bf << b->getClassType() << "\n";
                bf << p->getName() << "\n";
                bf << p->getAddress() << "\n";
                bf << p->getNationality() << "\n";
                bf << p->getCNIC() << "\n";
                bf << p->getAge() << "\n";
                bf << p->getBaggageWeight() << "\n";
                bf << b->getFare() << "\n";
                bf << b->getBaggageFare() << "\n";
            }
            bf.close();
        }
    }
}

bool ReservationSystem::loadFromFile() {
    // 1. Revenue & Counter
    {
        ifstream rf("revenue.txt");
        if (!rf.is_open()) return false;
        rf >> totalRevenue >> bookingIDCounter;
        rf.close();
    }
    // 2. Flight seat status
    {
        ifstream ff("flights.txt");
        if (ff.is_open()) {
            for (int i = 0; i < flightCount; i++) {
                string fNum;
                int    avail;
                ff >> fNum >> avail;
                Flight* f = getFlightByNumber(fNum);
                if (f) {
                    f->setAvailableSeats(avail);
                    for (int s = 0; s < 110; s++) {
                        int booked;
                        ff >> booked;
                        f->seats[s].setIsBooked(booked == 1);
                    }
                }
            }
            ff.close();
        }
    }
    // 3. Bookings
    {
        ifstream bf("bookings.txt");
        if (!bf.is_open()) return false;
        int count;
        bf >> count;
        bf.ignore();
        for (int i = 0; i < count; i++) {
            string bookingID, flightNum, nm, addr, nat, cnic;
            int    seatNo, classType, age, bagWeight, fare, baggageFare;
            getline(bf, bookingID);
            getline(bf, flightNum);
            bf >> seatNo >> classType;
            bf.ignore();
            getline(bf, nm);
            getline(bf, addr);
            getline(bf, nat);
            getline(bf, cnic);
            bf >> age >> bagWeight >> fare >> baggageFare;
            bf.ignore();
            loadBooking(flightNum, seatNo, classType,
                nm, addr, nat, cnic,
                age, bagWeight, fare, baggageFare, bookingID);
        }
        bf.close();
    }
    return true;
}

// =====================================================================
//  MAIN
// =====================================================================
int main() {
    ReservationSystem rs;

    cout << "\n+========================================+\n";
    cout << "|                                        |\n";
    cout << "|     FLY SKY PAKISTAN                   |\n";
    cout << "|     RESERVATION SYSTEM                 |\n";
    cout << "|                                        |\n";
    cout << "+========================================+\n";

    // Auto-load on startup
    if (rs.loadFromFile())
        cout << "\n[INFO] Previous data loaded successfully.\n";
    else
        cout << "\n[INFO] No saved data found. Starting fresh.\n";

    int choice;
    do {
        cout << "\n+====================================+\n";
        cout << "|         MAIN MENU                  |\n";
        cout << "+====================================+\n";
        cout << "|  1. Book Flight                    |\n";
        cout << "|  2. Check Reservation              |\n";
        cout << "|  3. Cancel Booking                 |\n";
        cout << "|  4. View All Bookings              |\n";
        cout << "|  5. Save Data to File              |\n";
        cout << "|  6. Load Data from File            |\n";
        cout << "|  7. Exit                           |\n";
        cout << "+====================================+\n";
        cout << "Enter your choice: ";
        choice = safeIntInput();

        // ── 1. BOOK FLIGHT ────────────────────────────────────────────
        if (choice == 1) {
            cout << "\n+-----------------------------------+\n";
            cout << "|     CHOOSE FLIGHT TYPE            |\n";
            cout << "+-----------------------------------+\n";
            cout << "|  1. Domestic                      |\n";
            cout << "|  2. International                 |\n";
            cout << "+-----------------------------------+\n";
            cout << "Enter your choice: ";
            int flightType = safeIntInput();
            if (flightType != 1 && flightType != 2) { cout << "Invalid choice!\n"; continue; }

            cout << "\n+================================================================+\n";
            cout << "|  AVAILABLE " << (flightType == 1 ? "DOMESTIC    " : "INTERNATIONAL")
                << " FLIGHTS                              |\n";
            cout << "+================================================================+\n\n";
            int dispCount = 1;
            for (int i = 0; i < rs.getFlightCount(); i++) {
                Flight* f = rs.getFlight(i);
                if (f->getType() == flightType && f->getAvailableSeats() > 0) {
                    cout << dispCount++ << ". ";
                    cout << "+------------------------------------------------+\n";
                    cout << "|  Flight: " << setw(38) << left << f->getFlightNumber() << "|\n";
                    cout << "|  Airline: " << setw(37) << left << f->getName() << "|\n";
                    cout << "|  Route: " << setw(39) << left
                        << (f->getOrigin() + " -> " + f->getDestination()) << "|\n";
                    cout << "|  Departure: " << setw(34) << left
                        << (f->getDepartureDay() + " " + f->getDepartureTime()) << "|\n";
                    cout << "|  Available: " << setw(34) << left << f->getAvailableSeats() << "|\n";
                    cout << "|  Type: " << setw(40) << left
                        << (f->getType() == 1 ? "Domestic" : "International") << "|\n";
                    cout << "+------------------------------------------------+\n\n";
                }
            }
            if (dispCount == 1) { cout << "No flights available.\n"; continue; }

            cout << "Enter flight number (0 = back): ";
            int flightChoice = safeIntInput();
            if (flightChoice == 0) continue;
            if (flightChoice < 1 || flightChoice > rs.getFlightCountByType(flightType)) {
                cout << "Invalid choice!\n"; continue;
            }

            cout << "How many persons? (1-10): ";
            int numPersons = safeIntInput();
            if (numPersons < 1 || numPersons > 10) { cout << "Invalid number!\n"; continue; }

            Flight* sel = rs.getFlightByIndex(flightType, flightChoice - 1);
            if (sel->getAvailableSeats() < numPersons) {
                cout << "Only " << sel->getAvailableSeats() << " seats available.\n"; continue;
            }

            cout << "\n+-----------------------------------+\n";
            cout << "|       SELECT CLASS                |\n";
            cout << "+-----------------------------------+\n";
            cout << "|  1. Business Class (Seats 1-25)   |\n";
            cout << "|  2. Economy Class  (Seats 26-110) |\n";
            cout << "+-----------------------------------+\n";
            cout << "Enter your choice: ";
            int classType = safeIntInput();

            int  startIdx = rs.getBookingCount();
            int  groupFare = 0;
            bool allOk = true;

            for (int person = 0; person < numPersons && allOk; person++) {
                cout << "\n+----------------------------------------+\n";
                cout << "|  PERSON #" << (person + 1) << " of " << numPersons
                    << "                             |\n";
                cout << "+----------------------------------------+\n";

                int seatArr[110];
                int seatCnt = rs.getAvailableSeatsArr(sel, classType, seatArr);
                cout << "Available Seats: ";
                for (int k = 0; k < seatCnt; k++) {
                    cout << seatArr[k];
                    if (seatArr[k] % 6 == 0) cout << "(W)";
                    cout << " ";
                }
                cout << "\nSelect seat number: ";
                int seatNo = safeIntInput();

                cin.ignore();
                string nm, addr, nat, cnic;
                int    age, bagWeight;
                cout << "Enter Name: ";         getline(cin, nm);
                cout << "Enter Address: ";      getline(cin, addr);
                cout << "Enter Nationality: ";  getline(cin, nat);
                cout << "Enter CNIC: ";         getline(cin, cnic);
                cout << "Enter Age: ";          age = safeIntInput();
                cout << "Enter Baggage (kg): "; bagWeight = safeIntInput();

                int idx = rs.createBooking(flightType, flightChoice - 1, classType,
                    nm, addr, nat, cnic, age, bagWeight, seatNo);
                if (idx < 0) {
                    cout << "Invalid seat! Booking aborted.\n";
                    allOk = false;
                    break;
                }
                groupFare += rs.getBooking(idx)->getTotalFare();
                cout << "Seat " << seatNo << " booked for " << nm << "!\n";
            }

            if (!allOk) continue;

            rs.applyGroupDiscount(numPersons, groupFare);

            cout << "\n+----------------------------------------+\n";
            cout << "|       BOOKING SUMMARY                  |\n";
            cout << "+----------------------------------------+\n";
            cout << "|  Total Persons: " << setw(23) << left << numPersons << "|\n";
            if (numPersons >= 5) cout << "|  Group Discount (5%) applied           |\n";
            cout << "|  FINAL AMOUNT:  Rs. " << groupFare << "\n";
            cout << "+----------------------------------------+\n";

            cout << "\n+----------------------------------------+\n";
            cout << "|     PRINTING E-TICKETS                 |\n";
            cout << "+----------------------------------------+\n";
            for (int i = startIdx; i < rs.getBookingCount(); i++) {
                Booking* b = rs.getBooking(i);
                Passenger* p = b->getPassenger();
                Flight* fl = b->getFlight();
                Seat       s = b->getSeat();
                int        ct = b->getClassType();
                int freeBag = p->getFreeBaggage(ct);

                cout << "\n+------------------------------------------------+\n";
                cout << "|        E-TICKET - FLY SKY PAKISTAN             |\n";
                cout << "+------------------------------------------------+\n";
                cout << "|  Booking ID:  " << setw(33) << left << b->getBookingID() << "|\n";
                cout << "+------------------------------------------------+\n";
                cout << "|  PASSENGER DETAILS                             |\n";
                cout << "|  Name: " << setw(40) << left << p->getName() << "|\n";
                cout << "|  CNIC: " << setw(40) << left << p->getCNIC() << "|\n";
                cout << "|  Age: " << setw(41) << left
                    << (to_string(p->getAge()) + " years") << "|\n";
                cout << "|  Nationality: " << setw(33) << left << p->getNationality() << "|\n";
                cout << "+------------------------------------------------+\n";
                cout << "|  FLIGHT DETAILS                                |\n";
                cout << "|  Flight: " << setw(38) << left << fl->getFlightNumber() << "|\n";
                cout << "|  Airline: " << setw(37) << left << fl->getName() << "|\n";
                cout << "|  Route: " << setw(39) << left
                    << (fl->getOrigin() + " -> " + fl->getDestination()) << "|\n";
                cout << "|  Departure: " << setw(34) << left
                    << (fl->getDepartureDay() + " " + fl->getDepartureTime()) << "|\n";
                cout << "|  Type: " << setw(40) << left
                    << (fl->getType() == 1 ? "Domestic" : "International") << "|\n";
                cout << "+------------------------------------------------+\n";
                cout << "|  SEAT DETAILS                                  |\n";
                cout << "|  Seat: " << setw(40) << left << s.getSeatNumber() << "|\n";
                cout << "|  Class: " << setw(39) << left
                    << (ct == 1 ? "Business Class" : "Economy Class") << "|\n";
                if (s.getSeatNumber() % 6 == 0)
                    cout << "|  Position: Window Seat                         |\n";
                cout << "+------------------------------------------------+\n";
                cout << "|  BAGGAGE DETAILS                               |\n";
                cout << "|  Weight: " << setw(38) << left
                    << (to_string(p->getBaggageWeight()) + " kg") << "|\n";
                cout << "|  Free Allowance: " << setw(30) << left
                    << (to_string(freeBag) + " kg") << "|\n";
                if (p->getBaggageWeight() > freeBag) {
                    int extra = p->getBaggageWeight() - freeBag;
                    cout << "|  Excess: " << setw(38) << left
                        << (to_string(extra) + " kg") << "|\n";
                }
                cout << "+------------------------------------------------+\n";
                cout << "|  FARE BREAKDOWN                                |\n";
                cout << "|  Base Fare: " << setw(25) << right
                    << ("Rs. " + to_string(b->getFare())) << "      |\n";
                if (b->getBaggageFare() > 0)
                    cout << "|  Baggage:   " << setw(25) << right
                    << ("Rs. " + to_string(b->getBaggageFare())) << "      |\n";
                cout << "|  " << string(44, '-') << " |\n";
                cout << "|  TOTAL:     " << setw(25) << right
                    << ("Rs. " + to_string(b->getTotalFare())) << "      |\n";
                cout << "+------------------------------------------------+\n";
                cout << "Have a pleasant journey with " << fl->getName() << "!\n";
            }

            // Auto-save after booking
            rs.saveToFile();
            cout << "\n[INFO] Data auto-saved to files.\n";
            cout << "\nALL BOOKINGS COMPLETED SUCCESSFULLY!\n";
        }

        // ── 2. CHECK RESERVATION ──────────────────────────────────────
        else if (choice == 2) {
            if (rs.getBookingCount() == 0) { cout << "No reservations found.\n"; continue; }

            cout << "\n+-----------------------------------+\n";
            cout << "|    CHECK RESERVATION              |\n";
            cout << "+-----------------------------------+\n";
            cout << "|  1. Search by CNIC                |\n";
            cout << "|  2. Search by Name                |\n";
            cout << "+-----------------------------------+\n";
            cout << "Enter your choice: ";
            int sc = safeIntInput();
            cin.ignore();
            string term;
            bool found = false;

            if (sc == 1) {
                cout << "Enter CNIC: "; getline(cin, term);
                for (int skip = 0; ; skip++) {
                    Booking* b = rs.findByCNIC(term, skip);
                    if (!b) break;
                    found = true;
                    Flight* fl = b->getFlight();
                    cout << "\n+------------------------------------------------+\n";
                    cout << "|           BOOKING DETAILS                      |\n";
                    cout << "+------------------------------------------------+\n";
                    cout << "|  Booking ID: " << setw(34) << left << b->getBookingID() << "|\n";
                    cout << "|  Passenger:  " << setw(34) << left << b->getPassengerName() << "|\n";
                    cout << "|  CNIC:       " << setw(34) << left << b->getPassengerCNIC() << "|\n";
                    cout << "|  Flight:     " << setw(34) << left << fl->getFlightNumber() << "|\n";
                    cout << "|  Route:      " << setw(34) << left
                        << (fl->getOrigin() + " -> " + fl->getDestination()) << "|\n";
                    cout << "|  Seat:       " << setw(34) << left << b->getSeatNumber() << "|\n";
                    cout << "|  Total Fare: " << setw(34) << left
                        << ("Rs. " + to_string(b->getTotalFare())) << "|\n";
                    cout << "+------------------------------------------------+\n";
                    cout << "Print ticket? (1=Yes, 0=No): ";
                    if (safeIntInput() == 1) {
                        Passenger* p = b->getPassenger();
                        Seat       s = b->getSeat();
                        int        ct = b->getClassType();
                        int freeBag = p->getFreeBaggage(ct);
                        cout << "\n+------------------------------------------------+\n";
                        cout << "|        E-TICKET - FLY SKY PAKISTAN             |\n";
                        cout << "+------------------------------------------------+\n";
                        cout << "|  Booking ID:  " << setw(33) << left << b->getBookingID() << "|\n";
                        cout << "|  Name: " << setw(40) << left << p->getName() << "|\n";
                        cout << "|  CNIC: " << setw(40) << left << p->getCNIC() << "|\n";
                        cout << "|  Flight: " << setw(38) << left << fl->getFlightNumber() << "|\n";
                        cout << "|  Route: " << setw(39) << left
                            << (fl->getOrigin() + " -> " + fl->getDestination()) << "|\n";
                        cout << "|  Departure: " << setw(34) << left
                            << (fl->getDepartureDay() + " " + fl->getDepartureTime()) << "|\n";
                        cout << "|  Seat: " << setw(40) << left << s.getSeatNumber() << "|\n";
                        cout << "|  Class: " << setw(39) << left
                            << (ct == 1 ? "Business Class" : "Economy Class") << "|\n";
                        cout << "|  Baggage: " << setw(37) << left
                            << (to_string(p->getBaggageWeight()) + " kg (Free: "
                                + to_string(freeBag) + " kg)") << "|\n";
                        cout << "|  Total Fare: " << setw(34) << left
                            << ("Rs. " + to_string(b->getTotalFare())) << "|\n";
                        cout << "+------------------------------------------------+\n";
                    }
                }
            }
            else if (sc == 2) {
                cout << "Enter Name: "; getline(cin, term);
                Booking* b = rs.findByName(term);
                if (b) {
                    found = true;
                    Flight* fl = b->getFlight();
                    cout << "\n+------------------------------------------------+\n";
                    cout << "|           BOOKING DETAILS                      |\n";
                    cout << "+------------------------------------------------+\n";
                    cout << "|  Booking ID: " << setw(34) << left << b->getBookingID() << "|\n";
                    cout << "|  Passenger:  " << setw(34) << left << b->getPassengerName() << "|\n";
                    cout << "|  CNIC:       " << setw(34) << left << b->getPassengerCNIC() << "|\n";
                    cout << "|  Flight:     " << setw(34) << left << fl->getFlightNumber() << "|\n";
                    cout << "|  Route:      " << setw(34) << left
                        << (fl->getOrigin() + " -> " + fl->getDestination()) << "|\n";
                    cout << "|  Seat:       " << setw(34) << left << b->getSeatNumber() << "|\n";
                    cout << "|  Total Fare: " << setw(34) << left
                        << ("Rs. " + to_string(b->getTotalFare())) << "|\n";
                    cout << "+------------------------------------------------+\n";
                }
            }
            if (!found) cout << "No reservation found.\n";
        }

        // ── 3. CANCEL BOOKING ─────────────────────────────────────────
        else if (choice == 3) {
            if (rs.getBookingCount() == 0) { cout << "No bookings to cancel.\n"; continue; }
            cin.ignore();
            string cnic;
            cout << "Enter CNIC: "; getline(cin, cnic);
            Booking* b = rs.findByCNIC(cnic);
            if (!b) { cout << "No booking found.\n"; continue; }

            Flight* fl = b->getFlight();
            cout << "\n+------------------------------------------------+\n";
            cout << "|           BOOKING DETAILS                      |\n";
            cout << "+------------------------------------------------+\n";
            cout << "|  Booking ID: " << setw(34) << left << b->getBookingID() << "|\n";
            cout << "|  Passenger:  " << setw(34) << left << b->getPassengerName() << "|\n";
            cout << "|  Flight:     " << setw(34) << left << fl->getFlightNumber() << "|\n";
            cout << "|  Seat:       " << setw(34) << left << b->getSeatNumber() << "|\n";
            cout << "|  Total Fare: " << setw(34) << left
                << ("Rs. " + to_string(b->getTotalFare())) << "|\n";
            cout << "+------------------------------------------------+\n";
            cout << "Are you sure? (1=Yes, 0=No): ";
            if (safeIntInput() != 1) { cout << "Cancellation aborted.\n"; continue; }

            int origFare, charge, refund;
            if (rs.cancelByCNIC(cnic, origFare, charge, refund)) {
                cout << "\n+----------------------------------------+\n";
                cout << "|    CANCELLATION DETAILS                |\n";
                cout << "+----------------------------------------+\n";
                cout << "|  Original Fare:      Rs. " << origFare << "\n";
                cout << "|  Cancellation (10%): Rs. " << charge << "\n";
                cout << "|  REFUND AMOUNT:      Rs. " << refund << "\n";
                cout << "+----------------------------------------+\n";
                cout << "Booking cancelled successfully!\n";
                // Auto-save after cancellation
                rs.saveToFile();
                cout << "[INFO] Data auto-saved to files.\n";
            }
        }

        // ── 4. VIEW ALL BOOKINGS ──────────────────────────────────────
        else if (choice == 4) {
            if (rs.getBookingCount() == 0) { cout << "No bookings available.\n"; continue; }
            cout << "\n+============================================================+\n";
            cout << "|                    ALL BOOKINGS                            |\n";
            cout << "+============================================================+\n";
            for (int i = 0; i < rs.getBookingCount(); i++) {
                Booking* b = rs.getBooking(i);
                Flight* fl = b->getFlight();
                cout << "\n" << (i + 1) << ".\n";
                cout << "+------------------------------------------------+\n";
                cout << "|  Booking ID: " << setw(34) << left << b->getBookingID() << "|\n";
                cout << "|  Passenger:  " << setw(34) << left << b->getPassengerName() << "|\n";
                cout << "|  CNIC:       " << setw(34) << left << b->getPassengerCNIC() << "|\n";
                cout << "|  Flight:     " << setw(34) << left << fl->getFlightNumber() << "|\n";
                cout << "|  Route:      " << setw(34) << left
                    << (fl->getOrigin() + " -> " + fl->getDestination()) << "|\n";
                cout << "|  Seat:       " << setw(34) << left << b->getSeatNumber() << "|\n";
                cout << "|  Total Fare: " << setw(34) << left
                    << ("Rs. " + to_string(b->getTotalFare())) << "|\n";
                cout << "+------------------------------------------------+\n";
            }
            cout << "\n  Total Revenue: Rs. " << rs.getTotalRevenue() << "\n";
        }

        // ── 5. MANUAL SAVE ────────────────────────────────────────────
        else if (choice == 5) {
            rs.saveToFile();
            cout << "\n+----------------------------------------+\n";
            cout << "|  Data saved successfully!              |\n";
            cout << "|  Files created:                        |\n";
            cout << "|    bookings.txt  (all bookings)        |\n";
            cout << "|    flights.txt   (seat status)         |\n";
            cout << "|    revenue.txt   (revenue & counter)   |\n";
            cout << "+----------------------------------------+\n";
        }

        // ── 6. MANUAL LOAD ────────────────────────────────────────────
        else if (choice == 6) {
            if (rs.loadFromFile())
                cout << "\n[INFO] Data loaded successfully from files.\n";
            else
                cout << "\n[ERROR] Could not load data. Files may not exist.\n";
        }

        // ── 7. EXIT ───────────────────────────────────────────────────
        else if (choice == 7) {
            // Auto-save on exit
            rs.saveToFile();
            cout << "\n[INFO] Data auto-saved on exit.\n";
            cout << "\nThank you for using Fly Sky Pakistan!\n";
            cout << "Have a safe flight!\n\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}