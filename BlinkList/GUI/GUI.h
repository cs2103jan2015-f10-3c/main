#pragma once
#include <msclr/marshal_cppstd.h>
#include "OperationCenter.h"

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::TextBox^  inputBox;
	private: System::Windows::Forms::Button^  confirmInputButton;
	private: System::Windows::Forms::TextBox^  outputMessageBox;
	private: System::Windows::Forms::TextBox^  displayBox;





	protected: 

	protected: 



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GUI::typeid));
			this->inputBox = (gcnew System::Windows::Forms::TextBox());
			this->confirmInputButton = (gcnew System::Windows::Forms::Button());
			this->outputMessageBox = (gcnew System::Windows::Forms::TextBox());
			this->displayBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// inputBox
			// 
			resources->ApplyResources(this->inputBox, L"inputBox");
			this->inputBox->Name = L"inputBox";
			this->inputBox->UseWaitCursor = true;
			// 
			// confirmInputButton
			// 
			resources->ApplyResources(this->confirmInputButton, L"confirmInputButton");
			this->confirmInputButton->Name = L"confirmInputButton";
			this->confirmInputButton->UseVisualStyleBackColor = true;
			this->confirmInputButton->UseWaitCursor = true;
			this->confirmInputButton->Click += gcnew System::EventHandler(this, &GUI::confirmInputButton_Click);
			// 
			// outputMessageBox
			// 
			resources->ApplyResources(this->outputMessageBox, L"outputMessageBox");
			this->outputMessageBox->Name = L"outputMessageBox";
			this->outputMessageBox->ReadOnly = true;
			this->outputMessageBox->UseWaitCursor = true;
			// 
			// displayBox
			// 
			resources->ApplyResources(this->displayBox, L"displayBox");
			this->displayBox->Name = L"displayBox";
			this->displayBox->ReadOnly = true;
			this->displayBox->UseWaitCursor = true;
			// 
			// GUI
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->displayBox);
			this->Controls->Add(this->outputMessageBox);
			this->Controls->Add(this->confirmInputButton);
			this->Controls->Add(this->inputBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->Name = L"GUI";
			this->UseWaitCursor = true;
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	//Actions happen whenever the user loads the application
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
				 //Show welcome message
				 //string welcomeMessage = OperationCenter::welcomeUser();
				 //outputMessageBox->Text = msclr::interop::marshal_as<String^>(welcomeMessage);
				 outputMessageBox->Text = "Hello Jim, Welcome to your Private Assistant!";
				 string dailyAgenda = OperationCenter::executeInput("show today");
				 displayBox->Text = msclr::interop::marshal_as<String^>(dailyAgenda);
			 }
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	
	//User click the "Enter" button and the input is read
	private: System::Void confirmInputButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 string userInput = msclr::interop::marshal_as<string>(inputBox->Text);
				 std::vector<string> displayString;
				 inputBox->Clear;
				 displayString = OperationCenter::executeInput(userInput);
				 outputMessageBox->Text = msclr::interop::marshal_as<String^>(displayString[0]);
				 displayBox->Text = msclr::interop::marshal_as<String^>(displayString[1]);
			 }
	
private: System::Void inputBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		 }
};
}
