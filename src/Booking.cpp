#include "../include/Booking.h"
#include <iostream>
#include <stdexcept>

Booking::Booking(int bid, int sid, int eid, int d, int start, int end) {

    if (bid <= 0 || sid <= 0 || eid <= 0 ||
        start < 0 || end > 1440 || start >= end) {
        throw invalid_argument("Invalid booking details!");
    }

    bookingId = bid;
    studentId = sid;
    equipmentId = eid;
    date = d;
    startTime = start;
    endTime = end;

    status = BookingStatus::CONFIRMED;
}

int Booking::getBookingId() const {
    return bookingId;
}

int Booking::getStudentId() const {
    return studentId;
}

int Booking::getEquipmentId() const {
    return equipmentId;
}

int Booking::getDate() const {
    return date;
}

int Booking::getStartTime() const {
    return startTime;
}

int Booking::getEndTime() const {
    return endTime;
}

BookingStatus Booking::getStatus() const {
    return status;
}

bool Booking::overlapsWith(const Booking& other) const {

    if (equipmentId != other.equipmentId ||
        date != other.date) {
        return false;
    }

    if (status != BookingStatus::CONFIRMED ||
        other.status != BookingStatus::CONFIRMED) {
        return false;
    }

    return (startTime < other.endTime &&
            other.startTime < endTime);
}

void Booking::cancelBooking() {
    if (status == BookingStatus::CONFIRMED) {
        status = BookingStatus::CANCELLED;
    }
}

void Booking::completeBooking() {
    if (status == BookingStatus::CONFIRMED) {
        status = BookingStatus::COMPLETED;
    }
}

bool Booking::operator<(const Booking& other) const {

    if (date != other.date) {
        return date < other.date;
    }

    return startTime < other.startTime;
}

void Booking::setStatus(BookingStatus newStatus) {
    status = newStatus;
}

void Booking::displayBooking() const {

    cout << "\nBooking ID: " << bookingId;
    cout << "\nStudent ID: " << studentId;
    cout << "\nEquipment ID: " << equipmentId;
    cout << "\nDate: " << date;
    cout << "\nStart Time: " << startTime / 60
         << ":" << (startTime % 60 < 10 ? "0" : "")
         << startTime % 60;

    cout << "\nEnd Time: " << endTime / 60
         << ":" << (endTime % 60 < 10 ? "0" : "")
         << endTime % 60;

    cout << "\nStatus: ";

    switch (status) {
        case BookingStatus::CONFIRMED:
            cout << "Confirmed";
            break;

        case BookingStatus::CANCELLED:
            cout << "Cancelled";
            break;

        case BookingStatus::COMPLETED:
            cout << "Completed";
            break;
    }

    cout << "\n";
}
