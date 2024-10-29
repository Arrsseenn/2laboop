#include "HotelSystem.h"
#include "MyForm.h"
#include "MyForm1.h"
#include "MyForm2.h"
#include "viewBookings.h"

namespace laboop {

	Person::Person(String^ name, String^ surName) :Name(name), SurName(surName) {}

	//Реалізація класу HotelSystem
	HotelSystem::HotelSystem(Windows::Forms::Label^ Label, Windows::Forms::Button^ Button1,
		Windows::Forms::Button^ Button2) {
		this->label = Label;
		this->button1 = Button1;
		this->button2 = Button2;
	}


	void HotelSystem::ShowUserMenu() {
		label->Text = "Меню користувача";
		button1->Text = "Створити заявку";
		button2->Text = "Переглянути наділсані заявки";
		isUserTurn = true;
	}
	void HotelSystem::ShowAdminMenu() {
		label->Text = "Меню Адміністратора";
		button1->Text = "Додати кімнату";
		button2->Text = "Переглянути надіслані заявки";
		isUserTurn = false;
	}

	void HotelSystem::ShowRoomMenu(HotelSystem^ system) {
		viewBookings^ form = gcnew viewBookings(system);
		form->Show();
	}

	void HotelSystem::showBookingForm() {
		MyForm1^ adminForm = gcnew MyForm1;
		MyForm2^ userForm = gcnew MyForm2;
		if (!isUserTurn) {
			adminForm->Show();
		}
		else {
			userForm->Show();
		}
	}
	void HotelSystem::showBooking(HotelSystem^ system) {
		viewBookings^ ViewBookings = gcnew viewBookings(system);
		ViewBookings->Show();

	}




	//Реалізація класу Room
	Room::Room(int roomNum, int roomCapacity, String^ roomType) :
		roomNumber(roomNum), roomCapacity(roomCapacity), roomType(roomType) {}





	//Реалізація класу Booking
	Booking::Booking(Room^ room, int bookingID, int clientID, String^ bookingDate, int hours) :
		room(room), bookingDate(bookingDate), clientID(clientID), bookingID(bookingID), hours(hours) {}

	void Booking::calculatePayment() {
		int roomCost = 0;

		if (room->roomType == "Standart") {
			roomCost = 100;
		}
		else if (room->roomType == "Bedroom") {
			roomCost = 200;
		}
		else if (room->roomType == "Superior") {
			roomCost = 300;
		}
		else if (room->roomType == "Corner room") {
			roomCost = 400;
		}
		else {
			MessageBox::Show("Невідомий тип номеру");
			return;
		}

		payment = roomCost * hours * room->roomCapacity;
	}




	//Реалізація класу Client
	Client::Client(String^ name, String^ surName, String^ phoneNumber, String^ email)
		:Person(name, surName), phoneNumber(phoneNumber), email(email) {}

	void Client::CreateBooking(Room^ room, int bookingID, int clientID, String^ bookingDate, int hours) {
		Booking(room, bookingID, clientID, bookingDate, hours);
	}

	bool Client::Equalse(Client^ other) {
		if (this->Name == other->Name ||
			this->SurName == other->SurName ||
			this->phoneNumber == other->phoneNumber) {
			return true;
		}
		return false;
	}




	//Реалізація класу Design
	Design::Design(
		Windows::Forms::Button^ button1, Windows::Forms::TextBox^ textBox1,
		Windows::Forms::TextBox^ textBox2, Windows::Forms::TextBox^ textBox3){
		this->button1 = button1;
		this->textBox1 = textBox1;
		this->textBox1 = textBox2;
		this->textBox1 = textBox3;
	}
	Design::Design(Windows::Forms::ListBox^ listBox1):listBox1(listBox1) {}
	
	void Design::LoadViewForm(HotelSystem^ system) {
		if (system != nullptr && system->getIsUserTurn()) {
			listBox1->Items->Add("Для вибору додаткових послуг натисніть двічі на бронюання");
			listBox1->Items->Add("");
			readFromFile("Booking.dat");
		}
		else {
			listBox1->Items->Add("Для вибору кімнати натисніть двічі");
			listBox1->Items->Add("");
			readFromFileRoom("Room.dat");
		}
	}

	void Design::SaveToFile(Client^ client, String^ fileName) {
		FileStream^ fileAppend = nullptr; 
		try {
			fileAppend = gcnew FileStream(fileName, FileMode::Append, FileAccess::Write);
			BinaryWriter^ writer = gcnew BinaryWriter(fileAppend);

			writer->Write(client->Name);
			writer->Write(client->SurName);
			writer->Write(client->GetPhonNum());
			writer->Write(client->GetEmail());

			writer->Close();
			MessageBox::Show("Дані успішно записані у файл: " + fileName);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Помилка при записі файлу: " + ex->Message);
		}
		finally {
			if (fileAppend != nullptr) fileAppend->Close();
		}
	}
	void Design::readFromFile(String^ fileName) {

		FileStream^ file = gcnew FileStream(fileName, FileMode::Open, FileAccess::Read);
		BinaryReader^ reader = gcnew BinaryReader(file);

		while (reader->BaseStream->Position < reader->BaseStream->Length) {
			String^ existingName = reader->ReadString();
			String^ existingSurName = reader->ReadString();
			String^ existingPhoneNum = reader->ReadString();
			String^ existingEmail = reader->ReadString();


			listBox1->Items->Add("Ім'я: " + existingName +
				"  Прізвище: " + existingSurName +
				" Номер телефону: " + existingPhoneNum +
			    " Email: " + existingEmail);
		
		}
		reader->Close();
		file->Close();
	}

	void Design::SaveToFile(Room^ room, String^ fileName) {
		FileStream^ file = gcnew FileStream(fileName, FileMode::Append, FileAccess::Write);
		BinaryWriter^ writer = gcnew BinaryWriter(file);

		writer->Write(room->roomCapacity + " " + room->roomNumber + " " + room->roomType);


		writer->Close();
		MessageBox::Show("Дані успішно записані у файл: " + fileName);
		file->Close();
	}
	void Design::readFromFileRoom(String^ fileName) {
		if (File::Exists(fileName)) {
			FileStream^ file = gcnew FileStream(fileName, FileMode::Open, FileAccess::Read);
			BinaryReader^ reader = gcnew BinaryReader(file);

			while (reader->BaseStream->Position < reader->BaseStream->Length) {
				// Зчитуємо дані для кожної кімнати
				int roomCapacity = reader->ReadInt32();
				int roomNumber = reader->ReadInt32();
				String^ roomType = reader->ReadString();
 

				String^ roomData = "Номер кімнати: "+ roomNumber + " Кількість місць: " + roomCapacity + " Тип кімнати: " + roomType;
				listBox1->Items->Add(roomData);
			}
			reader->Close();
			file->Close();
		}
		else {
			MessageBox::Show("Файл не знайдено: " + fileName);
		}
	}

	int Design::Generate() {
		Random^ random = gcnew Random();
		int fourDigitNumber = random->Next(1000, 10000);
		return fourDigitNumber;
	}
}
