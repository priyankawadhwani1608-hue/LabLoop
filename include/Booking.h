#pragma once

#include <string>
using namespace std;

enum class BookingStatus {
    CONFIRMED,
    CANCELLED,
    COMPLETED
};

class Booking {
private:
    int bookingId;
    int studentId;
    int equipmentId;

    int date;       // Format: YYYYMMDD
    int startTime;  // Minutes from midnight
    int endTime;

    BookingStatus status;

public:
    Booking(int bid, int sid, int eid,
            int d, int start, int end);

    int getBookingId() const;
    int getStudentId() const;
    int getEquipmentId() const;
    int getDate() const;
    int getStartTime() const;
    int getEndTime() const;

    void setStatus(BookingStatus newStatus);
    BookingStatus getStatus() const;

    bool overlapsWith(const Booking& other) const;

    void cancelBooking();
    void completeBooking();

    void displayBooking() const;

    // Sort bookings chronologically
    bool operator<(const Booking& other) const;
};
