#pragma once
#include "HotelSystem.h"

namespace laboop {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class viewBookings : public System::Windows::Forms::Form
	{
		Design^ design;
		HotelSystem^ hotelSystem;
		Client^ client;
	public:
		viewBookings(HotelSystem^ system)
		{
			InitializeComponent();
			this->design = gcnew Design(listBox1);
			this->hotelSystem = system;
		}

	protected:
		~viewBookings()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ listBox1;
	protected:

	private:
		System::ComponentModel::Container^ components;

#pragma region
		void InitializeComponent(void)
		{
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->HorizontalScrollbar = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(12, 12);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(1073, 356);
			this->listBox1->TabIndex = 0;
			this->listBox1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &viewBookings::listBox1_MouseDoubleClick);
			// 
			// viewBookings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1097, 385);
			this->Controls->Add(this->listBox1);
			this->Name = L"viewBookings";
			this->Text = L"viewBookings";
			this->Load += gcnew System::EventHandler(this, &viewBookings::viewBookings_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void viewBookings_Load(System::Object^ sender, System::EventArgs^ e) {
		design->LoadViewForm(hotelSystem);
	}

	private: System::Void listBox1_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (hotelSystem != nullptr && !hotelSystem->getIsUserTurn()) {
			Windows::Forms::DialogResult result = MessageBox::Show("������ ��", "ϳ�����������", MessageBoxButtons::YesNoCancel);

			if (result == Windows::Forms::DialogResult::Yes) {

				MessageBox::Show("�� ������ 'Yes'");
			}
			else if (result == Windows::Forms::DialogResult::No) {
				MessageBox::Show("�� ������ 'No'");
			}
			else if (result == Windows::Forms::DialogResult::Cancel) {
				return;
			}
		}
		else {
			if (listBox1->SelectedItem != nullptr) {
				String^ selectedRoom = listBox1->SelectedItem->ToString();
				if (selectedRoom->StartsWith("����� ������:")) {
					// ��������� ��������� ������� "����� ������: "
					int roomNumberStart = selectedRoom->IndexOf(": ") + 2;
					int roomNumberEnd = selectedRoom->IndexOf(" ʳ������ ����:");
					String^ roomNumberStr = selectedRoom->Substring(roomNumberStart, roomNumberEnd - roomNumberStart);

					// ��������� ������� "ʳ������ ����: "
					int roomCapacityStart = selectedRoom->IndexOf("ʳ������ ����: ") + 17;
					int roomCapacityEnd = selectedRoom->IndexOf(" ��� ������:");
					String^ roomCapacityStr = selectedRoom->Substring(roomCapacityStart, roomCapacityEnd - roomCapacityStart);

					// ��������� ������� "��� ������: "
					int roomTypeStart = selectedRoom->IndexOf("��� ������: ") + 13;
					String^ roomTypeStr = selectedRoom->Substring(roomTypeStart);

					// ���������� ������� ����� � ������� ����
					int roomNumber = Int32::Parse(roomNumberStr);
					int roomCapacity = Int32::Parse(roomCapacityStr);
					String^ roomType = roomTypeStr;

					// ��������� ��'��� Room �� ����� ��������� �����
					Room^ selectedRoomObject = gcnew Room(roomCapacity, roomNumber, roomType);

					design->SaveToFile(selectedRoomObject, "newRoomData.dat");

					MessageBox::Show("ʳ����� ������ ���������!");
				}
			}
		}
	}
	};
}
