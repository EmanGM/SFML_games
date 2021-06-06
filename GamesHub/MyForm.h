#pragma once

void exeGame(int game);


namespace StartGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;





	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Label^ label2;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(41, 124);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(143, 52);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Jogar Snake";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(41, 211);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(144, 52);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Jogar Tetris";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(41, 300);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(143, 52);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Jogar FlappyDuck";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(51, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(156, 34);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Choose a game to play!\r\n\r\n";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(41, 388);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(143, 52);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Jogar Arkanoid";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(41, 475);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(142, 51);
			this->button5->TabIndex = 6;
			this->button5->Text = L"Jogar Asteroides";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(41, 563);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(144, 52);
			this->button6->TabIndex = 12;
			this->button6->Text = L"Jogar Pong\r\n(2 jogadores)\r\n";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(214, 171);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(206, 136);
			this->label2->TabIndex = 13;
			this->label2->Text = L"           Controls \r\n\r\n\r\nBasically arrows or WASD\r\n\r\nPress Enter to restart the "
				L"game\r\n\r\nPress R to exit at any time ";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(418, 643);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		exeGame(1);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		exeGame(2);
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		exeGame(3);
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		exeGame(4);
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		exeGame(5);
	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		exeGame(6);
	}
};
}
