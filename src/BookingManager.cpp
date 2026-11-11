#include "../include/BookingManager.h"
#include <iostream>
#include <algorithm>
#include <ctime>

BookingManager::BookingManager() {
    nextBookingId = 1001;
}

bool BookingManager::isValidDate(int date) const {

    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    if (year < 1 || year > 9999 || month < 1 || month > 12) {
        return false;
    }

    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool leapYear = (year % 400 == 0) ||
                    (year % 4 == 0 && year % 100 != 0);

    if (leapYear) {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

    time_t now = time(nullptr);
    tm* currentTime = localtime(&now);

    if (currentTime == nullptr) {
        return false;
    }

    int today = (currentTime->tm_year + 1900) * 10000 +
                (currentTime->tm_mon + 1) * 100 +
                currentTime->tm_mday;

    return date >= today;
}

bool BookingManager::isValidTime(int start, int end) const {
    return start >= 0 && end <= 1440 && start < end;
}

bool BookingManager::hasConflict(const Booking& requested) const {

    for (const Booking& existing : bookings) {
        if (requested.overlapsWith(existing)) {
            return true;
        }
    }

    return false;
}

const vector<Booking>& BookingManager::getBookings() const {
    return bookings;
}

void BookingManager::loadBookings(
    const vector<Booking>& savedBookings, int nextId) {

    bookings = savedBookings;
    nextBookingId = nextId;
}

bool BookingManager::createBooking(
    int studentId,
    const Equipment& equipment,
    int date,
    int startTime) {

    return createBooking(
        studentId,
        equipment,
        date,
        startTime,
        startTime + 60
    );
}

bool BookingManager::createBooking(
    int studentId,
    const Equipment& equipment,
    int date,
    int startTime,
    int endTime) {

    if (date <= 0 || studentId <= 0) {
        cout << "\nInvalid booking details.\n";
        return false;
    }

    if (!isValidDate(date)) {
        cout << "\nInvalid date.\n";
        return false;
    }

    if (!isValidTime(startTime, endTime)) {
        cout << "\nInvalid time slot.\n";
        return false;
    }

    if (equipment.getStatus() != EquipmentStatus::AVAILABLE) {
        cout << "\nEquipment is not available for booking.\n";
        return false;
    }

    Booking requested(
        nextBookingId,
        studentId,
        equipment.getEquipmentId(),
        date,
        startTime,
        endTime
    );

    if (hasConflict(requested)) {
        cout << "\nBooking failed: Time slot already occupied.\n";
        return false;
    }

    bookings.push_back(requested);

    cout << "\nBooking successful!";
    cout << "\nYour Booking ID: " << nextBookingId << "\n";

    nextBookingId++;

    return true;
}

// Ownership-verified cancellation
bool BookingManager::cancelBooking(int bookingId, int studentId) {

    for (auto& booking : bookings) {

        if (booking.getBookingId() == bookingId) {

            if (booking.getStudentId() != studentId) {
                cout << "Access denied! This booking belongs to another student.\n";
                return false;
            }

            if (booking.getStatus() != BookingStatus::CONFIRMED) {
                cout << "This booking is already cancelled or completed.\n";
                return false;
            }

            booking.cancelBooking();

            cout << "Booking cancelled successfully!\n";
            return true;
        }
    }

    cout << "Booking ID not found!\n";
    return false;
}

void BookingManager::displayAllBookings() const {

    if (bookings.empty()) {
        cout << "\nNo bookings found.\n";
        return;
    }

    vector<Booking> sortedBookings = bookings;
    sort(sortedBookings.begin(), sortedBookings.end());

    cout << "\n========== ALL BOOKINGS ==========\n";

    for (const Booking& booking : sortedBookings) {
        booking.displayBooking();
        cout << "----------------------------------\n";
    }
}

void BookingManager::displayStudentBookings(int studentId) const {

    vector<Booking> studentBookings;

    for (const Booking& booking : bookings) {
        if (booking.getStudentId() == studentId) {
            studentBookings.push_back(booking);
        }
    }

    if (studentBookings.empty()) {
        cout << "\nNo bookings found for this student.\n";
        return;
    }

    sort(studentBookings.begin(), studentBookings.end());

    cout << "\n========== MY BOOKINGS ==========\n";

    for (const Booking& booking : studentBookings) {
        booking.displayBooking();
        cout << "----------------------------------\n";
    }
}
