#pragma once

#include "Booking.h"
#include "Equipment.h"
#include <vector>

class BookingManager {
private:
    vector<Booking> bookings;
    int nextBookingId;

    bool isValidDate(int date) const;
    bool isValidTime(int start, int end) const;
    bool hasConflict(const Booking& requested) const;

public:
    BookingManager();

    // Overload 1: Default 1-hour booking
    bool createBooking(int studentId, const Equipment& equipment, int date, int startTime);

    // Overload 2: Custom-duration booking
    bool createBooking(int studentId, const Equipment& equipment, int date, int startTime, int endTime);
    const vector<Booking>& getBookings() const;

    void loadBookings(const vector<Booking>& savedBookings, int nextId);

    bool cancelBooking(int bookingId, int studentId);
    void displayAllBookings() const;

    void displayStudentBookings(int studentId) const;
};
