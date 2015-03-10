#pragma once
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
			OperationCenter myOperationCenter;
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
	private: System::Windows::Forms::TextBox^  outputBox;
	private: System::Windows::Forms::TextBox^  inputBox;
	private: System::Windows::Forms::Button^  confirmInputButton;
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
			this->outputBox = (gcnew System::Windows::Forms::TextBox());
			this->inputBox = (gcnew System::Windows::Forms::TextBox());
			this->confirmInputButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// outputBox
			// 
			resources->ApplyResources(this->outputBox, L"outputBox");
			this->outputBox->Name = L"outputBox";
			this->outputBox->ReadOnly = true;
			this->outputBox->UseWaitCursor = true;
			this->outputBox->TextChanged += gcnew System::EventHandler(this, &GUI::textBox1_TextChanged);
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
			// GUI
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->confirmInputButton);
			this->Controls->Add(this->inputBox);
			this->Controls->Add(this->outputBox);
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
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	
	//User click the "Enter" button and the input is read
	private: System::Void confirmInputButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 String^ userInput = inputBox->Text;
				 String^ outputmessage;
				 inputBox->Clear;
				 outputMessage = myOperationCenter.executeInput(userInput);
				 outputBox->Text = outputMessage;
			 }
	};
}
