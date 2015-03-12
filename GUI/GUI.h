#pragma once
#include <msclr/marshal_cppstd.h>
#include <iostream>
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
			bool firstTime = true;
			std::cout << "Is this your first time using this assistant? [Y/N]" << std::endl;
			string userResponse;
			if(userResponse == "Y"){
				//create a new text file as a database
			}
			else if(userResponse == "N"){
				std::cout << "Welcome back!" << std::endl;
			}
			else{
				std::cout << "Invalid Response! Please answer again. [Y/N]" << std::endl;
			}

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
			this->inputBox->Enter += gcnew System::EventHandler(this, &GUI::inputBox_Enter);
			this->inputBox->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::inputBox_KeyUp);
			this->inputBox->Leave += gcnew System::EventHandler(this, &GUI::inputBox_Leave);
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
				 vector<string> outputResponse = OperationCenter::executeInput("show today");
				 displayBox->Text = msclr::interop::marshal_as<String^>(outputResponse[0]);
				 outputMessageBox->Text =  msclr::interop::marshal_as<String^>(outputResponse[1]);
			 }
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	
	//User click the "Enter" button and the input is read
	private: System::Void confirmInputButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 string userInput = msclr::interop::marshal_as<string>(inputBox->Text);
				 inputBox->Clear;
				 OperationCenter::executeInput(userInput);
				 outputMessageBox->Text = msclr::interop::marshal_as<String^>(Feedback::getResponse);
				 displayBox->Text = msclr::interop::marshal_as<String^>(Feedback::getDisplay);
			}
	
	//User presses "Enter" key after typing
	private: System::Void inputBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
					if(e->KeyCode == Keys::Enter){
						confirmInputButton->PerformClick();
					}

			}
	
	private: System::Void inputBox_Enter(System::Object^  sender, System::EventArgs^  e) {
				 //Change the foreground and background color when the textBox is entered
				 if(inputBox->Text != String::Empty){
					 inputBox->ForeColor == Color::Red;
					 inputBox->BackColor == Color::Black;
				
				 //Move the selection pointer to the end of the text
					 inputBox->Select(inputBox->Text->Length, 0);
				 }


			}

	private: System::Void inputBox_Leave(System::Object^  sender, System::EventArgs^  e) {
				 //Reset the foreground and backgound color when the user leaves the inputBox
				 inputBox->ForeColor == Color::Black;
				 inputBox->BackColor == Color::White;
				 inputBox->Select(0,0);
			}

	private: System::Void inputBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		 }
	


};
}
