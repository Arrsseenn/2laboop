#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace laboop {

    public ref class Person {
    public:
        String^ Name;
        String^ SurName;

        Person(String^ name, String^ surName);
    };

    public ref class HotelSystem {
    private:
        System::Windows::Forms::Label^ label;
        System::Windows::Forms::Button^ button1;
        System::Windows::Forms::Button^ button2;

        //поля
        bool isUserTurn;

    public:
        HotelSystem(
            Windows::Forms::Label^ Label, Windows::Forms::Button^ Button1,
            Windows::Forms::Button^ Button2);

        void ShowUserMenu();
        void ShowAdminMenu();

        void ShowRoomMenu(HotelSystem^ system);

        void showBookingForm();
        void showBooking(HotelSystem^ system);

        //getters
        bool getIsUserTurn() { return isUserTurn; }
    };



    public ref class Room {
    public:
        int roomCapacity;
        int roomNumber;
        String^ roomType;

        Room(int roomNum, int roomCapacity, String^ roomType);
    };



    public ref class Booking {
    private:
        double payment;

        String^ bookingDate;
        int clientID;
        int bookingID;
    public:
        bool isBookingApproved;
        int hours;
        Room^ room;

        Booking(Room^ room, int bookingID, int clientID, String^ bookingDate, int hours);

        void calculatePayment();
        String^ GetBookingDate() { return bookingDate; }
        double GetPayment() { return payment; }
        int GetClientID() { return clientID; }
        int GetBookingID() { return bookingID; }
    };



    public ref class Client : public Person {
        List<Booking^>^ bookings;
        String^ phoneNumber;
        String^ email;
    public:

        Client(String^ name, String^ surName, String^ phoneNumber, String^ email);

        void CreateBooking(Room^ room, int bookingID, int clientID, String^ bookingDate, int hours);
        bool Equalse(Client^ other);

        List<Booking^>^ GetBookings() { return bookings; }
        String^ GetPhonNum() { return phoneNumber; }
        String^ GetEmail() { return email; }
    };




    public ref class Design {
    private:
        System::Windows::Forms::Button^ button1;
        System::Windows::Forms::TextBox^ textBox1;
        System::Windows::Forms::TextBox^ textBox2;
        System::Windows::Forms::TextBox^ textBox3;
        //Для перевантаженого конструктора
        System::Windows::Forms::ListBox^ listBox1;

    public:

        Design(
            Windows::Forms::Button^ button1, Windows::Forms::TextBox^ textBox1,
            Windows::Forms::TextBox^ textBox2, Windows::Forms::TextBox^ textBox3);
        Design(Windows::Forms::ListBox^ listBox1);

        void LoadViewForm(HotelSystem^ system);

        void SaveToFile(Client^ client, String^ fileName);
        void readFromFile(String^ fileName);

        void SaveToFile(Room^ room, String^ fileName);
        void readFromFileRoom(String^ fileName);

        int Generate();
    };
}